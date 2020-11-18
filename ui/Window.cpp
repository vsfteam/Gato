#include "Window.h"
#include "Layout.h"
#include "Util.h"

#include <time.h>
#include <SDL2/SDL.h>

static int FilterEvent(void *userdata, SDL_Event *e)
{
    if (e->type == SDL_WINDOWEVENT && e->window.event == SDL_WINDOWEVENT_RESIZED)
    {
        ((Window *)userdata)->Resize(e->window.data1, e->window.data2);
        return 0;
    }
    return 1;
}

Window::Window(int width, int height)
{
    root = std::make_shared<GraphicObject>(StyleList{{"width", std::to_string(width)}, {"height", std::to_string(height)}});
    root->SetWidth(width);
    root->SetHeight(height);
    Util::SetDPIAware();

    SDL_Init(SDL_INIT_VIDEO);

    gWindow = SDL_CreateWindow("Gate", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
    gSurface = SDL_GetWindowSurface(gWindow);
    surface_wrap(&surface, (color_t *)gSurface->pixels, width, height);
    clock_gettime(CLOCK_MONOTONIC, &time);
    mutex = SDL_CreateMutex();

    SDL_SetEventFilter(FilterEvent, this);
}

Window::~Window()
{
    SDL_DestroyMutex(mutex);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}

void Window::Resize(int width, int height)
{
    SDL_LockMutex(mutex);
    SDL_SetWindowSize(gWindow, width, height);
    gSurface = SDL_GetWindowSurface(gWindow);

    surface_wrap(&surface, (color_t *)gSurface->pixels, width, height);

    root->style.Set("width", std::to_string(width));
    root->style.Set("height", std::to_string(height));

    root->SetWidth(width);
    root->SetHeight(height);
    UpdateWindowSurface();
    SDL_UnlockMutex(mutex);
}
void Window::Render(surface_t *base)
{
    struct timespec temp = {0, 0};
    root->Render(*root, &surface);
    clock_gettime(CLOCK_MONOTONIC, &temp);
    unsigned long long mtime = (temp.tv_sec - time.tv_sec) * 1000000 + (temp.tv_nsec - time.tv_nsec) / 1000;
    fps[(fps_index++) % 4] = 1000000.0f / mtime;
    float cur_fps = (fps[0] + fps[1] + fps[2] + fps[3]) / 4;
    time = temp;
    // printf("fps:%f\n", cur_fps);
}

void Window::UpdateWindowSurface()
{
    surface_clear(&surface, RGB(0xffffff), 0, 0, surface.width, surface.height);
    Render(&surface);
    SDL_UpdateWindowSurface(gWindow);
}

void Window::AppendChild(std::shared_ptr<GraphicObject> obj)
{
    root->AppendChild(obj);
}

void Window::OnCreate()
{
}
void Window::OnExit()
{
}

void Window::MainLoop()
{
    OnCreate();
    BlockLayout::Reflow(root);

    bool running = true;
    while (running)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_MOUSEMOTION:
                root->EventCapture(EVENT_TYPE::MOUSE_MOTION, e.button.x, e.button.y);
                break;
            case SDL_MOUSEBUTTONDOWN:
                root->EventCapture(EVENT_TYPE::MOUSE_BTN_DOWN, e.button.x, e.button.y);
                break;
            case SDL_MOUSEBUTTONUP:
                root->EventCapture(EVENT_TYPE::MOUSE_BTN_UP, e.button.x, e.button.y);
                break;
            case SDL_WINDOWEVENT:
                if (e.window.event == SDL_WINDOWEVENT_RESIZED)
                {
                    Resize(e.window.data1, e.window.data2);
                }
                break;
            }
        }
        root->UpdateTranstion();
        BlockLayout().Reflow(root);

        UpdateWindowSurface();
    }
    OnExit();
}