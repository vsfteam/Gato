#pragma once
#include "surface.h"
#include "GraphicObject.h"

#include <memory.h>
#include <time.h>

struct SDL_Window;
struct SDL_Surface;
struct SDL_mutex;
union SDL_Event;

class Window
{
private:
    SDL_Window *gWindow;
    SDL_Surface *gSurface;
    surface_t surface;
    std::shared_ptr<GraphicObject> root;
    struct timespec time;
    float fps[4] = {0};
    int fps_index = 0;
    SDL_mutex *mutex;

public:
    Window(int width, int height);
    ~Window();


    void Resize(int width, int height);
    void Render(surface_t *base);

    void UpdateWindowSurface();
    void AppendChild(std::shared_ptr<GraphicObject> obj);
    virtual void OnCreate();
    virtual void OnExit();
    void MainLoop();
};