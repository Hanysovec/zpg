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
    for (auto& transform : transforms) {
        if (auto translate = dynamic_cast<Translate*>(transform)) {
            translate->offset = offset;
            return;
        }
    }
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
void Transformation::addDynamicRotate(float angle, float speed, const glm::vec3& axis) {
    DynamicRotate* dynRotate = new DynamicRotate(angle, speed, axis);
    transforms.push_back(dynRotate);
}

const glm::mat4& Transformation::getMatrix() const {
    modelMatrix = glm::mat4(1.0f);

    glm::mat4 scaleMatrix = glm::mat4(1.0f);
    glm::mat4 rotateMatrix = glm::mat4(1.0f);
    glm::mat4 translateMatrix = glm::mat4(1.0f);

    for (const auto& transform : transforms) {
        if (auto scale = dynamic_cast<Scale*>(transform)) {
            scaleMatrix = scale->getMatrix(scaleMatrix);
        }
        else if (auto rotate = dynamic_cast<Rotate*>(transform)) {
            rotateMatrix = rotate->getMatrix(rotateMatrix);
        }
        else if (auto dynRotate = dynamic_cast<DynamicRotate*>(transform)) {
            rotateMatrix = dynRotate->getMatrix(rotateMatrix);
        }
        else if (auto translate = dynamic_cast<Translate*>(transform)) {
            translateMatrix = translate->getMatrix(translateMatrix);
        }
    }
    modelMatrix = translateMatrix * rotateMatrix * scaleMatrix;
    return modelMatrix;
}

