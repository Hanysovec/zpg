#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Shader.h"
#include "Observer.h"
#include "Camera.h"
#include "LightSource.h"
#include "SpotLight.h"
#define MAX_LIGHTS 10

class ShaderProgram : public Observer{ //udelat base shaderProgram at neposilam lightPos atd. pro konstantni shader
public:
    ShaderProgram(const char* vertexShaderSrc, const char* fragmentShaderSrc);
    void use() const;
    void stop() const;
    bool isCompiledSuccessfully() const;
    void setModelMatrix(const glm::mat4& modelMatrix) const;
    void setProjectionMatrix(const glm::mat4& projectionMatrix) const;
    void setViewMatrix(const glm::mat4& viewMatrix) const;
    void setNormalMatrix(const glm::mat3& normalMatrix) const;
    void setViewPosition(const glm::vec3& C) const;
    void setLightPosition(const glm::vec3& P);
    void setLightPositions(const std::vector<glm::vec3>& lightPositions);
    void setSpotlight(const glm::vec3& position, const glm::vec3& direction, float spotLightInnerCutOff, float spotLightOuterCutOff);
    void update(Subject* subject);

private:
    GLuint id;
    bool compiledSuccessfully;
    GLint idModelMatrix;
    GLint idProjectMatrix;
    GLint idViewMatrix;
    GLint idNormalMatrix;
    GLint idViewPosition;
    GLint idLightPosition;
    GLint idLightPositions[MAX_LIGHTS];
    GLint idNumLights;
    GLint idSpotLightPosition;
    GLint idSpotLightDirection;
    GLint idSpotLightInCutOff;
    GLint idSpotLightOutCutOff;
    void linkProgram();
    void sendUniform(GLint id, const glm::mat4& matrix);
    void sendUniform(GLint id, const glm::vec3& P);
};
