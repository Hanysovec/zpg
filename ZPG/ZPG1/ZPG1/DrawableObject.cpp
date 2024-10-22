#include "DrawableObject.h"
#include "Camera.h"

DrawableObject::DrawableObject(const float* vertices, size_t size, int vertexCount, ShaderProgram* shader) {
    this->model = new Model(vertices, size, vertexCount);
    this->shaderProgram = shader;
}

DrawableObject::~DrawableObject() {
    delete model;
}

void DrawableObject::draw() const {
    shaderProgram->use();
    shaderProgram->setModelMatrix(transform.getMatrix());
    model->draw();
    shaderProgram->stop();
}

void DrawableObject::translate(const glm::vec3& offset) {
    transform.translate(offset);
}

void DrawableObject::rotate(float angle, const glm::vec3& axis) {
    transform.rotate(angle, axis);
}

void DrawableObject::scale(const glm::vec3& scale) {
    transform.scale(scale);
}
