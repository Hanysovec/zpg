#pragma once
#include "BaseTransform.h"
#include <glm/gtc/matrix_transform.hpp>
class Translate : public BaseTransform {
    glm::vec3 offset;

public:
    Translate(const glm::vec3& offset);
    glm::mat4 apply(const glm::mat4& matrix) const override;
};

