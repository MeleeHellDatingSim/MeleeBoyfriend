#include <3ds.h>
#include <gfx_device.h>
#include "platform.h"

struct n3ds_platform : public platform
{
    void *Context;
    bool Running;
//    ALCdevice *ALDevice;
//    ALCcontext *ALContext;
//    ALuint Source = 0;
//    ALuint Buffer = 0;

    virtual int Init(bool Fullscreen);
    virtual void Exit();
    virtual bool MainLoop();
    virtual void SwapBuffers();
    virtual void PlaySound(int Frequency, void *Data, int DataSizeBytes);
    virtual void ExitMainLoop();
};

int n3ds_platform::
Init(bool Fullscreen)
{
    Running = true;
    srvInit();
    aptInit();
    hidInit(NULL);
    gfxInitDefault();
    Context = gfxCreateDevice(240, 320);
    gfxMakeCurrent(Context);
    return 0;
}

void n3ds_platform::
Exit()
{
    gfxExit();
    hidExit();
    aptExit();
    srvExit();
//    glfwTerminate();
//    alDeleteSources(1, &Source);
//    alDeleteBuffers(1, &Buffer);
//    ALDevice = alcGetContextsDevice(ALContext);
//    alcMakeContextCurrent(NULL);
//    alcDestroyContext(ALContext);
//    alcCloseDevice(ALDevice);
}

bool n3ds_platform::
MainLoop()
{
    return aptMainLoop() && Running;
}

void n3ds_platform::
SwapBuffers()
{
    gfxFlush(gfxGetFramebuffer(GFX_BOTTOM, GFX_LEFT, NULL, NULL));
    gfxFlushBuffers();
    gfxSwapBuffersGpu();
    gspWaitForVBlank();
}

void n3ds_platform::
ExitMainLoop()
{
    Running = false;
}

void n3ds_platform::
PlaySound(int Frequency, void *Data, int DataSizeBytes)
{
//    if (Source)
//    {
//        alDeleteSources(1, &Source);
//    }
//
//    alGenSources(1, &Source);
//    alSourcef(Source, AL_PITCH, 1);
//    alSourcef(Source, AL_GAIN, 1);
//    alSource3f(Source, AL_POSITION, 0.0, 0.0, 0.0);
//    alSource3f(Source, AL_VELOCITY, 0.0, 0.0, 0.0);
//    alSourcei(Source, AL_LOOPING, AL_FALSE);
//
//    if (Buffer)
//    {
//        alDeleteBuffers(1, &Buffer);
//    }
//
//    alGenBuffers(1, &Buffer);
//
//    alBufferData(Buffer, AL_FORMAT_STEREO16, Data, DataSizeBytes, Frequency);
//
//    alSourcei(Source, AL_BUFFER, Buffer);
//
//    alSourcePlay(Source);
}


static platform *Platform = new n3ds_platform();

platform *
GetPlatform()
{
    return Platform;
}

int
GetWindowWidth()
{
    return 320;
}

int
GetWindowHeight()
{
    return 240;
}

void
GetMouseState(mouse *Mouse)
{
//    double XPos, YPos;
//    glfwGetCursorPos(((pc_platform *)Platform)->Window, &XPos, &YPos);
//    Mouse->XPos = XPos;
//    Mouse->YPos = YPos;
//    Mouse->Pressed = (glfwGetMouseButton(((pc_platform *)Platform)->Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS);

    touchPosition touch;
    hidTouchRead(&touch);

    Mouse->XPos = touch.px;
    Mouse->YPos = touch.py;

    hidScanInput();
    Mouse->Pressed = (hidKeysDown() & KEY_TOUCH) != 0;
}

float GetWindowAspect()
{
    return (float)GetWindowWidth() / (float)GetWindowHeight();
}


