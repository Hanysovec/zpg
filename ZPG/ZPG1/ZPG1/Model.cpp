#include "Model.h"

Model::Model(const float* vertices, size_t size, int vertexCount, int modelId) {
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);


    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    this->vertexCount = vertexCount;
    this->modelId = modelId;
}

void Model::draw() const {
    glBindVertexArray(VAO);
    glStencilFunc(GL_ALWAYS, modelId, 0xFF);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}