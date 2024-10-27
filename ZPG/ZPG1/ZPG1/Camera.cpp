#include "Camera.h"
#include "Observer.h"

Camera::Camera()
    : position(glm::vec3(0.0f, 0.5f, 0.5f)),
    target(glm::vec3(0.0f, 0.0f, 0.0f)),
    up(glm::vec3(0.0f, 1.0f, 0.0f)),
    yaw(0.0f),
    pitch(0.0f)
{
    forward = glm::normalize(target - position);
    projectionMatrix = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
    updateViewMatrix();
}

glm::mat4 Camera::getViewMatrix() const {
    return viewMatrix;
}

glm::mat4 Camera::getProjectionMatrix() const {
    return projectionMatrix;
}

glm::vec3 Camera::getPosition() const
{
    return position;
}

void Camera::updateViewMatrix() {
    viewMatrix = glm::lookAt(position, target, up);
    notifyObservers(viewMatrix, projectionMatrix, position);
}

void Camera::moveForward(float distance) {
    position += forward * distance;
    target = position + forward;
    updateViewMatrix();
}

void Camera::moveBackward(float distance) {
    position -= forward * distance;
    target = position + forward;
    updateViewMatrix();
}

void Camera::moveLeft(float distance) {
    glm::vec3 right = glm::normalize(glm::cross(forward, up));
    position -= right * distance;
    target = position + forward;
    updateViewMatrix();
}

void Camera::moveRight(float distance) {
    glm::vec3 right = glm::normalize(glm::cross(forward, up));
    position += right * distance;
    target = position + forward;
    updateViewMatrix();
}

void Camera::rotate(float deltaYaw, float deltaPitch) {
    yaw += deltaYaw;
    pitch += deltaPitch;

    if (pitch > 89.0f) {
        pitch = 89.0f;
    }

    if (pitch < -89.0f) {
        pitch = -89.0f;
    }

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    forward = glm::normalize(front);
    target = position + forward;
    updateViewMatrix();
}
