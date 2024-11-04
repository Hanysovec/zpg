#include "Transformation.h"

/*Transformation::Transformation() {
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
}*/

void Transformation::addTranslate(const glm::vec3& offset) {
    Translate* translate = new Translate(offset);
    transforms.push_back(translate);
}

void Transformation::addRotate(float angle, const glm::vec3& axis) {
    Rotate* rotate = new Rotate(angle, axis);
    transforms.push_back(rotate);
}

void Transformation::addScale(const glm::vec3& scaleF) {
    Scale* scale = new Scale(scaleF);
    transforms.push_back(scale);
}

const glm::mat4& Transformation::getMatrix() const {
    modelMatrix = glm::mat4(1.0f);
    for (const auto& transform : transforms) {
        modelMatrix = transform->apply(modelMatrix);
    }
    return modelMatrix;
}

