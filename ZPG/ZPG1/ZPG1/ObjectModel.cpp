#include "ObjectModel.h"

ObjectModel::ObjectModel(ModelLoader::Vertex* model, int vertexCount, unsigned int* pIndices, unsigned int mNumVertices, int modelId)
{
    this->vertexCount = vertexCount;
    this->pIndices = pIndices;
    this->model = model;
    this->modelId = modelId;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(ModelLoader::Vertex)*mNumVertices, this->model, GL_STATIC_DRAW);

    glGenVertexArrays(1, &VAO);
    if (VAO == 0) {
        printf("VAO was not generated correctly.\n");
        exit(EXIT_FAILURE);
    }
    glBindVertexArray(VAO);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ModelLoader::Vertex), (GLvoid*)(0));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(ModelLoader::Vertex), (GLvoid*)(3 * sizeof(GLfloat)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(ModelLoader::Vertex), (GLvoid*)(6 * sizeof(GLfloat)));
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * this->vertexCount, this->pIndices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(VAO);
}

void ObjectModel::draw() const
{
    glBindVertexArray(VAO);
    glStencilFunc(GL_ALWAYS, modelId, 0xFF);
    glDrawElements(GL_TRIANGLES, this->vertexCount, GL_UNSIGNED_INT, NULL);
}
