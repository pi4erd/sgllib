#pragma once

#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <memory>

constexpr int VERTEX_ATTRIBS[] = {
    3, // v_position
    3, // v_normal
};

constexpr int INSTANCE_ATTRIBS[] = {
    3, // i_offset
};

class Mesh {
public:
    Mesh(GLuint vbo, GLuint vao, GLuint ebo, size_t vcount);
    ~Mesh();

    void draw(GLenum primitiveType=GL_TRIANGLES);
    void drawInstanced(size_t instanceCount, GLenum primitiveType=GL_TRIANGLES);

    static std::shared_ptr<Mesh> createFromVertexArrayAttrib(
        const std::vector<float> &vertData,
        const std::vector<GLuint> &indices,
        const std::vector<int> attribs
    );

    static std::shared_ptr<Mesh> createFromVertexArray(
        const std::vector<float> &vertData,
        const std::vector<GLuint> &indices
    );

    static std::shared_ptr<Mesh> createFromVertexArrayInstanced(
        const std::vector<float> &vertData,
        const std::vector<GLuint> &indices,
        GLuint instanceBuffer
    );

private:
    GLuint vbo, vao, ebo;
    
    size_t elementCount;
};
