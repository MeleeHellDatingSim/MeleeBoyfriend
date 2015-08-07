
#include <stdint.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>

#include "platform.h"
#include "stb_image.h"
#include "stb_truetype.h"
#include "stb_vorbis.h"
#include "graphics.h"
#include "match3.h"
#include "scene.h"
#include "font.h"
#include "gl.h"

void
RandomizeGrid(match3_grid *Grid)
{
    int *Slots = Grid->Slots;
    for (int Y = 0; Y < 10; ++Y)
    {
        for (int X = 0; X < 10; ++X)
        {
            Slots[X + Y * 10] = 1 << (rand() % 3);
        }
    }
}

void
FixMouseCoords(mouse *MouseState)
{
    float XPos = MouseState->XPos / (float)GetWindowWidth();
    float YPos = MouseState->YPos / (float)GetWindowHeight();

    float Aspect = (float)GetWindowWidth()/(float)GetWindowHeight();
    float XTrans = 20.0 * Aspect;
    float YTrans = 20.0;
    MouseState->XPos = XPos * XTrans;
    MouseState->YPos = YPos * YTrans;
}

void
InitDefaults()
{
    UIDefaultFont = new font("assets/fonts/mplus-2p-regular.ttf");
}

class menu_button : public ui_button
{
    bool Highlight = false;
public:
    texture HighlightTexture;

    menu_button(const char *String = nullptr) : ui_button(String)
    {

    }

    virtual void Draw();
    virtual void OnMouseEnter();
    virtual void OnMouseExit();
};

void menu_button::
Draw()
{
    float X = XPosition - (Width / 2.0);
    float Y = YPosition - (Height / 2.0);
    if (Highlight)
    {
        glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_TRUE);
        glBlendFunc(GL_ONE_MINUS_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glDisable(GL_BLEND);
        glEnable(GL_TEXTURE_2D);
        glColor4f(1, 1, 1, 1);
        HighlightTexture.Bind();
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
        glEnable(GL_BLEND);

        glBlendFunc(GL_ONE_MINUS_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        color TempColor = Color;
        Color = { 1, 1, 1, 1 };
        ui_label::Draw();
        Color = TempColor;



        glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_FALSE);

        glBlendFunc(GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA);
        HighlightTexture.Bind();
        glColor4f(1, 1, 1, 1);
    }
    else
    {
        
        DefaultTexture.Bind();
        glColor4f(1, 1, 1, 0.67f);
    }

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
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
    glColor4f(1, 1, 1, 1);

    if (Highlight)
    {
        glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    }
    else
    {
        glEnable(GL_STENCIL_TEST);
        glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
        glDepthMask(GL_FALSE);
        glStencilFunc(GL_NEVER, 1, 0xFF);
        glStencilOp(GL_REPLACE, GL_KEEP, GL_KEEP);
        glStencilMask(0xFF);

//        ui_label::Draw();
        float XOff = Width - Width * 1.0;
        float YOff = Height - Height * 0.71;
        glBegin(GL_QUADS);
        glVertex2f(X + XOff, Y + YOff);
        glVertex2f(X + Width - XOff, Y + YOff);
        glVertex2f(X + Width - XOff, Y + Height - YOff);
        glVertex2f(X + XOff, Y + Height - YOff);
        glEnd();

        glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
        glDepthMask(GL_TRUE);
        glStencilMask(0x00);

        glStencilFunc(GL_EQUAL, 1, 0xFF);
        ui_label::Draw();
        glDisable(GL_STENCIL_TEST);
    }
}

void menu_button::
OnMouseEnter()
{
    Highlight = true;
}

void menu_button::
OnMouseExit()
{
    Highlight = false;
}


const char *OptFullscreenString = "-fullscreen";

#ifdef _3DS
#include <3ds.h>
#include <unistd.h>
#endif

int main(int argc, char **argv)
{
    bool Fullscreen = false;
    for (int i = 1; i < argc; ++i)
    {
        if (strncmp(argv[i], OptFullscreenString, strlen(OptFullscreenString)) == 0)
        {
            Fullscreen = true;
        }
    }

    platform *Platform = GetPlatform();
    if (Platform->Init(Fullscreen))
    {
        printf("wat\n");
    }
#ifdef _3DS
    if (argc > 0) {
        chdir(argv[0]);
    }
    consoleInit(GFX_TOP, NULL);
    printf("Project Meme: Tournament Edition\n");
#endif
    InitDefaults();

    int Channels;
    int SampleRate;
    short *SampleData;
    int Samples = stb_vorbis_decode_filename("assets/Melee_Acoustic_2.ogg", &Channels, &SampleRate, &SampleData);
    Platform->PlaySound(SampleRate, SampleData, 2 * Samples * 2);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float Aspect = (float)GetWindowWidth()/(float)GetWindowHeight();

#ifdef _3DS
    glOrtho(0, 1, 1, 0, -1, 1);
    glTranslatef(0.5f, 0.5f, 0.0f);
    glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
    glTranslatef(-0.5f, -0.5f, 0.0f);
    glScalef(1.0 / (20.0 * Aspect), 1.0 / 20.0, 1.0);
#else
    glOrtho(0, 20 * Aspect, 20, 0, -1, 1);
#endif

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    scene MainScene = {};
    MainScene.BackgroundTexture = texture::Load("assets/Background_Menu.png");
    MainScene.SceneType = SCENE_MENU;
//    MainScene.TargetTexture = texture::Load("assets/ken.png");
//    MainScene.TargetScriptBox = texture::Load("assets/Button_Gray.png");

    font *ArimoFont = new font("assets/fonts/Arimo-BoldItalic.ttf", 44.0);

    texture ButtonDefault = texture::Load("assets/Button_Melee.png");
    texture ButtonHighlight = texture::Load("assets/Button_Melee_Highlight.png");

    menu_button *NewGameButton = new menu_button("New Game");
    NewGameButton->DefaultTexture = ButtonDefault;
    NewGameButton->HighlightTexture = ButtonHighlight;
    NewGameButton->Width = 15.0;
    NewGameButton->Height = 4.0;
    NewGameButton->BBYScale = 0.65;
    NewGameButton->BBXScale = 0.8;
    NewGameButton->SetPosition(10.0, 7.2);
    NewGameButton->SetFont(ArimoFont);
    NewGameButton->SetColor(252.0/255.0, 201.0/255.0, 0.0, 0.67);

    MainScene.UIScene.Add(NewGameButton);

    menu_button *LoadGameButton = new menu_button("Load Game");
    LoadGameButton->DefaultTexture = ButtonDefault;
    LoadGameButton->HighlightTexture = ButtonHighlight;
    LoadGameButton->Width = 15.0;
    LoadGameButton->Height = 4.0;
    LoadGameButton->BBYScale = 0.65;
    LoadGameButton->BBXScale = 0.8;
    LoadGameButton->SetPosition(8.5, 10.0);
    LoadGameButton->SetFont(ArimoFont);
    LoadGameButton->SetColor(252.0/255.0, 201.0/255.0, 0.0, 0.67);

    MainScene.UIScene.Add(LoadGameButton);

    menu_button *SettingsButton = new menu_button("Options");
    SettingsButton->DefaultTexture = ButtonDefault;
    SettingsButton->HighlightTexture = ButtonHighlight;
    SettingsButton->Width = 15.0;
    SettingsButton->Height = 4.0;
    SettingsButton->BBYScale = 0.65;
    SettingsButton->BBXScale = 0.8;
    SettingsButton->SetPosition(10.0, 12.8);
    SettingsButton->SetFont(ArimoFont);
    SettingsButton->SetColor(252.0/255.0, 201.0/255.0, 0.0, 0.67);

    MainScene.UIScene.Add(SettingsButton);

    class : public menu_button
    {
    public:

        virtual void OnClick()
        {
            platform *Platform = GetPlatform();
            Platform->ExitMainLoop();
        }

    } QuitButton;
    QuitButton.SetText("Exit");
    QuitButton.DefaultTexture = ButtonDefault;
    QuitButton.HighlightTexture = ButtonHighlight;
    QuitButton.Width = 15.0;
    QuitButton.Height = 4.0;
    QuitButton.BBYScale = 0.65;
    QuitButton.BBXScale = 0.8;
    QuitButton.SetPosition(9.0, 15.6);
    QuitButton.SetFont(ArimoFont);
    QuitButton.SetColor(252.0/255.0, 201.0/255.0, 0.0, 0.67);

    MainScene.UIScene.Add(&QuitButton);

    ui_button *MBLogo = new ui_button("");
    MBLogo->DefaultTexture = texture::Load("assets/meleedat_logo.png");
    MBLogo->Width = 20.0;
    MBLogo->Height = 10.0;
    MBLogo->SetPosition(15.0 * Aspect, 10.0);

    MainScene.UIScene.Add(MBLogo);

//    RandomizeGrid(&MainScene.Grid);
    while (Platform->MainLoop())
    {
        GetMouseState(&MainScene.Mouse);
        FixMouseCoords(&MainScene.Mouse);

        MainScene.Update();

        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();

        MainScene.Draw();

        Platform->SwapBuffers();
    }

    Platform->Exit();
}

