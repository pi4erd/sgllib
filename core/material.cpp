#include "material.hpp"
#include "log.hpp"

#include <fmt/format.h>

#include <glm/gtc/type_ptr.hpp>
#include <stdexcept>

Material::Material(GLuint handle, GLboolean canFindAttribs) : program(handle), canFindAttribs(canFindAttribs)
{
    int uniformCount;

    glUseProgram(program);
    glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &uniformCount);

    GLenum type;
    GLuint location;
    GLsizei size, length;

    char nameBuffer[256];
    for(int i = 0; i < uniformCount; i++) {
        glGetActiveUniform(program, (GLuint)i, sizeof(nameBuffer), &length, &size,
            &type, nameBuffer);
        location = glGetUniformLocation(program, nameBuffer);
        
        if(location == UINT32_MAX) {
            LOG_ERROR("Failed to find uniform ID {}.", i);
            continue;
        }

        MaterialProperty property = {location, type};
        uniforms.insert({nameBuffer, property});
    }

    LOG_DEBUG("Constructed material {}", program);
}

Material::~Material()
{
    glDeleteProgram(program);

    LOG_DEBUG("Destroyed material {}", program);
}

void Material::use()
{
    glUseProgram(program);
}

void Material::uniform1(const std::string &name, GLint value)
{
    glUniform1i(getLocation(name), value);
}

void Material::uniform1(const std::string &name, GLuint value)
{
    glUniform1ui(getLocation(name), value);
}

void Material::uniform1(const std::string &name, GLfloat value)
{
    glUniform1f(getLocation(name), value);
}

void Material::uniform2(const std::string &name, const glm::vec2 &vec)
{
    glUniform2fv(getLocation(name), 1, glm::value_ptr(vec));
}

void Material::uniform3(const std::string &name, const glm::vec3 &vec)
{
    glUniform3fv(getLocation(name), 1, glm::value_ptr(vec));
}

void Material::uniform4(const std::string &name, const glm::vec4 &vec)
{
    glUniform4fv(getLocation(name), 1, glm::value_ptr(vec));
}

void Material::uniform4x4(const std::string &name, const glm::mat4 &matrix)
{
    glUniformMatrix4fv(getLocation(name), 1, false, glm::value_ptr(matrix));
}

void Material::uniform1(GLuint location, GLint value) {
    glUniform1i(location, value);
}

void Material::uniform1(GLuint location, GLuint value) {
    glUniform1ui(location, value);
}

void Material::uniform1(GLuint location, GLfloat value) {
    glUniform1f(location, value);
}

void Material::uniform2(GLuint location, const glm::vec2 &vec) {
    glUniform2fv(location, 1, glm::value_ptr(vec));
}

void Material::uniform3(GLuint location, const glm::vec3 &vec) {
    glUniform3fv(location, 1, glm::value_ptr(vec));
}

void Material::uniform4(GLuint location, const glm::vec4 &vec) {
    glUniform4fv(location, 1, glm::value_ptr(vec));
}

void Material::uniform4x4(GLuint location, const glm::mat4 &matrix) {
    glUniformMatrix4fv(location, 1, false, glm::value_ptr(matrix));
}

GLuint Material::getLocation(const std::string &name)
{
    if(!canFindAttribs)
        throw std::runtime_error("Cannot search for locations in material with SpirV shaders!");

    if(uniforms.find(name) == uniforms.end()) // Fall back if uniform isn't in the map
        return glGetUniformLocation(program, name.c_str());

    return uniforms[name].location;
}

MaterialBuilder::MaterialBuilder()
{
    LOG_DEBUG("Created MaterialBuilder");
}

MaterialBuilder::~MaterialBuilder()
{
    LOG_DEBUG("Destroyed MaterialBuilder");
}

std::shared_ptr<Material> MaterialBuilder::build()
{
    GLuint program = glCreateProgram();

    GLboolean canFindAttribs = GL_TRUE;

    for(auto &shader : attachedShaders) {
        if(shader->spirvBinary == GL_TRUE) canFindAttribs = GL_FALSE;
        glAttachShader(program, shader->getId());
    }

    glLinkProgram(program);

    int success;

    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if(success != GL_TRUE) {
        char infoLog[512];
        glGetProgramInfoLog(program, sizeof(infoLog), nullptr, infoLog);
        throw std::runtime_error(fmt::format("Failed to link shaders in material: {}", infoLog));
    }

    for(auto shader : attachedShaders) {
        glDetachShader(program, shader->getId());
    }
    attachedShaders.clear();

    return std::make_shared<Material>(program, canFindAttribs);
}

std::unique_ptr<Material> MaterialBuilder::buildUnique()
{
    GLuint program = glCreateProgram();
    GLboolean canFindAttribs = GL_TRUE;

    for(auto &shader : attachedShaders) {
        if(shader->spirvBinary == GL_TRUE) canFindAttribs = GL_FALSE;
        glAttachShader(program, shader->getId());
    }

    glLinkProgram(program);

    int success;

    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if(success != GL_TRUE) {
        char infoLog[512];
        glGetProgramInfoLog(program, sizeof(infoLog), nullptr, infoLog);
        throw std::runtime_error(fmt::format("Failed to link shaders in material: {}", infoLog));
    }

    for(auto shader : attachedShaders) {
        glDetachShader(program, shader->getId());
    }
    attachedShaders.clear();

    return std::make_unique<Material>(program, canFindAttribs);
}

MaterialBuilder MaterialBuilder::attachShader(std::shared_ptr<Shader> shader)
{
    LOG_DEBUG("Attached shader {}", shader->getId());

    attachedShaders.push_back(shader);
    return std::move(*this);
}
