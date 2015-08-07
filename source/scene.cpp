#include "gl.h"
#include "scene.h"


scene::
scene() : Grid(this), UIScene(this)
{

}

void scene::
Update()
{
    Grid.Update();
    UIScene.Update();
}

#include <cstdio>

void scene::
Draw()
{
    float Aspect = GetWindowAspect();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glEnable(GL_TEXTURE_2D);
    BackgroundTexture.Bind();
    if (SceneType == SCENE_MENU)
    {
        float Offset = 220.0/1024.0;
        glDisable(GL_BLEND);
        glColor4f(1, 1, 1, 1);
        glBegin(GL_QUADS);
        glTexCoord2f(0, Offset);
        glVertex2f(0, 0);
        glTexCoord2f(1, Offset);
        glVertex2f(20 * Aspect, 0);
        glTexCoord2f(1, 1.0 - Offset);
        glVertex2f(20 * Aspect, 20);
        glTexCoord2f(0, 1.0 - Offset);
        glVertex2f(0, 20);
        glEnd();

        UIScene.Draw();
    }
    else
    {
        glBegin(GL_QUADS);
        glTexCoord2f(0, 0);
        glVertex2f(0, 0);
        glTexCoord2f(1, 0);
        glVertex2f(20 * Aspect, 0);
        glTexCoord2f(1, 1);
        glVertex2f(20 * Aspect, 20);
        glTexCoord2f(0, 1);
        glVertex2f(0, 20);
        glEnd();

        {
            float TargetX = (5.0/8.0) * 20.0 * Aspect;
            float TargetWidth = (2.5/8.0) * 20.0 * Aspect;
            float TargetY = (1.0/8.0) * 20.0;

            TargetTexture.Bind();
            glBegin(GL_QUADS);
            glTexCoord2f(0, 0);
            glVertex2f(TargetX, TargetY);
            glTexCoord2f(1, 0);
            glVertex2f(TargetX + TargetWidth, TargetY);
            glTexCoord2f(1, 1);
            glVertex2f(TargetX + TargetWidth, 20);
            glTexCoord2f(0, 1);
            glVertex2f(TargetX, 20);
            glEnd();
        }

        {
            float TextX = 0.5 * Aspect;
            float TextY = (6.0/8.0) * 20.0;

            TargetScriptBox.Bind();
            glColor4f(0.5, 0.5, 0.5, 0.7);
            glBegin(GL_QUADS);
            glTexCoord2f(0, 0);
            glVertex2f(TextX, TextY);
            glTexCoord2f(1, 0);
            glVertex2f(20 * Aspect - TextX, TextY);
            glTexCoord2f(1, 1);
            glVertex2f(20 * Aspect - TextX, 19.5);
            glTexCoord2f(0, 1);
            glVertex2f(TextX, 19.5);
            glEnd();
            glColor4f(1, 1, 1, 1);
        }

        {
            float ScriptX = 0.9 * Aspect;
            float ScriptY = (6.7/8.0) * 20.0;
            glLoadIdentity();
            glTranslatef(ScriptX, ScriptY, 0.0f);
            glScalef(1.0/(20.0 * Aspect), 1.0/20.0, 1.0);
//            Print(0.0f, 0.0f, "All I had to do was smash him out; he came back! I was never used to losing and that was a");
//            Print(0.0f, 15.0f, "major shock. I can't believe I lost to my I lost to chillindude.");
        }

        {
            Grid.Draw();
        }
    }
    glPopMatrix();
}