#pragma once
#include "BasicModel.h"
class SkyboxModel : public BasicModel
{
public:
    SkyboxModel(const float* vertices, size_t size, int vertexCount);
    void draw() const;

private:
    int vertexCount;
    GLuint VAO, VBO;
};

