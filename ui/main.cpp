#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <SDL2/SDL.h>
#include "surface.h"
#include "render.h"
#include <time.h>

class Surface
{
private:
    surface_t *surface;

public:
    Surface()
    {
    }
};

class Style
{
public:
};

class GraphicObject
{
protected:
    int x, y;
    int absoluteX, absoluteY;
    int width, height;

public:
    GraphicObject() : GraphicObject(0, 0, 0, 0)
    {
        absoluteX = 0;
        absoluteY = 0;
    }
    GraphicObject(int _x, int _y, int _width, int _height)
        : x(_x), y(_y), width(_width), height(_height)
    {
        absoluteX = 0;
        absoluteY = 0;
    }
    virtual ~GraphicObject()
    {
    }

    void SetAbsolutePositon(int x, int y)
    {
        absoluteX = x;
        absoluteY = y;
    }
    int GetX()
    {
        return x;
    }
    int GetY()
    {
        return y;
    }

    int GetAbsoluteX()
    {
        return absoluteX;
    }
    int GetAbsoluteY()
    {
        return absoluteY;
    }
    virtual void Render(GraphicObject &parent, surface_t *base) = 0;
    virtual void OnEvent()
    {
    }
    virtual void OnFocus()
    {
    }
    virtual void OnUnFocus()
    {
    }
    virtual void EventCapture(bool state, int x, int y)
    {
        if ((x >= GetAbsoluteX() && x < (GetAbsoluteX() + width)) && (y >= GetAbsoluteY() && y < (GetAbsoluteY() + height)))
        {
            OnEvent();

            if (state == false) //UP
            {
                OnUnFocus();
            }
            else
            {
                OnFocus();
            }
        }
    }
};

class GraphicTreeObject : public GraphicObject
{
private:
    std::vector<std::shared_ptr<GraphicObject>> objs;

public:
    GraphicTreeObject(int x, int y, int width, int height)
        : GraphicObject(x, y, width, height)
    {
    }

    void Append(std::shared_ptr<GraphicObject> obj)
    {
        objs.push_back(obj);
    }

    void Render(GraphicObject &parent, surface_t *base)
    {
        for (auto &item : objs)
        {
            item->SetAbsolutePositon(GetAbsoluteX() + item->GetX(), GetAbsoluteY() + item->GetY());
            item->Render(*this, base);
        }
    }

    void EventCapture(bool state, int x, int y)
    {
        for (auto &item : objs)
        {
            item->EventCapture(state, x, y);
        }
        GraphicObject::EventCapture(state, x, y);
    }
};

class Rectangle : public GraphicObject
{
private:
    int radius;
    color_t fill_color;

public:
    Rectangle(int x, int y, int width, int height, int radius, color_t fill_color) : GraphicObject(x, y, width, height)
    {
        this->radius = radius;
        this->fill_color = fill_color;
    }

    void Render(GraphicObject &parent, surface_t *base)
    {
        style_t style = {
            .fill_color = fill_color,
            .border_radius = {1, 1, 1, 1},
        };
        draw_rectangle(base, GetAbsoluteX(), GetAbsoluteY(), width, height, radius, style);
    }

    void SetColor(color_t fill_color)
    {
        this->fill_color = fill_color;
    }
};

class Button : public GraphicTreeObject
{
private:
    std::shared_ptr<Rectangle> button, shadow1, shadow2;

public:
    Button(int x, int y, int width, int height) : GraphicTreeObject(x, y, width, height)
    {
        shadow2 = std::make_shared<Rectangle>(x + 5, y + 5, width, height, 10, ARGB(0x3f000000));
        shadow1 = std::make_shared<Rectangle>(x + 10, y + 10, width, height, 10, ARGB(0x3f000000));
        button = std::make_shared<Rectangle>(x, y, width, height, 10, RGB(0xff3e3e));
        Append(shadow2);
        Append(shadow1);
        Append(button);
    }

    void OnEvent()
    {
    }

    void OnFocus()
    {
        button->SetColor(RGB(0xffff3e));
    }
    void OnUnFocus()
    {
        button->SetColor(RGB(0xff3e3e));
    }
};

class Windows : public GraphicObject
{
private:
    SDL_Window *gWindow;
    SDL_Surface *gSurface;
    surface_t surface;
    GraphicTreeObject tree;
    struct timespec time;
    float fps[4] = {0};
    int fps_index = 0;

public:
    Windows(int width, int height) : tree(0, 0, width, height)
    {
        SDL_Init(SDL_INIT_VIDEO);
        gWindow = SDL_CreateWindow("Gate", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
        gSurface = SDL_GetWindowSurface(gWindow);
        surface_wrap(&surface, (color_t *)gSurface->pixels, width, height);
        clock_gettime(CLOCK_MONOTONIC, &time);
    }
    ~Windows()
    {
        SDL_DestroyWindow(gWindow);
        SDL_Quit();
    }

    void Render(GraphicObject &parent, surface_t *base)
    {
        struct timespec temp = {0, 0};
        tree.Render(*this, &surface);
        clock_gettime(CLOCK_MONOTONIC, &temp);
        unsigned long long mtime = (temp.tv_sec - time.tv_sec) * 1000000 + (temp.tv_nsec - time.tv_nsec) / 1000;
        fps[(fps_index++) % 4] = 1000000.0f / mtime;
        float cur_fps = (fps[0] + fps[1] + fps[2] + fps[3]) / 4;
        time = temp;
        // printf("fps:%f\n", cur_fps);
    }

    void UpdateWindowSurface()
    {
        surface_clear(&surface, RGB(0xffffff), 0, 0, surface.width, surface.height);
        Render(*this, &surface);
        SDL_UpdateWindowSurface(gWindow);
    }

    void Append(std::shared_ptr<GraphicObject> obj)
    {
        tree.Append(obj);
    }

    virtual void onCreate()
    {
    }
    virtual void onExit()
    {
    }

    void MainLoop()
    {
        onCreate();

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
                case SDL_MOUSEBUTTONDOWN:
                    if (e.button.button == SDL_BUTTON_LEFT)
                    {
                        std::cout << "DOWN LEFT\n";
                    }
                    else if (e.button.button == SDL_BUTTON_MIDDLE)
                    {
                        std::cout << "DOWN MIDDLE\n";
                    }
                    else if (e.button.button == SDL_BUTTON_RIGHT)
                    {
                        std::cout << "DOWN RIGHT\n";
                    }

                    tree.EventCapture(true, e.button.x, e.button.y);
                    break;
                case SDL_MOUSEBUTTONUP:
                    if (e.button.button == SDL_BUTTON_LEFT)
                    {
                        std::cout << "UP LEFT\n";
                    }
                    else if (e.button.button == SDL_BUTTON_MIDDLE)
                    {
                        std::cout << "UP MIDDLE\n";
                    }
                    else if (e.button.button == SDL_BUTTON_RIGHT)
                    {
                        std::cout << "UP RIGHT\n";
                    }

                    tree.EventCapture(false, e.button.x, e.button.y);
                    break;
                }
            }
            UpdateWindowSurface();
        }
        onExit();
    }
};

class MyWindows : public Windows
{
public:
    MyWindows() : Windows(1920, 1080)
    {
    }

    void onCreate()
    {
        Append(std::make_shared<Button>(0, 0, 200, 200));
    }

    void onExit()
    {
    }
};

int main()
{
    MyWindows().MainLoop();
    return 0;
}