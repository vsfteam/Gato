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
    MyWindow() : Window(1920, 1080) {}
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

        // Case 5:
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

        // Case 6:
        // auto obj = std::make_shared<GraphicObject>(StyleList{{"width", "50"}, {"height", "50"}, {"background-color", "#134E7E"}, {"padding-left", "20px"}, {"padding-top", "50px"}});
        // AppendChild(obj);

        // Case 7:

        auto obj = std::make_shared<GraphicObject>(StyleList{{"width", "auto"}, {"height", "100%"}, {"background-color", "#1682C2"}});
        auto task_bar = std::make_shared<GraphicObject>(StyleList{{"width", "auto"}, {"height", "30"}, {"background-color", "#10ffffff"}, {"content", "Mon Jun 22 9:41 AM"}, {"font-size", "16"}, {"color", "#ffffff"}});
        auto body = std::make_shared<GraphicObject>(StyleList{{"width", "auto"}, {"height", std::to_string(502 - 30 - 10)}, {"padding-top", "10"}, {"padding-left", "42"}});
        auto content = std::make_shared<GraphicObject>(StyleList{{"display", "inline-block"}, {"width", std::to_string(335 + 14)}, {"height", "auto"}, {"background-color", "#3fffffff"}, {"border-radius", "15"}, {"padding", "7"}});
        task_bar->SetCallback("onclick", [content](std::shared_ptr<GraphicObject> obj, Any e) -> void {
            content->SetVisibility(!content->GetVisibility());
        });
        // for (int i = 0; i < 5; i++)
        {
            auto item = std::make_shared<GraphicObject>(StyleList{
                {"display", "inline-block"},
                {"width", std::to_string(335 / 2 - 8 - 14)},
                {"height", std::to_string(75 * 2)},
                {"background-color", "#4fffffff"},
                {"border-radius", "11"},
                {"padding", "7"},
                {"margin", "7"},
            });

            {
                auto item_padding = std::make_shared<GraphicObject>(StyleList{{"height", std::to_string(50 - 14)}, {"padding", "7"}});
                auto item_icon = std::make_shared<GraphicObject>(StyleList{
                    {"display", "inline-block"},
                    {"width", std::to_string(30)},
                    {"height", std::to_string(50 - 14 - 6)},
                    {"padding-top", "3"},
                    {"padding-bottom", "3"},
                });
                auto item_icon_image = std::make_shared<GraphicObject>(StyleList{
                    {"width", "30"},
                    {"height", "30"},
                    {"background-image", "res/wifi.png"},
                });
                auto item_left = std::make_shared<GraphicObject>(StyleList{{"display", "inline-block"}, {"width", "85"}, {"padding-left", "14"}, {"height", std::to_string(50 - 14)}, {"background-color", "#00ff0000"}});
                auto item_left_text1 = std::make_shared<GraphicObject>(StyleList{{"display", "inline-block"}, {"width", "80"}, {"height", std::to_string((50 - 14) / 2)}, {"content", "Wi-Fi"}, {"font-size", "16"}});
                auto item_left_text2 = std::make_shared<GraphicObject>(StyleList{{"display", "inline-block"}, {"width", "80"}, {"height", std::to_string((50 - 14) / 2)}, {"content", "Home"}, {"font-size", "12"}, {"color", "#6f000000"}});
                item_icon->AppendChild(item_icon_image);
                item_padding->AppendChild(item_icon);
                item_padding->AppendChild(item_left);
                item_left->AppendChild(item_left_text1);
                item_left->AppendChild(item_left_text2);

                item->AppendChild(item_padding);
            }
            {
                auto item_padding = std::make_shared<GraphicObject>(StyleList{{"height", std::to_string(50 - 14)}, {"padding", "7"}});
                auto item_icon = std::make_shared<GraphicObject>(StyleList{
                    {"display", "inline-block"},
                    {"width", std::to_string(30)},
                    {"height", std::to_string(50 - 14 - 6)},
                    {"padding-top", "3"},
                    {"padding-bottom", "3"},
                });
                auto item_icon_image = std::make_shared<GraphicObject>(StyleList{
                    {"width", "30"},
                    {"height", "30"},
                    {"background-image", "res/bluetooth.png"},
                });
                auto item_left = std::make_shared<GraphicObject>(StyleList{{"display", "inline-block"}, {"width", "85"}, {"padding-left", "14"}, {"height", std::to_string(50 - 14)}, {"background-color", "#00ff0000"}});
                auto item_left_text1 = std::make_shared<GraphicObject>(StyleList{{"display", "inline-block"}, {"width", "80"}, {"height", std::to_string((50 - 14) / 2)}, {"content", "Bluetooth"}, {"font-size", "16"}});
                auto item_left_text2 = std::make_shared<GraphicObject>(StyleList{{"display", "inline-block"}, {"width", "80"}, {"height", std::to_string((50 - 14) / 2)}, {"content", ""}, {"font-size", "12"}, {"color", "#6f000000"}});
                item_icon->AppendChild(item_icon_image);

                item_padding->AppendChild(item_icon);
                item_padding->AppendChild(item_left);
                item_left->AppendChild(item_left_text1);
                item_left->AppendChild(item_left_text2);

                item->AppendChild(item_padding);
            }
            {
                auto item_padding = std::make_shared<GraphicObject>(StyleList{{"height", std::to_string(50 - 14)}, {"padding", "7"}});
                auto item_icon = std::make_shared<GraphicObject>(StyleList{
                    {"display", "inline-block"},
                    {"width", std::to_string(30)},
                    {"height", std::to_string(50 - 14 - 6)},
                    {"padding-top", "3"},
                    {"padding-bottom", "3"},
                });
                auto item_icon_image = std::make_shared<GraphicObject>(StyleList{
                    {"width", "30"},
                    {"height", "30"},
                    {"background-image", "res/wifi.png"},
                });
                auto item_left = std::make_shared<GraphicObject>(StyleList{{"display", "inline-block"}, {"width", "85"}, {"padding-left", "14"}, {"height", std::to_string(50 - 14)}, {"background-color", "#00ff0000"}});
                auto item_left_text1 = std::make_shared<GraphicObject>(StyleList{{"display", "inline-block"}, {"width", "80"}, {"height", std::to_string((50 - 14) / 2)}, {"content", "AirDop"}, {"font-size", "16"}});
                auto item_left_text2 = std::make_shared<GraphicObject>(StyleList{{"display", "inline-block"}, {"width", "80"}, {"height", std::to_string((50 - 14) / 2)}, {"content", "Contacts Only"}, {"font-size", "12"}, {"color", "#6f000000"}});
                item_icon->AppendChild(item_icon_image);
                item_padding->AppendChild(item_icon);
                item_padding->AppendChild(item_left);
                item_left->AppendChild(item_left_text1);
                item_left->AppendChild(item_left_text2);

                item->AppendChild(item_padding);
            }
            content->AppendChild(item);
        }
        {
            auto parent = std::make_shared<GraphicObject>(StyleList{{"display", "inline-block"}, {"width", std::to_string(335 / 2 + 8)}});
            {
                auto item = std::make_shared<GraphicObject>(StyleList{
                    {"display", "inline-block"},
                    {"width", std::to_string(335 / 2 - 8 - 14 - 14)},
                    {"height", std::to_string(75 - 14 - 14)},
                    {"background-color", "#4fffffff"},
                    {"border-radius", "11"},
                    {"padding", "14"},
                    {"margin", "7"},
                });
                {
                    auto item_icon = std::make_shared<GraphicObject>(StyleList{{"display", "inline-block"}, {"width", std::to_string(30)}, {"height", std::to_string(50 - 14)}, {"background-color", "#ff0000"}});
                    auto item_left = std::make_shared<GraphicObject>(StyleList{{"display", "inline-block"}, {"width", "85"}, {"padding-left", "14"}, {"height", std::to_string(50 - 14)}, {"background-color", "#00ff0000"}});
                    auto item_left_text1 = std::make_shared<GraphicObject>(StyleList{{"display", "inline-block"}, {"width", "80"}, {"height", std::to_string((50 - 14) / 2)}, {"content", "Do not"}, {"font-size", "16"}});
                    auto item_left_text2 = std::make_shared<GraphicObject>(StyleList{{"display", "inline-block"}, {"width", "80"}, {"height", std::to_string((50 - 14) / 2)}, {"content", "Distrub"}, {"font-size", "16"}});

                    item->AppendChild(item_icon);
                    item->AppendChild(item_left);
                    item_left->AppendChild(item_left_text1);
                    item_left->AppendChild(item_left_text2);
                }
                parent->AppendChild(item);
            }
            {
                auto item = std::make_shared<GraphicObject>(StyleList{
                    {"display", "inline-block"},
                    {"width", std::to_string((335 / 2 - 8) / 2 - 8 - 14 - 14)},
                    {"height", std::to_string(75 - 14 - 14)},
                    {"background-color", "#4fffffff"},
                    {"border-radius", "11"},
                    {"padding", "14"},
                    {"margin", "7"},
                });

                {
                    auto item_icon = std::make_shared<GraphicObject>(StyleList{{"width", "auto"}, {"height", std::to_string(25)}, {"background-color", "#ff0000"}});
                    auto item_text = std::make_shared<GraphicObject>(StyleList{{"width", "auto"}, {"height", std::to_string(35)}, {"content", "Keyboard"}, {"font-size", "12"}});
                    item->AppendChild(item_icon);
                    item->AppendChild(item_text);
                }

                parent->AppendChild(item);
            }
            {
                auto item = std::make_shared<GraphicObject>(StyleList{
                    {"display", "inline-block"},
                    {"width", std::to_string((335 / 2 - 8) / 2 - 8 - 14 - 14)},
                    {"height", std::to_string(75 - 14 - 14)},
                    {"background-color", "#4fffffff"},
                    {"border-radius", "11"},
                    {"padding", "14"},
                    {"margin", "7"},
                });

                {
                    auto item_icon = std::make_shared<GraphicObject>(StyleList{{"width", "auto"}, {"height", std::to_string(25)}, {"background-color", "#ff0000"}});
                    auto item_text = std::make_shared<GraphicObject>(StyleList{{"width", "auto"}, {"height", std::to_string(35)}, {"content", "Keyboard"}, {"font-size", "12"}});
                    item->AppendChild(item_icon);
                    item->AppendChild(item_text);
                }

                parent->AppendChild(item);
            }
            content->AppendChild(parent);
        }
        {
            auto item = std::make_shared<GraphicObject>(StyleList{
                {"display", "inline-block"},
                {"width", std::to_string(335 - 14 - 14)},
                {"height", std::to_string(75 - 14 - 14)},
                {"background-color", "#4fffffff"},
                {"border-radius", "11"},
                {"padding", "14"},
                {"margin", "7"}});

            {
                auto item_text = std::make_shared<GraphicObject>(StyleList{
                    {"width", "auto"},
                    {"height", std::to_string(20)},
                    {"content", "Sound"},
                    {"font-size", "16"},
                });
                auto item_slider = std::make_shared<GraphicObject>(StyleList{
                    {"width", "auto"},
                    {"height", std::to_string(25)},
                    {"background-color", "#20000000"},
                    {"border-radius", std::to_string(25 / 2)},
                });
                {
                    auto item_slider_white = std::make_shared<GraphicObject>(StyleList{
                        {"width", "200"},
                        {"height", std::to_string(25)},
                        {"background-color", "#ffffff"},
                        {"border-radius", std::to_string(25 / 2)},
                    });
                    auto item_icon = std::make_shared<GraphicObject>(StyleList{
                        {"display", "inline-block"},
                        {"width", std::to_string(25)},
                        {"height", std::to_string(25)},
                        {"background-color", "#ff0000"},
                    });
                    auto item_space = std::make_shared<GraphicObject>(StyleList{
                        {"display", "inline-block"},
                        {"width", std::to_string(200 - 25)},
                        {"height", std::to_string(25)},
                    });
                    auto item_icon_end = std::make_shared<GraphicObject>(StyleList{
                        {"display", "inline-block"},
                        {"width", std::to_string(25)},
                        {"height", std::to_string(25)},
                        {"background-color", "#4f000000"},
                        {"border-radius", std::to_string(25 / 2)},
                    });
                    item_space->AppendChild(item_icon);
                    item_slider->AppendChild(item_slider_white);
                    item_slider_white->AppendChild(item_space);
                    item_slider_white->AppendChild(item_icon_end);

                    item_slider->SetCallback("ondragover", [item_slider_white, item_space](std::shared_ptr<GraphicObject> obj, Any e) -> void {
                        auto pair = e.AnyCast<std::pair<int, int>>();
                        int offset = pair.first - item_slider_white->GetAbsoluteX();
                        offset = std::min(std::max(offset, 12), obj->GetWidth() - 12);
                        item_slider_white->SetStyle("width", std::to_string(25 + offset - 12));
                        item_space->SetStyle("width", std::to_string(offset - 12));
                    });
                }

                item->AppendChild(item_text);
                item->AppendChild(item_slider);
            }
            content->AppendChild(item);
        }
        {
            auto parent = std::make_shared<GraphicObject>(StyleList{{"display", "inline-block"}, {"padding", "7"}});
            auto item = std::make_shared<GraphicObject>(StyleList{
                {"display", "inline-block"},
                {"width", "335"},
                {"height", "75"},
                {"background-color", "#4fffffff"},
                {"border-radius", "11"},
            });
            item->AddTransiton("height", 0.3, 1, .53, .7, 1.51, 1);
            parent->AppendChild(item);
            content->AppendChild(parent);
            item->SetCallback("onclick", [](std::shared_ptr<GraphicObject> obj, Any e) -> void {
                if (obj->GetStyle("height").AnyCast<ValueType::Length>().value == 75)
                    obj->SetStyle("height", std::to_string(100));
                else
                    obj->SetStyle("height", std::to_string(75));
            });
        }

        {
            auto parent = std::make_shared<GraphicObject>(StyleList{{"display", "inline-block"}, {"padding", "7"}, {"height", "300px"}});
            for (int i = 0; i < 4; i++)
            {
                auto item = std::make_shared<GraphicObject>(StyleList{
                    {"display", "inline-block"},
                    {"width", "75"},
                    {"height", "75"},
                    {"background-color", "#4fffffff"},
                    {"border-radius", "11"},
                });
                parent->AppendChild(item);
            }

            content->AppendChild(parent);
        }
        // auto obj = std::make_shared<GraphicObject>(StyleList{{"width", "auto"}, {"height", "100%"}, {"background-color", "#ff0000"}});
        obj->AppendChild(task_bar);
        obj->AppendChild(body);
        body->AppendChild(content);
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