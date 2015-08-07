#include "ui_core.h"
#include "platform.h"

font *UIDefaultFont = nullptr;

ui_label::
ui_label(const char *str)
{
    LabelText = str;
}

void Print(float X, float Y, const char *Text);

void ui_label::
Draw()
{
    float Aspect = GetWindowAspect();
    glPushMatrix();
    glLoadIdentity();
    glColor4f(Color.R, Color.G, Color.B, Color.A);
    float X = XPosition;
    float Y = YPosition;
    float HalfWidth = Font->GetStringWidth(LabelText, 0.0) / 2.0;
    float HalfHeight = Font->GetCharHeight(0.0) / 2.0;
    glTranslatef(X - HalfWidth, Y + HalfHeight, 0.0);
    glScalef(1.0/(20.0 * Aspect), 1.0/20.0, 1.0);
    Font->DrawString(0.0, 0.0, 0.0, LabelText);
    glColor4f(1, 1, 1, 1);
    glPopMatrix();
}

void ui_label::
SetFont(font *NewFont)
{
    Font = NewFont;
}

void ui_label::
SetText(const char *str)
{
    LabelText = str;
}