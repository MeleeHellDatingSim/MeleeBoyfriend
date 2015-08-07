
#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "gl.h"

struct color
{
    float R, G, B, A;
};

struct texture
{
    GLuint Id;

    void Bind();

    static texture Load(const char *Path);
};

#endif
