#ifndef UI_CORE_H
#define UI_CORE_H

#include <vector>
#include "graphics.h"
#include "font.h"

struct scene;

extern font *UIDefaultFont;

class ui_element
{

public:
    bool MouseWasOver = false;
    float BBXScale = 1.0;
    float BBYScale = 1.0;
    float XPosition, YPosition;
    float Width, Height;
    color Color = { 1, 1, 1, 1 };

    void SetPosition(float X, float Y)
    {
        XPosition = X;
        YPosition = Y;
    }

    void SetColor(float R, float G, float B, float A)
    {
        Color = { R, G, B, A };
    }

    virtual void OnMouseExit() = 0;
    virtual void OnMouseEnter() = 0;
    virtual void OnClick() = 0;
    virtual void Draw() = 0;
};

class ui_scene
{
    scene *Scene;
    std::vector<ui_element *> elements;
    bool MouseButtonClicked = false;
public:

    ui_scene(scene *TheScene);
    void Add(ui_element *element);
    void Remove(ui_element *element);
    void Update();
    void Draw();
};


class ui_label : public ui_element
{
private:
    const char *LabelText;
    font *Font = UIDefaultFont;
public:
    ui_label(const char *str = nullptr);
    void SetFont(font *NewFont);
    void SetText(const char *str);
    virtual void OnMouseExit() {}
    virtual void OnMouseEnter() {}
    virtual void OnClick() {}
    virtual void Draw();
};

class ui_button : public ui_label
{
public:
    texture DefaultTexture;

    ui_button(const char *str = nullptr) : ui_label(str) {}

    virtual void Draw();
};


#endif
