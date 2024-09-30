#pragma once

#include "shader.hpp"

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <vector>
#include <map>
#include <string>
#include <memory>

struct MaterialProperty {
    // char name[64];
    GLuint location;
    GLenum type;
};

class Material {
public:
    Material(GLuint handle, GLboolean canFindAttribs);
    ~Material();

    void use();
    GLuint getHandle() { return program; }

    // By name
    void uniform1(const std::string &name, GLint value);
    void uniform1(const std::string &name, GLuint value);
    void uniform1(const std::string &name, GLfloat value);
    void uniform2(const std::string &name, const glm::vec2 &vec);
    void uniform3(const std::string &name, const glm::vec3 &vec);
    void uniform4(const std::string &name, const glm::vec4 &vec);
    void uniform4x4(const std::string &name, const glm::mat4 &matrix);

    // By location
    void uniform1(GLuint location, GLint value);
    void uniform1(GLuint location, GLuint value);
    void uniform1(GLuint location, GLfloat value);
    void uniform2(GLuint location, const glm::vec2 &vec);
    void uniform3(GLuint location, const glm::vec3 &vec);
    void uniform4(GLuint location, const glm::vec4 &vec);
    void uniform4x4(GLuint location, const glm::mat4 &matrix);

    MaterialProperty getPropertyInfo(GLuint location);
    MaterialProperty getPropertyInfo(const std::string &name);

private:
    GLuint getLocation(const std::string &name);

    GLuint program;

    std::map<std::string, MaterialProperty> uniforms;
    std::vector<MaterialProperty> uniformsIndexed;

    GLboolean canFindAttribs = false;
};

class MaterialBuilder {
public:
    MaterialBuilder();
    ~MaterialBuilder();

    std::shared_ptr<Material> build();
    std::unique_ptr<Material> buildUnique();
    MaterialBuilder attachShader(std::shared_ptr<Shader> shader);

private:
    std::vector<std::shared_ptr<Shader>> attachedShaders;
};
