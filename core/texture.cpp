#include "texture.hpp"
#include "log.hpp"

#include <GL/glew.h>
#include <memory>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

Texture::Texture(GLuint handle) : handle(handle) {
    LOG_DEBUG("Created texture {}", handle);
}

Texture::~Texture() {
    LOG_DEBUG("Destroying texture {}", handle);
    glDeleteTextures(1, &handle);
}

std::shared_ptr<Texture> Texture::createEmptyStorage(GLsizei width, GLsizei height, GLenum format) {
    GLuint handle;

    glGenTextures(1, &handle);
    glBindTexture(GL_TEXTURE_2D, handle);
    
    glTextureStorage2D(handle, 1, format, width, height);
    
    return std::make_shared<Texture>(handle);
}

std::shared_ptr<Texture> Texture::fromImage(const std::string &path, GLenum format) {
    GLuint handle;

    glGenTextures(1, &handle);
    glBindTexture(GL_TEXTURE_2D, handle);

    int width, height, channels;
    uint8_t *image_data = stbi_load(path.c_str(), &width, &height, &channels, 4);

    glTexImage2D(
        GL_TEXTURE_2D, 0, format,
        width, height, 0, GL_RGBA,
        GL_UNSIGNED_BYTE, image_data
    );

    stbi_image_free(image_data);

    return std::make_shared<Texture>(handle);
}

void Texture::recreateStorage(GLsizei newWidth, GLsizei newHeight, GLenum format)
{
    // Hope this is enough
    glBindTexture(GL_TEXTURE_2D, handle);
    glTextureStorage2D(handle, 1, format, newWidth, newHeight);
}

void Texture::makeMipmaps() {
    glBindTexture(GL_TEXTURE_2D, handle);
    glActiveTexture(GL_TEXTURE0);
    glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture::setParameter(GLenum param, GLint value) {
    glBindTexture(GL_TEXTURE_2D, handle);
    glTexParameteri(GL_TEXTURE_2D, param, value);
}

void Texture::use(GLuint unit) {
    glBindTexture(GL_TEXTURE_2D, handle);
    glBindTextureUnit(unit, handle);
}

void Texture::bind_image(GLuint unit, GLenum accessMode) {
    // TODO: Decide what to do with format here
    glBindImageTexture(unit, handle, 0, GL_FALSE, 0, accessMode, GL_RGBA32F);
}
