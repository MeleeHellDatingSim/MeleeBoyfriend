
#include "ui_core.h"
#include "scene.h"
#include "platform.h"

ui_scene::
ui_scene(scene *TheScene) : Scene(TheScene)
{
    
}

void ui_scene::
Add(ui_element *element)
{
    elements.push_back(element);
}

void ui_scene::
Remove(ui_element *element)
{

}

static bool
MouseIsInBox(mouse *Mouse, float X0, float Y0, float X1, float Y1)
{
    float MX = Mouse->XPos;
    float MY = Mouse->YPos;
    if (MX < X0) return false;
    if (MX > X1) return false;
    if (MY < Y0) return false;
    if (MY > Y1) return false;
    return true;
}

void ui_scene::
Update()
{
    mouse *Mouse = &Scene->Mouse;
    bool CallOnClick = false;
    if (!MouseButtonClicked  && Mouse->Pressed)
    {
        MouseButtonClicked = true;
    }
    if (MouseButtonClicked && !Mouse->Pressed)
    {
        CallOnClick = true;
        MouseButtonClicked = false;
    }

    if (Mouse)
    for (auto e : elements)
    {
        float X0 = e->XPosition - ((e->Width * e->BBXScale) / 2.0);
        float X1 = e->XPosition + ((e->Width * e->BBXScale) / 2.0);
        float Y0 = e->YPosition - ((e->Height * e->BBYScale) / 2.0);
        float Y1 = e->YPosition + ((e->Height * e->BBYScale) / 2.0);
        bool IsInside = MouseIsInBox(Mouse, X0, Y0, X1, Y1);

        if (e->MouseWasOver && !IsInside)
        {
            e->OnMouseExit();
            e->MouseWasOver = false;
        }
        else if (!e->MouseWasOver && IsInside)
        {
            e->OnMouseEnter();
            e->MouseWasOver = true;
        }

        if (IsInside && CallOnClick)
        {
            e->OnClick();
        }
    }
}

void ui_scene::
Draw()
{
    for (auto e : elements)
    {
        e->Draw();
    }
}