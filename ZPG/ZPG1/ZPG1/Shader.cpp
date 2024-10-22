#include "Shader.h"
#include <stdio.h>

bool Shader::attachShader(const char* source, GLenum shaderType, GLuint programID) {
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        checkCompilationErrors(shader);
        return false;
    }

    glAttachShader(programID, shader);
    glDeleteShader(shader);
    return true;
}

void Shader::checkCompilationErrors(GLuint shader) {
    char infoLog[512];
    glGetShaderInfoLog(shader, 512, NULL, infoLog);
    fprintf(stderr, "Shader compilation failed: %s\n", infoLog);
}
