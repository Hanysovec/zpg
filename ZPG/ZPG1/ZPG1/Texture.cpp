#include "Texture.h"
Texture::Texture(const char* filePath) {
    textureID = SOIL_load_OGL_texture(
        filePath,
        SOIL_LOAD_RGBA,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );

    if (textureID == 0) {
        fprintf(stderr, "Failed to load texture.\n");
        printf(SOIL_last_result());
        printf("\n");
    }

}

Texture::Texture(const char* filePath, const char* filePath2, const char* filePath3, const char* filePath4, const char* filePath5, const char* filePath6)
{
    textureID = SOIL_load_OGL_cubemap(
        filePath,
        filePath2,
        filePath3,
        filePath4,
        filePath5,
        filePath6,
        SOIL_LOAD_RGBA,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS
    );

    if (textureID == 0) {
        fprintf(stderr, "Failed to load texture.\n");
        printf(SOIL_last_result());
        printf("\n");
    }
}

Texture::~Texture() {
    glDeleteTextures(1, &textureID);
}


GLuint Texture::getID() const {
    return textureID; 
}