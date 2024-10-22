#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Observer.h"
#include <vector>
class Camera {
public:
    Camera();
    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix() const;

    void setPosition(const glm::vec3& position);
    void setTarget(const glm::vec3& target);
    void setProjection(float fov, float aspectRatio, float nearPlane, float farPlane);

    void moveForward(float distance);
    void moveBackward(float distance);
    void moveRight(float distance);
    void moveLeft(float distance);
    void rotate(float yaw, float pitch);
    void addObserver(Observer* observer);
    void notifyObservers();

private:
    glm::vec3 position;
    glm::vec3 target;
    glm::vec3 up;
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
    glm::vec3 forward;
    float yaw;
    float pitch;
    std::vector<Observer*> observers;

    void updateViewMatrix();
};

