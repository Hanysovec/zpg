#pragma once
#include "BasicModel.h"
#include "Texture.h"
#include "ModelLoader.h"
class ObjectModel : public BasicModel
{
public:
    ObjectModel(ModelLoader::Vertex* model, int vertexCount, unsigned int* pIndices, unsigned int mNumVertices, int modelId);
    void draw() const;

private:
    int vertexCount;
    ModelLoader::Vertex* model;
    unsigned int* pIndices;
    int modelId;
    GLuint VAO, VBO, IBO;
};

