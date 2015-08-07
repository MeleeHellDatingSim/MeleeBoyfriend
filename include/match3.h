
#ifndef MATCH3_H
#define MATCH3_H

enum
{
    M3_ITEM_RED = 1,
    M3_ITEM_BLUE = 2,
    M3_ITEM_GREEN = 4,
    M3_ITEM_PURPLE = 8
};

struct scene;

struct match3_grid
{
    int Slots[10 * 10];
    int PickedSlot = -1;
    float PickedX;
    float PickedY;
    int ScoreCurrent;
    int ScoreTarget;
    scene *Scene;

    match3_grid(scene *TheScene) : Scene(TheScene)
    {

    }

    void Update();
    void Draw();
};


#endif
