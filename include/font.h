
#ifndef FONT_H
#define FONT_H
#include "graphics.h"
#include "stb_truetype.h"

class font
{
    stbtt_bakedchar BakedCData[96];
    texture Texture;
    float FontHeight;
public:
    font(const char *Path, float Height = 32.0);
    void DrawString(float XOffset, float YOffset, float CharScale, const char *String);
    float GetStringWidth(const char *String, float CharScale);
    float GetCharHeight(float CharScale);
};


#endif
