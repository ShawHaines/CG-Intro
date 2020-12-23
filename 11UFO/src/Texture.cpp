#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Texture.h"

GLuint loadTexture(const std::string& fileName) {
    GLuint texture;
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // setting filter and wrapping method
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Very important, or the color would not be right.
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);

    // load and generate texture.
    int width, height, nrChannels;
    unsigned char *data =
        stbi_load(fileName.data(), &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                     GL_UNSIGNED_BYTE, data);
        // glGenerateMipmap(GL_TEXTURE_2D);
        std::cout<< "Texture loaded: w " << width <<", h "<<height <<std::endl;
    } else {
        std::cout << "Failed to load texture." << std::endl;
    }
    stbi_image_free(data);
    glDisable(GL_TEXTURE_2D);
    return texture;
}