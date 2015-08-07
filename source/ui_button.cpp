
#include "ui_core.h"

void ui_button::
Draw()
{
    float X = XPosition - (Width / 2.0);
    float Y = YPosition - (Height / 2.0);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    DefaultTexture.Bind();
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex2f(X, Y);
    glTexCoord2f(1, 0);
    glVertex2f(X + Width, Y);
    glTexCoord2f(1, 1);
    glVertex2f(X + Width, Y + Height);
    glTexCoord2f(0, 1);
    glVertex2f(X, Y + Height);
    glEnd();

    ui_label::Draw();
}