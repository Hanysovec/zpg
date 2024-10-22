#pragma once
#include <GL/glew.h>

class Shader {
public:
    static bool attachShader(const char* source, GLenum shaderType, GLuint programID);

private:
    static void checkCompilationErrors(GLuint shader);
};
