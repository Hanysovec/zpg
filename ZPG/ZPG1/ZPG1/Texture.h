#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <SOIL.h>
#include <string>

class Texture {
public:
    Texture(const char* filePath);
    Texture(const char* filePath, const char* filePath2, const char* filePath3, const char* filePath4, const char* filePath5, const char* filePath6);
    ~Texture();
    GLuint getID() const;
private:
    GLuint textureID;
};

