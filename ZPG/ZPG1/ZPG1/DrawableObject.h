#pragma once
#include "ShaderProgram.h"
#include "Model.h"
#include "BasicModel.h"
#include "Transformation.h"
#include "Material.h"
#include "TextureModel.h"
#include "SkyboxModel.h"

class DrawableObject {
public:
    DrawableObject(const float* vertices, size_t size, int vertexCount, ShaderProgram* shader, Material* material);
    DrawableObject(const float* vertices, size_t size, int vertexCount, ShaderProgram* shader, Material* material, Texture* texture, GLuint offset);
    DrawableObject(const float* vertices, size_t size, int vertexCount, ShaderProgram* shader, Texture* texture, GLuint offset);
    ~DrawableObject();
    void draw() const;
    void draw(int a) const;
    Transformation* getTransformation();
    void setMaterial(Material* mat);

private:
    BasicModel* model;
    ShaderProgram* shaderProgram;
    Transformation* transform;
    Material* mat;
    Texture* texture;
    GLuint offset;
};
