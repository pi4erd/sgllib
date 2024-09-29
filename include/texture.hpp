#pragma once

#include <GL/glew.h>
#include <memory>

class Texture {
public:
    Texture(GLuint handle);
    ~Texture();

    static std::shared_ptr<Texture> createEmptyStorage(GLsizei width, GLsizei height);
    static std::shared_ptr<Texture> fromImage(const std::string &path);

    void recreateStorage(GLsizei newWidth, GLsizei newHeight);

    void makeMipmaps();

    // Binds and sets texture to unit
    void bind_image(GLuint unit, GLenum accessMode);
    void use(GLuint unit);
    GLuint getHandle() { return handle; }

private:
    GLuint handle;
};
