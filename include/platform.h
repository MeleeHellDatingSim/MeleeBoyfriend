
#ifndef PLATFORM_H
#define PLATFORM_H


struct platform
{
    virtual int Init(bool Fullscreen) = 0;
    virtual void Exit() = 0;
    virtual bool MainLoop() = 0;
    virtual void SwapBuffers() = 0;
    virtual void PlaySound(int Frequency, void *Data, int DataSizeBytes) = 0;
    virtual void ExitMainLoop() = 0;
};

struct mouse
{
    int Pressed = 0;
    float XPos;
    float YPos;
};

platform *GetPlatform();
int GetWindowWidth();
int GetWindowHeight();
void GetMouseState(mouse *Mouse);
float GetWindowAspect();


#endif
