#include "camera.hpp"

#include "log.hpp"
#include <glm/ext/matrix_transform.hpp>
#include <glm/matrix.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

Camera::Camera() : origin(0.0), rotation(0.0),
  up(0.0, -1.0, 0.0), fovY(glm::half_pi<float>()),
  nearPlane(0.1f), farPlane(5000.0f) {
    LOG_DEBUG("Created camera");
}

Camera::~Camera() {
    LOG_DEBUG("Destroyed camera");
}

glm::vec3 Camera::right() {
    return rotationMatrix() * glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
}

glm::vec3 Camera::forward() {
    return rotationMatrix() * glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
}

glm::mat4 Camera::rotationMatrix() {
    return glm::rotate(rotation.y, glm::vec3(0.0, -1.0, 0.0))
        * glm::rotate(rotation.x, glm::vec3(1.0, 0.0, 0.0))
        * glm::rotate(rotation.z, glm::vec3(0.0, 0.0, 1.0));
}

glm::mat4 Camera::viewMatrix() {
    return glm::lookAt(origin, origin + forward(), up);
}

glm::mat4 Camera::projectionMatrix(float aspect) {
    return glm::perspectiveLH(fovY, aspect, nearPlane, farPlane);
}
