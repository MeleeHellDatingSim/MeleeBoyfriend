
#include "graphics.h"
#include "gl.h"
#include "stb_image.h"


void texture::
Bind()
{
    glBindTexture(GL_TEXTURE_2D, Id);
}

texture texture::
Load(const char* Path) {
    GLuint Name;
    glGenTextures(1, &Name);
    glBindTexture(GL_TEXTURE_2D, Name);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int Width, Height, Comp;
    unsigned char* ImageData = stbi_load(Path, &Width, &Height, &Comp, 4);
    if (!ImageData)
    {
        printf("Image Load Error\n");
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, ImageData);
    stbi_image_free(ImageData);
    printf("GL_ERROR: %d\n", glGetError());
    texture Texture = {};
    Texture.Id = Name;
    return Texture;
}