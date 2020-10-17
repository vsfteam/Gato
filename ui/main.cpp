#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <memory>
#include <SDL2/SDL.h>
#include "surface.h"
#include "render.h"
#include <time.h>
#include <functional>
#include <random>
#include <chrono>

#include "Style.h"
class Surface
{
private:
    surface_t *surface;

public:
    Surface()
    {
    }
};

using StyleList = std::initializer_list<std::pair<std::string, std::string>>;

class GraphicObject
{
private:
protected:
    int x = 0, y = 0;
    int absoluteX = 0, absoluteY = 0;
    int width = 0, height = 0;
    bool visiable = true;

public:
    std::vector<std::shared_ptr<GraphicObject>> children;
    Style style;
    GraphicObject() = delete;
    GraphicObject(StyleList list)
    {
        for (const auto &item : list)
        {
            style.Set(item.first, item.second);
        }
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
    void SetWidth(int width)
    {
        this->width = width;
    }
    int GetWidth()
    {
        return width;
    }
    void SetX(int x)
    {
        this->x = x;
    }
    void SetY(int y)
    {
        this->y = y;
    }
    void SetHeight(int height)
    {
        this->height = height;
    }
    int GetHeight()
    {
        return height;
    }
    void Hide()
    {
        visiable = false;
    }
    void Show()
    {
        visiable = true;
    }
    int GetAbsoluteX()
    {
        return absoluteX;
    }
    int GetAbsoluteY()
    {
        return absoluteY;
    }
    void Render(GraphicObject &parent, surface_t *base)
    {
        if (visiable)
        {
            OnRender(parent, base);
        }

        for (auto &item : children)
        {
            // std::cout << "GetAbsoluteX() + item->GetX() : " << GetAbsoluteX() + item->GetX() << ",   "
            //           << "GetAbsoluteY() + item->GetY() : " << GetAbsoluteY() + item->GetY() << ",   "
            //           << "\n";
            item->SetAbsolutePositon(GetAbsoluteX() + item->GetX(), GetAbsoluteY() + item->GetY());
            item->Render(*this, base);
        }
    }
    virtual void OnRender(GraphicObject &parent, surface_t *base)
    {
    }

    virtual void OnEvent()
    {
    }
    virtual void OnFocus()
    {
    }
    virtual void OnUnFocus()
    {
    }

    void AppendChild(std::shared_ptr<GraphicObject> obj)
    {
        children.push_back(obj);
    }
    virtual void EventCapture(bool state, int x, int y)
    {
        for (auto &item : children)
        {
            item->EventCapture(state, x, y);
        }

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

class Rectangle : public GraphicObject
{
private:
    int radius;
    color_t fill_color;
    std::mt19937 random;

public:
    color_t GetRandomColor()
    {
        color_t c;
        c.a = 255;
        c.r = random() % 256;
        c.g = random() % 256;
        c.b = random() % 256;
        return c;
    }
    Rectangle(StyleList list) : GraphicObject(list)
    {
        random = std::mt19937(std::chrono::system_clock::now().time_since_epoch().count());

        this->radius = 10;
        this->fill_color = GetRandomColor();
    }

    void OnRender(GraphicObject &parent, surface_t *base)
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

class BlockLayout
{
public:
    using GraphicObjectIterator = std::vector<std::shared_ptr<GraphicObject>>::iterator;
    int AlignInlineBlock(int height, int lineHeight, GraphicObjectIterator begin, GraphicObjectIterator end)
    {
        for (auto it = begin; it != end; it++)
        {
            std::shared_ptr<GraphicObject> item = *it;
            std::string align = item->style.Get("vertical-align");

            if (align == "" || align == "bottom")
            {
                item->SetY(height + lineHeight - item->GetHeight());
            }
            else if (align == "top")
            {
                item->SetY(height);
            }
        }
    }

    int CalcInlineBlocks(int width, int height, GraphicObjectIterator begin, GraphicObjectIterator end, GraphicObjectIterator &newBegin)
    {
        int lineHeight = 0;
        int lineWidth = 0;
        auto it = begin;
        for (; it != end; it++)
        {
            std::shared_ptr<GraphicObject> item = *it;

            if (item->style.Get("display") != "inline-block")
            {
                break;
            }
            else if (item->GetWidth() + lineWidth > width)
            {
                // Only one item in one line
                if (it == begin)
                {
                    item->SetX(0);
                    item->SetY(height);
                    return item->GetHeight();
                }
                break;
            }
            else
            {
                newBegin = it;
                item->SetX(lineWidth);
                // item->SetY(height);

                if (item->GetHeight() > lineHeight)
                {
                    lineHeight = item->GetHeight();
                }
                lineWidth += item->GetWidth();

                // std::cout << "X:" << item->GetX() << "  Y:" << item->GetY() << "\n";
            }
        }

        AlignInlineBlock(height, lineHeight, begin, it);
        return lineHeight;
    }
    // 计算block width, 和非auto height
    void ReflowForward(std::shared_ptr<GraphicObject> obj, std::shared_ptr<GraphicObject> parent, std::shared_ptr<GraphicObject> widthFixedParent, std::shared_ptr<GraphicObject> heightFixedParent, int level = 0)
    {
        std::string width = obj->style.Get("width");
        std::string height = obj->style.Get("height");
        std::string display = obj->style.Get("display");

        if (parent != nullptr)
        {
            if (width == "" || width == "auto")
            {
                if (display == "" || display == "block")
                {
                    obj->SetWidth(parent->GetWidth());
                    widthFixedParent = obj;
                }
                else
                {
                    // auto width of inline-block, depend on total width of child items
                    obj->SetWidth(0);
                }
            }
            else
            {
                auto pair = Style::GetLength(width);
                if (pair.second == "px")
                {
                    obj->SetWidth(pair.first);
                }
                else if (pair.second == "%")
                {
                    obj->SetWidth(parent->GetWidth() * pair.first / 100.0);
                }
                widthFixedParent = obj;
            }

            if (height == "" || height == "auto")
            {
            }
            else
            {
                auto pair = Style::GetLength(height);
                if (pair.second == "px")
                    obj->SetHeight(pair.first);
                else if (pair.second == "%")
                {
                    obj->SetHeight(heightFixedParent->GetHeight() * pair.first / 100.0);
                }
                heightFixedParent = obj;
            }
        }

        for (auto &item : obj->children)
        {
            ReflowForward(item, obj, widthFixedParent, heightFixedParent, level + 1);
        }

        // calc auto width of inline-block
        if (display == "inline-block" && width == "auto")
        {
            int childWidth = 0;
            for (auto &item : obj->children)
            {
                childWidth += item->GetWidth();
            }

            if (childWidth > widthFixedParent->GetWidth())
                childWidth = widthFixedParent->GetWidth();
            obj->SetWidth(childWidth);

            for (auto &item : obj->children)
            {
                std::string width = item->style.Get("width");
                if (width == "" || width == "auto")
                {
                }
                else
                {
                    auto pair = Style::GetLength(width);
                    if (pair.second == "%")
                    {
                        item->SetWidth(obj->GetWidth() * pair.first / 100.0);
                    }
                }
            }
        }

        int childHeight = 0;

        for (auto it = obj->children.begin(); it != obj->children.end(); it++)
        {
            std::shared_ptr<GraphicObject> item = *it;
            std::string display = item->style.Get("display");

            if (display == "inline-block")
            {
                childHeight += CalcInlineBlocks(obj->GetWidth(), childHeight, it, obj->children.end(), it);
            }
            else
            {
                item->SetY(childHeight);
                childHeight += item->GetHeight();
            }
        }

        if (parent != nullptr)
        {
            std::string height = obj->style.Get("height");
            if (height == "" || height == "auto")
            {
                if (obj->children.size() != 0)
                    obj->SetHeight(childHeight);
            }
        }

        for (int i = 0; i < level; i++)
            printf("\t");

        // std::cout << "w/h(" << obj->GetWidth() << "/" << obj->GetHeight() << ")\n";
    }
    void Reflow(std::shared_ptr<GraphicObject> root)
    {
        ReflowForward(root, nullptr, root, root);
    }
};

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
    Window(int width, int height)
    {
        root = std::make_shared<GraphicObject>(StyleList{{"width", std::to_string(width)}, {"height", std::to_string(height)}});
        root->SetWidth(width);
        root->SetHeight(height);
        SDL_Init(SDL_INIT_VIDEO);

        gWindow = SDL_CreateWindow("Gate", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
        gSurface = SDL_GetWindowSurface(gWindow);
        surface_wrap(&surface, (color_t *)gSurface->pixels, width, height);
        clock_gettime(CLOCK_MONOTONIC, &time);
        mutex = SDL_CreateMutex();

        SDL_SetEventFilter(FilterEvent, this);
    }

    static int FilterEvent(void *userdata, SDL_Event *e)
    {
        if (e->type == SDL_WINDOWEVENT && e->window.event == SDL_WINDOWEVENT_RESIZED)
        {
            ((Window *)userdata)->Resize(e->window.data1, e->window.data2);
            return 0;
        }
        return 1;
    }

    ~Window()
    {
        SDL_DestroyMutex(mutex);
        SDL_DestroyWindow(gWindow);
        SDL_Quit();
    }

    void Resize(int width, int height)
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
    void Render(surface_t *base)
    {
        struct timespec temp = {0, 0};
        BlockLayout().Reflow(root);
        root->Render(*root, &surface);
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
        Render(&surface);
        SDL_UpdateWindowSurface(gWindow);
    }

    void AppendChild(std::shared_ptr<GraphicObject> obj)
    {
        root->AppendChild(obj);
    }

    virtual void OnCreate()
    {
    }
    virtual void OnExit()
    {
    }

    void MainLoop()
    {
        OnCreate();

        bool running = true;
        UpdateWindowSurface();
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
                    root->EventCapture(true, e.button.x, e.button.y);
                    break;
                case SDL_MOUSEBUTTONUP:
                    root->EventCapture(false, e.button.x, e.button.y);
                case SDL_WINDOWEVENT:
                    if (e.window.event == SDL_WINDOWEVENT_RESIZED)
                    {
                        Resize(e.window.data1, e.window.data2);
                    }
                    break;
                }
            }
            // UpdateWindowSurface();
        }
        OnExit();
    }
};

class MyWindow : public Window
{
private:
public:
    MyWindow() : Window(1920, 1080) {}
    void OnCreate()
    {
        // Case 1:
        // auto obj = std::make_shared<Rectangle>(StyleList{{"width", "50%"}, {"height", "auto"}});
        // obj->AppendChild(std::make_shared<Rectangle>(StyleList{{"width", "50%"}, {"height", "30%"}}));
        // obj->AppendChild(std::make_shared<Rectangle>(StyleList{{"width", "110"}, {"height", "60"}}));
        // obj->AppendChild(std::make_shared<Rectangle>(StyleList{{"width", "130%"}, {"height", "50"}}));

        // AppendChild(obj);

        // auto obj2 = std::make_shared<Rectangle>(StyleList{{"width", "-1"}, {"height", "50"}});
        // obj2->AppendChild(std::make_shared<Rectangle>(StyleList{{"width", "50%"}, {"height", "120%"}}));

        // AppendChild(obj2);
        // AppendChild(std::make_shared<Rectangle>(StyleList{{"width", "200"}, {"height", "30%"}}));
        // AppendChild(std::make_shared<Rectangle>(StyleList{{"width", "300"}, {"height", "30"}}));

        // Case 2:
        // auto obj = std::make_shared<Rectangle>(StyleList{{"width", "50%"}, {"height", "auto"}});
        // obj->AppendChild(std::make_shared<Rectangle>(StyleList{{"display", "inline-block"}, {"width", "100"}, {"height", "10%"}}));
        // obj->AppendChild(std::make_shared<Rectangle>(StyleList{{"display", "inline-block"}, {"width", "110"}, {"height", "60"}}));
        // obj->AppendChild(std::make_shared<Rectangle>(StyleList{{"display", "inline-block"}, {"width", "100"}, {"height", "50"}}));

        // obj->AppendChild(std::make_shared<Rectangle>(StyleList{{"display", "inline-block"}, {"width", "200"}, {"height", "50"}}));
        // obj->AppendChild(std::make_shared<Rectangle>(StyleList{{"display", "inline-block"}, {"width", "300"}, {"height", "150"}}));
        // obj->AppendChild(std::make_shared<Rectangle>(StyleList{{"display", "block"}, {"width", "150"}, {"height", "60"}}));
        // obj->AppendChild(std::make_shared<Rectangle>(StyleList{{"display", "inline-block"}, {"width", "200"}, {"height", "80"}}));
        // obj->AppendChild(std::make_shared<Rectangle>(StyleList{{"display", "inline-block"}, {"width", "130%"}, {"height", "100"}}));
        // obj->AppendChild(std::make_shared<Rectangle>(StyleList{{"display", "inline-block"}, {"width", "70"}, {"height", "20"}}));
        // obj->AppendChild(std::make_shared<Rectangle>(StyleList{{"display", "inline-block"}, {"width", "80"}, {"height", "150"}}));
        // obj->AppendChild(std::make_shared<Rectangle>(StyleList{{"display", "inline-block"}, {"width", "180"}, {"height", "40"}}));
        // obj->AppendChild(std::make_shared<Rectangle>(StyleList{{"display", "block"}, {"width", "200"}, {"height", "150"}}));
        // obj->AppendChild(std::make_shared<Rectangle>(StyleList{{"display", "inline-block"}, {"width", "130"}, {"height", "60"}}));
        // obj->AppendChild(std::make_shared<Rectangle>(StyleList{{"display", "inline-block"}, {"width", "170"}, {"height", "110"}}));

        // AppendChild(obj);

        // Case 3:
        // auto obj = std::make_shared<Rectangle>(StyleList{{"display", "inline-block"}, {"width", "auto"}, {"height", "auto"}});
        // obj->AppendChild(std::make_shared<Rectangle>(StyleList{{"display", "inline-block"}, {"width", "20%"}, {"height", "20%"}}));
        // auto obj2 = std::make_shared<Rectangle>(StyleList{{"display", "inline-block"}, {"width", "auto"}, {"height", "auto"}});
        // obj2->AppendChild(std::make_shared<Rectangle>(StyleList{{"display", "inline-block"}, {"width", "20%"}, {"height", "50%"}}));
        // obj2->AppendChild(std::make_shared<Rectangle>(StyleList{{"display", "inline-block"}, {"width", "100"}, {"height", "200"}}));

        // obj->AppendChild(obj2);

        // AppendChild(obj);

        // Case 4:
        auto obj = std::make_shared<Rectangle>(StyleList{{"width", "auto"}, {"height", "auto"}});
        obj->AppendChild(std::make_shared<Rectangle>(StyleList{{"display", "inline-block"}, {"width", "100"}, {"height", "10%"}}));
        obj->AppendChild(std::make_shared<Rectangle>(StyleList{{"display", "inline-block"}, {"width", "110"}, {"height", "60"}}));
        obj->AppendChild(std::make_shared<Rectangle>(StyleList{{"display", "inline-block"}, {"width", "100"}, {"height", "50"}}));
        obj->AppendChild(std::make_shared<Rectangle>(StyleList{{"display", "inline-block"}, {"width", "10%"}, {"height", "50"}}));
        obj->AppendChild(std::make_shared<Rectangle>(StyleList{{"display", "inline-block"}, {"width", "20%"}, {"height", "30"}}));
        obj->AppendChild(std::make_shared<Rectangle>(StyleList{{"display", "inline-block"}, {"width", "100"}, {"height", "50"}}));
        obj->AppendChild(std::make_shared<Rectangle>(StyleList{{"display", "inline-block"}, {"width", "100"}, {"height", "50"}}));

        auto obj2 = std::make_shared<Rectangle>(StyleList{{"display", "inline-block"}, {"width", "40%"}, {"height", "auto"}});
        obj2->AppendChild(std::make_shared<Rectangle>(StyleList{{"display", "inline-block"}, {"width", "100"}, {"height", "50"}}));
        obj2->AppendChild(std::make_shared<Rectangle>(StyleList{{"display", "inline-block"}, {"width", "10%"}, {"height", "50"}}));
        obj2->AppendChild(std::make_shared<Rectangle>(StyleList{{"display", "inline-block"}, {"width", "20%"}, {"height", "30"}}));
        obj2->AppendChild(std::make_shared<Rectangle>(StyleList{{"display", "inline-block"}, {"width", "100"}, {"height", "50"}}));
        obj2->AppendChild(std::make_shared<Rectangle>(StyleList{{"display", "inline-block"}, {"width", "100"}, {"height", "50"}}));
        obj2->AppendChild(std::make_shared<Rectangle>(StyleList{{"display", "inline-block"}, {"width", "20%"}, {"height", "20%"}}));
        obj2->AppendChild(std::make_shared<Rectangle>(StyleList{{"display", "inline-block"}, {"width", "100"}, {"height", "20%"}}));
        obj->AppendChild(obj2);
        AppendChild(obj);
    }

    void OnExit() {}
};

#ifdef _WIN32
#include <Windows.h>  
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
#else
int main()
#endif
{
    MyWindow().MainLoop();
    return 0;
}