#include <GLFW/glfw3.h>
#include "platform.h"

#if defined(__APPLE_CC__)
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#else
#define AL_LIBTYPE_STATIC 1
#include <AL/al.h>
#include <AL/alc.h>
#endif

struct pc_platform : public platform
{
    GLFWwindow *Window = NULL;
    ALCdevice *ALDevice;
    ALCcontext *ALContext;
    ALuint Source = 0;
    ALuint Buffer = 0;

    virtual int Init(bool Fullscreen);
    virtual void Exit();
    virtual bool MainLoop();
    virtual void SwapBuffers();
    virtual void PlaySound(int Frequency, void *Data, int DataSizeBytes);
    virtual void ExitMainLoop();
};

int pc_platform::
Init(bool Fullscreen)
{
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_SAMPLES, 4);

    Window = glfwCreateWindow(1280, 720, "Project Meme: Tournament Edition", Fullscreen ? glfwGetPrimaryMonitor() : NULL, NULL);
    if (!Window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(Window);
    glfwSwapInterval(1);

    ALDevice = alcOpenDevice(NULL);

    if (!ALDevice)
    {
        return -1;
    }

    ALContext = alcCreateContext(ALDevice, NULL);
    alcMakeContextCurrent(ALContext);
    return 0;
}

void pc_platform::
Exit()
{
    glfwTerminate();
    alDeleteSources(1, &Source);
    alDeleteBuffers(1, &Buffer);
    ALDevice = alcGetContextsDevice(ALContext);
    alcMakeContextCurrent(NULL);
    alcDestroyContext(ALContext);
    alcCloseDevice(ALDevice);
}

bool pc_platform::
MainLoop()
{
    return !glfwWindowShouldClose(Window);
}

void pc_platform::
SwapBuffers()
{
    glfwSwapBuffers(Window);
    glfwPollEvents();
}

void pc_platform::
ExitMainLoop()
{
    glfwSetWindowShouldClose(Window, true);
}

void pc_platform::
PlaySound(int Frequency, void *Data, int DataSizeBytes)
{
    if (Source)
    {
        alDeleteSources(1, &Source);
    }

    alGenSources(1, &Source);
    alSourcef(Source, AL_PITCH, 1);
    alSourcef(Source, AL_GAIN, 1);
    alSource3f(Source, AL_POSITION, 0.0, 0.0, 0.0);
    alSource3f(Source, AL_VELOCITY, 0.0, 0.0, 0.0);
    alSourcei(Source, AL_LOOPING, AL_TRUE);

    if (Buffer)
    {
        alDeleteBuffers(1, &Buffer);
    }

    alGenBuffers(1, &Buffer);

    alBufferData(Buffer, AL_FORMAT_STEREO16, Data, DataSizeBytes, Frequency);

    alSourcei(Source, AL_BUFFER, Buffer);

    alSourcePlay(Source);
}


static platform *Platform = new pc_platform();

platform *
GetPlatform()
{
    return Platform;
}

int
GetWindowWidth()
{
    int Width, Height;
    glfwGetWindowSize(((pc_platform *)Platform)->Window, &Width, &Height);
    return Width;
}

int
GetWindowHeight()
{
    int Width, Height;
    glfwGetWindowSize(((pc_platform *)Platform)->Window, &Width, &Height);
    return Height;
}

void
GetMouseState(mouse *Mouse)
{
    double XPos, YPos;
    glfwGetCursorPos(((pc_platform *)Platform)->Window, &XPos, &YPos);
    Mouse->XPos = XPos;
    Mouse->YPos = YPos;
    Mouse->Pressed = (glfwGetMouseButton(((pc_platform *)Platform)->Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS);
}

float GetWindowAspect()
{
    return (float)GetWindowWidth() / (float)GetWindowHeight();
}


