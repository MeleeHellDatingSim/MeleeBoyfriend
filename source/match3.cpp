#include "gl.h"
#include "match3.h"
#include "platform.h"
#include "graphics.h"

color ColorTable[8] =
{
    { 1.0, 0.0, 0.0, 1.0 },
    { 1.0, 0.0, 0.0, 1.0 },
    { 0.0, 0.0, 1.0, 1.0 },
    { 0.0, 0.0, 1.0, 1.0 },
    { 0.0, 1.0, 0.0, 1.0 },
    { 0.0, 1.0, 0.0, 1.0 },
    { 0.917647, 0.678431, 0.917647, 1.0 },
    { 0.917647, 0.678431, 0.917647, 1.0 },
};

void match3_grid::
Update()
{

}

void match3_grid::
Draw()
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    float Aspect = GetWindowAspect();
    float GridX = (1.0/8.0) * 20.0 * Aspect;
    float GridY = (1.0/8.0) * 20.0;

    glTranslatef(GridX, GridY, 0.0);
    glDisable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    for (int Y = 0; Y < 10; ++Y)
    {
        for (int X = 0; X < 10; ++X)
        {
            if (PickedSlot - (X + Y * 10))
            {
                color Color = ColorTable[Slots[X + Y * 10] & 0b111];
                glColor3f(Color.R, Color.G, Color.B);
                glVertex2i(X, Y);
                glVertex2i(X + 1, Y);
                glVertex2i(X + 1, Y + 1);
                glVertex2i(X, Y + 1);
            }
            else
            {

            }
        }
    }
    glEnd();
    glColor4f(1, 1, 1, 1);
    glPopMatrix();
}