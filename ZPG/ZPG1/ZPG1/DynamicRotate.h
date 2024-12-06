#pragma once
#include "BaseTransform.h"
#include <glm/gtc/matrix_transform.hpp>

class DynamicRotate : public BaseTransform {
    float angle;
    float rotationSpeed;
    glm::vec3 axis;

public:
    DynamicRotate(float angle, float speed, const glm::vec3& axis);
    glm::mat4 getMatrix(const glm::mat4& matrix) override;
};
