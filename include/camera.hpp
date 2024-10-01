#pragma once

#include <glm/glm.hpp>

class Camera {
public:
    Camera();
    ~Camera();

    glm::vec3 right();
    glm::vec3 forward();

    glm::mat4 rotationMatrix();

    glm::mat4 viewMatrix();
    glm::mat4 projectionMatrix(float aspect);
    glm::mat4 projectionRHMatrix(float aspect);

public: // public properties
    glm::vec3 origin;
    glm::vec3 rotation;
    glm::vec3 up;

    float nearPlane, farPlane;
    float fovY;
};
