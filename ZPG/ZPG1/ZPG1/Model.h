#pragma once
#include <GL/glew.h>
#include "BasicModel.h"

class Model : public BasicModel {
public:
    Model(const float* vertices, size_t size, int vertexCount, int modelId);
    void draw() const;

private:
    int vertexCount;
    int modelId;
    GLuint VAO, VBO;
};
