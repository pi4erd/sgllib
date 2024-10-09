#pragma once

#include <GL/glew.h>
#include <memory>

class Texture {
public:
    Texture(GLuint handle);
    ~Texture();

    static std::shared_ptr<Texture> createEmptyStorage(GLsizei width, GLsizei height, GLenum format=GL_RGBA32F);
    static std::shared_ptr<Texture> fromImage(const std::string &path, GLenum format=GL_RGBA8);

    void recreateStorage(GLsizei newWidth, GLsizei newHeight, GLenum format=GL_RGBA32F);

    void makeMipmaps();

    // Binds and sets texture to unit
    void bind_image(GLuint unit, GLenum accessMode);
    void use(GLuint unit);
    GLuint getHandle() { return handle; }

private:
    GLuint handle;
};
