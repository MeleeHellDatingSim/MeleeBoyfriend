
#include <cstdio>
#include <stdlib.h>
#include "font.h"
#include "platform.h"
#include "gl.h"

font::
font(const char *Path, float Height)
{
    FILE *File = fopen(Path, "rb");
    fseek (File, 0, SEEK_END);
    unsigned int Size = ftell(File);
    rewind(File);
    unsigned char *TTFBuffer = (unsigned char *)malloc(Size);
    fread(TTFBuffer, 1, Size, File);

    fclose(File);
    unsigned char *TempBitmap = (unsigned char *)malloc(512*512);
    FontHeight = Height;
    stbtt_BakeFontBitmap((unsigned char*)TTFBuffer,0, FontHeight, TempBitmap,512,512, 32,96, BakedCData); // no guarantee this fits!
    // can free ttf_buffer at this point
    glGenTextures(1, &Texture.Id);
    Texture.Bind();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, 512,512, 0, GL_ALPHA, GL_UNSIGNED_BYTE, TempBitmap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // can free temp_bitmap at this point

    free(TTFBuffer);
    free(TempBitmap);

}


void font::
DrawString(float XOffset, float YOffset, float CharScale, const char *String)
{
    // assume orthographic projection with units = screen pixels, origin at top left
    glEnable(GL_TEXTURE_2D);
//    glEnable(GL_BLEND);
    Texture.Bind();
    glBegin(GL_QUADS);
    while (*String) {
        if (*String >= 32 && (unsigned char)(*String) < 128) {
            stbtt_aligned_quad q;
            stbtt_GetBakedQuad(BakedCData, 512,512, *String-32, &XOffset,&YOffset,&q,1);//1=opengl & d3d10+,0=d3d9
            glTexCoord2f(q.s0,q.t0); glVertex2f(q.x0,q.y0);
            glTexCoord2f(q.s1,q.t0); glVertex2f(q.x1,q.y0);
            glTexCoord2f(q.s1,q.t1); glVertex2f(q.x1,q.y1);
            glTexCoord2f(q.s0,q.t1); glVertex2f(q.x0,q.y1);
        }
        ++String;
    }
    glEnd();
}


float font::
GetStringWidth(const char *String, float CharScale)
{
    int total = 0;
    while (*String) {
        if (*String >= 32 && (unsigned char)(*String) < 128) {
            total += BakedCData[*String-32].xadvance;
        }
        ++String;
    }

    return ((float)total) / (20.0 * GetWindowAspect());
}

float font::
GetCharHeight(float CharScale)
{
    return FontHeight / (20.0 * GetWindowAspect());
}

