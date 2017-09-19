
#ifndef SCENE_H
#define SCENE_H

#include "graphics.h"
#include "platform.h"
#include "match3.h"
#include "ui_core.h"

enum
{
    SCENE_MENU,
    SCENE_VENUE
};

struct scene
{
    mouse Mouse;
    match3_grid Grid;
    int SceneType;
    ui_scene UIScene;
    texture BackgroundTexture;
    texture TargetTexture;
    texture TargetScriptBox;
    //script TargetScript;

    scene();
    void Update();
    virtual void Draw();
};

#endif
