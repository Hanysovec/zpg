#include "SkyboxModel.h"

SkyboxModel::SkyboxModel(const float* vertices, size_t size, int vertexCount)
{
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);


    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    this->vertexCount = vertexCount;
}

void SkyboxModel::draw() const
{
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    glClear(GL_DEPTH_BUFFER_BIT);
}
