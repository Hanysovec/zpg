#pragma once
#include "BasicModel.h"
#include "Texture.h"
class TextureModel : public BasicModel
{
public:
    TextureModel(const float* vertices, size_t size, int vertexCount);
    void draw() const;

private:
    int vertexCount;
    GLuint VAO, VBO;

};

