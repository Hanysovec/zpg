#include "ShaderProgram.h"
#include <stdio.h>
#include "ShaderLoader.h"

/*ShaderProgram::ShaderProgram(const char* vertexShaderSrc, const char* fragmentShaderSrc) {
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

    idModelMatrix = glGetUniformLocation(id, "modelMatrix");
    if (idModelMatrix == -1) {
        fprintf(stderr, "Failed to get uniform location for modelMatrix\n");
    }
    idViewMatrix = glGetUniformLocation(id, "viewMatrix");
    if (idViewMatrix == -1) {
        fprintf(stderr, "Failed to get uniform location for viewMatrix\n");
    }
    idProjectMatrix = glGetUniformLocation(id, "projectionMatrix");
    if (idProjectMatrix == -1) {
        fprintf(stderr, "Failed to get uniform location for projectionMatrix\n");
    }
}*/
ShaderProgram::ShaderProgram(const char* vertexFile, const char* fragmentFile) {
    id = glCreateProgram();
    ShaderLoader* sLoad = new ShaderLoader(vertexFile, fragmentFile, &id);
    compiledSuccessfully = true;

    idModelMatrix = glGetUniformLocation(id, "modelMatrix");
    if (idModelMatrix == -1) {
        fprintf(stderr, "Failed to get uniform location for modelMatrix\n");
    }
    idViewMatrix = glGetUniformLocation(id, "viewMatrix");
    if (idViewMatrix == -1) {
        fprintf(stderr, "Failed to get uniform location for viewMatrix\n");
    }
    idProjectMatrix = glGetUniformLocation(id, "projectionMatrix");
    if (idProjectMatrix == -1) {
        fprintf(stderr, "Failed to get uniform location for projectionMatrix\n");
    }
    idNormalMatrix = glGetUniformLocation(id, "normalMatrix");
    if (idProjectMatrix == -1) {
        fprintf(stderr, "Failed to get uniform location for normalMatrix\n");
    }
    idViewPosition = glGetUniformLocation(id, "viewPosition");
    if (idProjectMatrix == -1) {
        fprintf(stderr, "Failed to get uniform location for viewPosition\n");
    }
    idLightPosition = glGetUniformLocation(id, "lightPosition");
    if (idProjectMatrix == -1) {
        fprintf(stderr, "Failed to get uniform location for lightPosition\n");
    }
    for (int i = 0; i < MAX_LIGHTS; i++) {
        std::string lightPosUniformName = "lightPositions[" + std::to_string(i) + "]";
        idLightPositions[i] = glGetUniformLocation(id, lightPosUniformName.c_str());
    }
    idNumLights = glGetUniformLocation(id, "numLights");
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

void ShaderProgram::sendUniform(GLint id, const glm::mat4& matrix)
{
    glUniformMatrix4fv(id, 1, GL_FALSE, &matrix[0][0]);
}

void ShaderProgram::sendUniform(GLint id, const glm::vec3& P)
{
    glUniform3fv(id, 1, &P[0]);
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
    glUniformMatrix4fv(idModelMatrix, 1, GL_FALSE, &M[0][0]);
}
void ShaderProgram::setProjectionMatrix(const glm::mat4& P) const {
    glUniformMatrix4fv(idProjectMatrix, 1, GL_FALSE, &P[0][0]);
}
void ShaderProgram::setViewMatrix(const glm::mat4& V) const {
    glUniformMatrix4fv(idViewMatrix, 1, GL_FALSE, &V[0][0]);
}
void ShaderProgram::setNormalMatrix(const glm::mat3& N) const {
    glUniformMatrix3fv(idNormalMatrix, 1, GL_FALSE, &N[0][0]);
}
void ShaderProgram::setViewPosition(const glm::vec3& C) const {
    glUniform3fv(idViewPosition, 1, &C[0]);
}
void ShaderProgram::setLightPosition(const glm::vec3& P) {
    glUniform3fv(idLightPosition, 1, &P[0]);
}
void ShaderProgram::setLightPositions(const std::vector<glm::vec3>& lightPositions) {
    int numLights = std::min(static_cast<int>(lightPositions.size()), MAX_LIGHTS);
    glUniform1i(idNumLights, numLights);
    for (int i = 0; i < numLights; i++) {
        sendUniform(idLightPositions[i], lightPositions[i]);
    }
}

void ShaderProgram::onLightUpdate(const glm::vec3& P){
    use();
    //glUniform3fv(idLightPosition, 1, &P[0]);
    sendUniform(idLightPosition, P);
    stop();
}

void ShaderProgram::onCameraUpdate(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const glm::vec3& cameraPosition) {
    use();
    /*glUniformMatrix4fv(idViewMatrix, 1, GL_FALSE, &viewMatrix[0][0]);
    glUniformMatrix4fv(idProjectMatrix, 1, GL_FALSE, &projectionMatrix[0][0]);
    glUniform3fv(idViewPosition, 1, &cameraPosition[0]);*/
    sendUniform(idViewMatrix, viewMatrix);
    sendUniform(idProjectMatrix, projectionMatrix);
    sendUniform(idViewPosition, cameraPosition);
    stop();
}
