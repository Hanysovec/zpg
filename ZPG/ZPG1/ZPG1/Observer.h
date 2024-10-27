#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
class Observer
{
public:
    virtual void onCameraUpdate(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const glm::vec3& cameraPosition) = 0;
    virtual void onLightUpdate(const glm::vec3& position) = 0;
};

