#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Shader.h"
#include "Observer.h"
#include "Camera.h"

class ShaderProgram : public Observer{
public:
    ShaderProgram(const char* vertexShaderSrc, const char* fragmentShaderSrc);
    void use() const;
    void stop() const;
    bool isCompiledSuccessfully() const;
    void setModelMatrix(const glm::mat4& modelMatrix) const;
    void setProjectionMatrix(const glm::mat4& projectionMatrix) const;
    void setViewMatrix(const glm::mat4& viewMatrix) const;
    void onCameraUpdate(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const glm::vec3& cameraPosition);
    void setNormalMatrix(const glm::mat3& normalMatrix) const;
    void setViewPosition(const glm::vec3& C) const;
    void onLightUpdate(const glm::vec3& P);
    void setLightPosition(const glm::vec3& P);

private:
    GLuint id;
    bool compiledSuccessfully;
    GLint idModelMatrix;
    GLint idProjectMatrix;
    GLint idViewMatrix;
    GLint idNormalMatrix;
    GLint idViewPosition;
    GLint idLightPosition;
    void linkProgram();
};
