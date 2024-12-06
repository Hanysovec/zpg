#pragma once
#include "BaseTransform.h"
#include <glm/gtc/matrix_transform.hpp>
class Translate : public BaseTransform {

public:
    glm::vec3 offset;
    Translate(const glm::vec3& offset);
    glm::mat4 getMatrix(const glm::mat4& matrix) override;
};

