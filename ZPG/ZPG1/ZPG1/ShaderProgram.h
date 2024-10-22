#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Shader.h"
#include "Observer.h"

class ShaderProgram : public Observer{
public:
    ShaderProgram(const char* vertexShaderSrc, const char* fragmentShaderSrc);
    void use() const;
    void stop() const;
    bool isCompiledSuccessfully() const;
    void setModelMatrix(const glm::mat4& modelMatrix) const;
    void setProjectionMatrix(const glm::mat4& projectionMatrix) const;
    void setViewMatrix(const glm::mat4& viewMatrix) const;
    void onCameraUpdate(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);

private:
    GLuint id;
    bool compiledSuccessfully;
    GLint idModelTransform;
    GLint idProjectMatrix;
    GLint idViewMatrix;
    void linkProgram();
};
