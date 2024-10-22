#pragma once
#include <GL/glew.h>

class Model {
public:
    Model(const float* vertices, size_t size, int vertexCount);
    void draw() const;

private:
    int vertexCount;
    GLuint VAO, VBO;
};
