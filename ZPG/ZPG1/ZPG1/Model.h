#pragma once
#include <GL/glew.h>
#include "BasicModel.h"

class Model : public BasicModel {
public:
    Model(const float* vertices, size_t size, int vertexCount);
    void draw() const;

private:
    int vertexCount;
    GLuint VAO, VBO;
};
