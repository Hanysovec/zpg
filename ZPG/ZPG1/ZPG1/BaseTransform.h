#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

class BaseTransform {
protected:
    glm::mat4 modelMatrix = glm::mat4(1.0f);

public:
    virtual glm::mat4 apply(const glm::mat4& matrix) const = 0;
};
