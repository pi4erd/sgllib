#pragma once

#include <GL/glew.h>

#include <memory>
#include <string>

class Shader {
public:
    Shader(GLenum shaderType);
    ~Shader();

    GLuint getId();
    void compile();

    static std::shared_ptr<Shader> fromGlslFile(std::string path, GLenum shaderType);
    static std::unique_ptr<Shader> fromGlslFileUnique(std::string path, GLenum shaderType);
    static std::shared_ptr<Shader> fromSpirvBinary(std::string path, GLenum shaderType);
    static std::unique_ptr<Shader> fromSpirvBinaryUnique(std::string path, GLenum shaderType);

    GLuint shader;
};
