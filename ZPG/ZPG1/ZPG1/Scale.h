#pragma once
#include "BaseTransform.h"
#include <glm/gtc/matrix_transform.hpp>
class Scale : public BaseTransform {
    glm::vec3 scale;

public:
    Scale(const glm::vec3& scaleFactor);
    glm::mat4 getMatrix(const glm::mat4& matrix) override;
};

