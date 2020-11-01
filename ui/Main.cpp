#include "Style.h"
#include "Window.h"

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <memory>

class MyWindow : public Window
{
private:
public:
    MyWindow() : Window(810, 850) {}
    void OnCreate()
    {
        // Case 1:
        // auto obj = std::make_shared<GraphicObject>(StyleList{{"width", "50%"}, {"height", "auto"}});
        // obj->AppendChild({{"width", "50%"}, {"height", "30%"}});
        // obj->AppendChild({{"width", "110"}, {"height", "60"}});
        // obj->AppendChild({{"width", "130%"}, {"height", "50"}});

        // AppendChild(obj);

        // auto obj2 = std::make_shared<GraphicObject>(StyleList{{"width", "-1"}, {"height", "50"}});
        // obj2->AppendChild({{"width", "50%"}, {"height", "120%"}});

        // AppendChild(obj2);
        // AppendChild({{"width", "200"}, {"height", "30%"}}));
        // AppendChild({{"width", "300"}, {"height", "30"}}));

        // Case 2:
        // auto obj = std::make_shared<GraphicObject>(StyleList{{"width", "50%"}, {"height", "auto"}});
        // obj->AppendChild({{"display", "inline-block"}, {"width", "100"}, {"height", "10%"}});
        // obj->AppendChild({{"display", "inline-block"}, {"width", "110"}, {"height", "60"}});
        // obj->AppendChild({{"display", "inline-block"}, {"width", "100"}, {"height", "50"}});

        // obj->AppendChild({{"display", "inline-block"}, {"width", "200"}, {"height", "50"}});
        // obj->AppendChild({{"display", "inline-block"}, {"width", "300"}, {"height", "150"}});
        // obj->AppendChild({{"display", "block"}, {"width", "150"}, {"height", "60"}});
        // obj->AppendChild({{"display", "inline-block"}, {"width", "200"}, {"height", "80"}});
        // obj->AppendChild({{"display", "inline-block"}, {"width", "130%"}, {"height", "100"}});
        // obj->AppendChild({{"display", "inline-block"}, {"width", "70"}, {"height", "20"}});
        // obj->AppendChild({{"display", "inline-block"}, {"width", "80"}, {"height", "150"}});
        // obj->AppendChild({{"display", "inline-block"}, {"width", "180"}, {"height", "40"}});
        // obj->AppendChild({{"display", "block"}, {"width", "200"}, {"height", "150"}}));
        // obj->AppendChild({{"display", "inline-block"}, {"width", "130"}, {"height", "60"}});
        // obj->AppendChild({{"display", "inline-block"}, {"width", "170"}, {"height", "110"}});

        // AppendChild(obj);

        // Case 3:
        // auto obj = std::make_shared<GraphicObject>(StyleList{{"display", "inline-block"}, {"width", "auto"}, {"height", "auto"}});
        // obj->AppendChild({{"display", "inline-block"}, {"width", "20%"}, {"height", "20%"}});
        // auto obj2 = std::make_shared<GraphicObject>(StyleList{{"display", "inline-block"}, {"width", "auto"}, {"height", "auto"}});
        // obj2->AppendChild({{"display", "inline-block"}, {"width", "20%"}, {"height", "50%"}});
        // obj2->AppendChild({{"display", "inline-block"}, {"width", "100"}, {"height", "200"}});

        // obj->AppendChild(obj2);

        // AppendChild(obj);

        // Case 4:
        // auto obj = std::make_shared<GraphicObject>(StyleList{{"width", "auto"}, {"height", "auto"}});
        // obj->AppendChild({{"display", "inline-block"}, {"width", "100"}, {"height", "10%"}});
        // obj->AppendChild({{"display", "inline-block"}, {"width", "110"}, {"height", "60"}});
        // obj->AppendChild({{"display", "inline-block"}, {"width", "100"}, {"height", "50"}});
        // obj->AppendChild({{"display", "inline-block"}, {"width", "10%"}, {"height", "50"}});
        // obj->AppendChild({{"display", "inline-block"}, {"width", "20%"}, {"height", "30"}});
        // obj->AppendChild({{"display", "inline-block"}, {"width", "100"}, {"height", "50"}});
        // obj->AppendChild({{"display", "inline-block"}, {"width", "100"}, {"height", "50"}});

        // auto obj2 = std::make_shared<GraphicObject>(StyleList{{"display", "inline-block"}, {"width", "40%"}, {"height", "auto"}});
        // obj2->AppendChild({{"display", "inline-block"}, {"width", "100"}, {"height", "50"}});
        // obj2->AppendChild({{"display", "inline-block"}, {"width", "10%"}, {"height", "50"}});
        // obj2->AppendChild({{"display", "inline-block"}, {"width", "20%"}, {"height", "30"}});
        // obj2->AppendChild({{"display", "inline-block"}, {"width", "100"}, {"height", "50"}});
        // obj2->AppendChild({{"display", "inline-block"}, {"width", "100"}, {"height", "50"}});
        // obj2->AppendChild({{"display", "inline-block"}, {"width", "20%"}, {"height", "20%"}});
        // obj2->AppendChild({{"display", "inline-block"}, {"width", "100"}, {"height", "20%"}});
        // obj->AppendChild(obj2);
        // AppendChild(obj);

        // Case 4:
        // auto obj = std::make_shared<GraphicObject>(StyleList{{"width", "50"}, {"height", "50"}, {"background-color", "#134E7E"}});

        // obj->AddTransiton(Transiton("width", 1, 1, 0.31, 0, 1.69, 1));
        // obj->AddTransiton(Transiton("height", 1, 1, 0.31, 0, 1.69, 1));
        // obj->SetOnClickCallback([](std::shared_ptr<GraphicObject> obj) -> void {
        //     int h = obj->GetStyle("width").AnyCast<ValueType::Length>().value;
        //     if (h == 50)
        //     {
        //         obj->SetStyle("width", "300");
        //     }
        //     else
        //     {
        //         obj->SetStyle("width", "50");
        //     }
        // });
        // AppendChild(obj);

        // Case 5:
        // auto obj = std::make_shared<GraphicObject>(StyleList{{"width", "50"}, {"height", "50"}, {"background-color", "#134E7E"}, {"padding-left", "20px"}, {"padding-top", "50px"}});
        // AppendChild(obj);

        // Case 6:
        auto obj = std::make_shared<GraphicObject>(StyleList{{"width", "auto"}, {"height", "100%"}});
        auto body = std::make_shared<GraphicObject>(StyleList{{"width", "auto"}, {"height", "800"}});
        body->AppendChild({{"display", "inline-block"}, {"width", "0"}, {"height", "100%"}});

        auto menu = std::make_shared<GraphicObject>(StyleList{{"display", "inline-block"}, {"width", "auto"}, {"height", "0"}, {"background-color", "#134E7E"}, {"vertical-align", "bottom"}});
        auto left = std::make_shared<GraphicObject>(StyleList{{"display", "inline-block"}, {"width", "60"}, {"height", "100%"}});
        auto center = std::make_shared<GraphicObject>(StyleList{{"display", "inline-block"}, {"width", "280"}, {"height", "100%"}});
        auto right = std::make_shared<GraphicObject>(StyleList{{"display", "inline-block"}, {"width", std::to_string(470 - 20)}, {"height", std::to_string(800 - 61)}, {"padding-left", "20px"}, {"padding-top", "61"}});

        for (int i = 0; i < 7; i++)
        {
            left->AppendChild(
                {
                    {"width", "60"},
                    {"height", "60"},
                    {"background-color", "#2D2D30"},
                });
        }

        for (int i = 0; i < 7; i++)
        {
            auto layout = std::make_shared<GraphicObject>(StyleList{
                {"height", "50"},
                {"padding-left", "2px"},
                {"padding-right", "2px"},
                {"padding-top", "2px"},
                {"padding-bottom", "2px"},
            });
            layout->AppendChild(
                {
                    {"display", "inline-block"},
                    {"width", "40"},
                    {"height", "40"},
                    {"background-color", "#2D2D30"},
                });
            layout->AppendChild(
                {
                    {"display", "inline-block"},
                    {"width", "200"},
                    {"height", "40"},
                    {"background-color", "#ff0000"},
                });
            center->AppendChild(layout);
        }

        for (int i = 0; i < 7; i++)
        {
            right->AppendChild(
                {
                    {"display", "inline-block"},
                    {"width", "125"},
                    {"height", "125"},
                    {"background-color", "#2D2D30"},
                    {"border-color", "#ffffff"},
                    {"border-width", "2px"},
                    {"border-radius", "0px"},
                });
        }

        menu->AddTransiton(Transiton("height", 0.3, 1, .53, .7, 1.51, 1));
        menu->Hide();
        menu->AppendChild(left);
        menu->AppendChild(center);
        menu->AppendChild(right);

        body->AppendChild(menu);
        obj->AppendChild(body);
        auto taskBar = std::make_shared<GraphicObject>(StyleList{{"width", "auto"}, {"height", "50"}});
        auto rect1 = std::make_shared<GraphicObject>(StyleList{{"display", "inline-block"}, {"width", "60"}, {"height", "50"}, {"background-color", "#ff0000"}});
        taskBar->AppendChild(rect1);
        rect1->SetOnClickCallback([menu](std::shared_ptr<GraphicObject> obj) -> void {
            if (menu->GetStyle("height").AnyCast<ValueType::Length>().value != 800)
            {
                menu->SetStyle("height", "800");
                menu->Show();
            }
            else
            {
                menu->SetStyle("height", "50");
                menu->Hide();
            }
            printf("Y:%d\n", menu->GetY());
        });
        // rect2->SetOnClickCallback([menu](std::shared_ptr<GraphicObject> obj) -> void {
        //     menu->Show();
        // });
        obj->AppendChild(taskBar);
        AppendChild(obj);
    }

    void OnExit() {}
};

#ifdef _WIN32
#include <Windows.h>
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
#else
int main()
#endif
{
    MyWindow().MainLoop();
    return 0;
}