#include "ShaderProgram.h"
#include <stdio.h>

ShaderProgram::ShaderProgram(const char* vertexShaderSrc, const char* fragmentShaderSrc) {
    id = glCreateProgram();

    bool vertexSuccess = Shader::attachShader(vertexShaderSrc, GL_VERTEX_SHADER, id);
    bool fragmentSuccess = Shader::attachShader(fragmentShaderSrc, GL_FRAGMENT_SHADER, id);

    if (vertexSuccess && fragmentSuccess) {
        linkProgram();
        compiledSuccessfully = true;
    }
    else {
        compiledSuccessfully = false;
    }

    idModelTransform = glGetUniformLocation(id, "modelMatrix");
    if (idModelTransform == -1) {
        fprintf(stderr, "Failed to get uniform location for modelMatrix\n");
    }
    idViewMatrix = glGetUniformLocation(id, "viewMatrix");
    if (idViewMatrix == -1) {
        fprintf(stderr, "Failed to get uniform location for viewMatrix\n");
    }
    else {
        fprintf(stderr, ":)\n");
    }
    idProjectMatrix = glGetUniformLocation(id, "projectionMatrix");
    if (idProjectMatrix == -1) {
        fprintf(stderr, "Failed to get uniform location for projectionMatrix\n");
    }
}

void ShaderProgram::linkProgram() {
    glLinkProgram(id);

    GLint success;
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(id, 512, NULL, infoLog);
        fprintf(stderr, "Program linking failed: %s\n", infoLog);
        compiledSuccessfully = false;
    }
}

void ShaderProgram::use() const {
    glUseProgram(id);
}

void ShaderProgram::stop() const {
    glUseProgram(0);
}

bool ShaderProgram::isCompiledSuccessfully() const {
    return compiledSuccessfully;
}

void ShaderProgram::setModelMatrix(const glm::mat4& M) const {
    glUniformMatrix4fv(idModelTransform, 1, GL_FALSE, &M[0][0]);
}
void ShaderProgram::setProjectionMatrix(const glm::mat4& P) const {
    glUniformMatrix4fv(idProjectMatrix, 1, GL_FALSE, &P[0][0]);
}
void ShaderProgram::setViewMatrix(const glm::mat4& V) const {
    glUniformMatrix4fv(idViewMatrix, 1, GL_FALSE, &V[0][0]);
}

void ShaderProgram::onCameraUpdate(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
    use();
    glUniformMatrix4fv(idViewMatrix, 1, GL_FALSE, &viewMatrix[0][0]);
    glUniformMatrix4fv(idProjectMatrix, 1, GL_FALSE, &projectionMatrix[0][0]);
    stop();
}
