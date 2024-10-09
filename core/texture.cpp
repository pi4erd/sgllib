#include "texture.hpp"
#include "log.hpp"

#include <GL/glew.h>
#include <memory>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

Texture::Texture(GLuint handle) : handle(handle) {
    LOG_DEBUG("Created texture {}", handle);
}

std::shared_ptr<Texture> Texture::createEmptyStorage(GLsizei width, GLsizei height, GLenum format) {
    GLuint handle;

    glGenTextures(1, &handle);
    glBindTexture(GL_TEXTURE_2D, handle);

    glTextureParameteri(handle, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTextureParameteri(handle, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTextureParameteri(handle, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTextureParameteri(handle, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
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

    glTextureParameteri(handle, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTextureParameteri(handle, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTextureParameteri(handle, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTextureParameteri(handle, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

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


Texture::~Texture() {
    LOG_DEBUG("Destroying texture {}", handle);
    glDeleteTextures(1, &handle);
}

void Texture::use(GLuint unit) {
    glBindTextureUnit(unit, handle);
}

void Texture::bind_image(GLuint unit, GLenum accessMode) {
    // TODO: Decide what to do with format here
    glBindImageTexture(unit, handle, 0, GL_FALSE, 0, accessMode, GL_RGBA32F);
}
