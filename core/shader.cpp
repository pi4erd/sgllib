#include "shader.hpp"
#include "log.hpp"

#include <fmt/format.h>

#include "fileutil.hpp"

Shader::Shader(GLenum shaderType)
{
    LOG_DEBUG("Created shader type {}", shaderType);
    shader = glCreateShader(shaderType);
}

Shader::~Shader()
{
    glDeleteShader(shader);
    LOG_DEBUG("Deleted shader {}", shader);
}

GLuint Shader::getId()
{
    return shader;
}

void Shader::compile()
{
    glCompileShader(shader);

    int success;

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(success != GL_TRUE) {
        char infoLog[512];
        glGetShaderInfoLog(shader, sizeof(infoLog), nullptr, infoLog);

        throw std::runtime_error(fmt::format("Failed to compile shader: {}", infoLog));
    }
}

std::shared_ptr<Shader> Shader::fromGlslFile(std::string path, GLenum shaderType)
{
    std::string shaderCode = utils::readFileToEnd(path);

    std::shared_ptr<Shader> result = std::make_shared<Shader>(shaderType);

    const char* shaderCodeCstr = shaderCode.c_str();

    glShaderSource(result->shader, 1, &shaderCodeCstr, nullptr);

    result->compile();

    return result;
}

std::unique_ptr<Shader> Shader::fromGlslFileUnique(std::string path, GLenum shaderType)
{
    std::string shaderCode = utils::readFileToEnd(path);

    std::unique_ptr<Shader> result = std::make_unique<Shader>(shaderType);

    const char* shaderCodeCstr = shaderCode.c_str();

    glShaderSource(result->shader, 1, &shaderCodeCstr, nullptr);

    result->compile();

    return std::move(result);
}

std::shared_ptr<Shader> Shader::fromSpirvBinary(std::string path, GLenum shaderType)
{
    std::vector<uint8_t> binary = utils::readFileBinary(path);

    std::shared_ptr<Shader> result = std::make_shared<Shader>(shaderType);

    glShaderBinary(1, &result->shader, GL_SHADER_BINARY_FORMAT_SPIR_V, binary.data(), binary.size());
    glSpecializeShader(result->shader, "main", 0, nullptr, nullptr);

    int success;

    glGetShaderiv(result->shader, GL_COMPILE_STATUS, &success);

    if(success != GL_TRUE) {
        char infoLog[512];
        glGetShaderInfoLog(result->shader, sizeof(infoLog), nullptr, infoLog);

        throw std::runtime_error(fmt::format("Failed to specialize shader binary: {}", infoLog));
    }

    result->spirvBinary = GL_TRUE;

    return result;
}

std::unique_ptr<Shader> Shader::fromSpirvBinaryUnique(std::string path, GLenum shaderType)
{
    std::vector<uint8_t> binary = utils::readFileBinary(path);

    std::unique_ptr<Shader> result = std::make_unique<Shader>(shaderType);

    glShaderBinary(1, &result->shader, GL_SHADER_BINARY_FORMAT_SPIR_V, binary.data(), binary.size());
    glSpecializeShader(result->shader, "main", 0, nullptr, nullptr);

    int success;

    glGetShaderiv(result->shader, GL_COMPILE_STATUS, &success);

    if(success != GL_TRUE) {
        char infoLog[512];
        glGetShaderInfoLog(result->shader, sizeof(infoLog), nullptr, infoLog);

        throw std::runtime_error(fmt::format("Failed to specialize shader binary: {}", infoLog));
    }
    
    result->spirvBinary = GL_TRUE;

    return std::move(result);
}
