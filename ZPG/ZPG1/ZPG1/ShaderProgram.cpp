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
    idSpotLightPosition = glGetUniformLocation(id, "spotLightPosition");
    if (idProjectMatrix == -1) {
        fprintf(stderr, "Failed to get uniform location for spotLightPosition\n");
    }
    idSpotLightDirection = glGetUniformLocation(id, "spotLightDirection");
    if (idProjectMatrix == -1) {
        fprintf(stderr, "Failed to get uniform location for spotLightDirection\n");
    }
    idSpotLightInCutOff = glGetUniformLocation(id, "spotLightInnerCutOff");
    if (idProjectMatrix == -1) {
        fprintf(stderr, "Failed to get uniform location for spotLightInnerCutOff\n");
    }
    idSpotLightOutCutOff = glGetUniformLocation(id, "spotLightOuterCutOff");
    if (idProjectMatrix == -1) {
        fprintf(stderr, "Failed to get uniform location for spotLightOuterCutOff\n");
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
void ShaderProgram::setSpotlight(const glm::vec3& position, const glm::vec3& direction, float spotLightInnerCutOff, float spotLightOuterCutOff)
{
    sendUniform(idSpotLightDirection, direction);
    sendUniform(idSpotLightPosition, position);
    sendUniform(idSpotLightInCutOff, spotLightInnerCutOff);
    sendUniform(idSpotLightOutCutOff, spotLightOuterCutOff);
}

void ShaderProgram::update(Subject* subject)
{
    Camera* camera = dynamic_cast<Camera*>(subject);
    if (camera) {
        use();
        sendUniform(idViewMatrix, camera->getViewMatrix());
        sendUniform(idProjectMatrix, camera->getProjectionMatrix());
        sendUniform(idViewPosition, camera->getPosition());
        stop();
    }
    LightSource* light = dynamic_cast<LightSource*>(subject);
    if (light) {
        use();
        sendUniform(idLightPosition, light->getPosition());
        stop();
    }
    SpotLight* spotLight = dynamic_cast<SpotLight*>(subject); 
    if (spotLight) {
        use();
        sendUniform(idSpotLightDirection, spotLight->getDirection());
        sendUniform(idSpotLightPosition, spotLight->getPosition());
        glUniform1f(idSpotLightInCutOff, spotLight->getInnerCutOff());
        glUniform1f(idSpotLightOutCutOff, spotLight->getOuterCutOff());
        stop();
    }
}
