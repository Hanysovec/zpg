#pragma once
#include "BaseTransform.h"
#include <glm/gtc/matrix_transform.hpp>
class Rotate : public BaseTransform {
    float angle;
    glm::vec3 axis;

public:
    Rotate(float angle, const glm::vec3& axis);
    glm::mat4 apply(const glm::mat4& matrix) const override;
};

