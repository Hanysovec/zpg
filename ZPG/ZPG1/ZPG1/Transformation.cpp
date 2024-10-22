#include "Transformation.h"

Transformation::Transformation() {
    modelMatrix = glm::mat4(1.0f);
}

void Transformation::translate(const glm::vec3& offset) {
    modelMatrix = glm::translate(modelMatrix, offset);
}

void Transformation::rotate(float angle, const glm::vec3& axis) {
    modelMatrix = glm::rotate(modelMatrix, angle, axis);
}

void Transformation::scale(const glm::vec3& scale) {
    modelMatrix = glm::scale(modelMatrix, scale);
}

const glm::mat4& Transformation::getMatrix() const {
    return modelMatrix;
}
