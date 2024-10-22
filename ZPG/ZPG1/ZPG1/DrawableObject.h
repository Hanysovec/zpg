#pragma once
#include "ShaderProgram.h"
#include "Model.h"
#include "Transformation.h"

class DrawableObject {
public:
    DrawableObject(const float* vertices, size_t size, int vertexCount, ShaderProgram* shader);
    ~DrawableObject();
    void draw() const;
    void translate(const glm::vec3& offset);
    void rotate(float angle, const glm::vec3& axis);
    void scale(const glm::vec3& scale);

private:
    Model* model;
    ShaderProgram* shaderProgram;
    Transformation transform;
};
