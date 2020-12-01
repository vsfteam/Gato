#pragma once

#include "Any.h"
#include "TypeWrap.h"

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <regex>
#include <assert.h>

using StyleList = std::initializer_list<std::pair<std::string, std::string>>;

// https://developer.mozilla.org/zh-CN/docs/Web/CSS/CSS_Types

namespace ValueType
{
    class Angle
    {
    };
    class BasicShape
    {
    };
    class BlendMode
    {
    };
    class Color
    {
    public:
        unsigned char b;
        unsigned char g;
        unsigned char r;
        unsigned char a;

        Color(unsigned char _b,
              unsigned char _g,
              unsigned char _r,
              unsigned char _a) : b(_b), g(_g), r(_r), a(_a)
        {
        }
    };
    class CustomIdent
    {
    };
    class FilterFunction
    {
    };
    class Flex
    {
    };
    class Frequency
    {
    };
    class Gradient
    {
    };
    class Image
    {
    };
    class Integer
    {
    };
    class Length
    {
    public:
        double value = 0.0f;
        std::string unit;
        bool isAuto = true;
        Length() : value(0), unit("px")
        {
            isAuto = true;
        }

        Length(double v, std::string u) : value(v), unit(u)
        {
            isAuto = false;
        }
    };
    class Number
    {
    };
    class Percentage
    {
    public:
        double value;

        Percentage(double v) : value(v)
        {
        }
    };
    class Position
    {
        double vaule;
    };
    class Ratio
    {
    };
    class Resolution
    {
    };
    class ShapeBox
    {
    };
    class SingleTransitionTimingFunction
    {
    };
    class String
    {
    };
    class Time
    {
    };
    class TransformFunction
    {
    };
    class Url
    {
    };

    // Some special vlue
    class Auto
    {
    };
    class Initial
    {
    };
    class Inherit
    {
    };
    class Unset
    {
    };

} // namespace ValueType

class Style
{
private:
    std::map<std::string, Any> styleMap;

public:
    static double GetLength(std::string value)
    {
        std::smatch m;
        if (!std::regex_match(value, m, std::regex("([-+]?[0-9]+)(px)?")))
            assert(0);
        return std::stoi(m.str(1));
    }

    static double GetPercent(std::string value)
    {
        std::smatch m;
        if (!std::regex_match(value, m, std::regex("([-+]?[0-9]+)%")))
            assert(0);
        return std::stoi(m.str(1));
    }

    static ValueType::Color GetColor(std::string value)
    {
        std::smatch m;
        if (!std::regex_match(value, m, std::regex("#([0-9A-Fa-f]{6,8})"))) // TODO: 6/8
            assert(0);

        unsigned long c = std::stoul(m.str(1), 0, 16);

        if (value.size() == 7)
            return ValueType::Color(c, c >> 8, c >> 16, 255);
        else
            return ValueType::Color(c, c >> 8, c >> 16, c >> 24);
    }

    static color_t ToColorT(ValueType::Color c)
    {
        color_t color;
        color.r = c.r;
        color.g = c.g;
        color.b = c.b;
        color.a = c.a;

        return color;
    }

    bool MatchLength(std::string value)
    {
        std::regex r("([-+]?[0-9]+)(px|%)?|(auto)");
        return std::regex_match(value, r);
    }
    void Set(std::string key, std::string value)
    {
        Any v;
        if (key == "width" || key == "height")
        {
            if (value == "" || value == "auto")
                v = ValueType::Length();
            else if (std::regex_match(value, std::regex("([-+]?[0-9]+)(px)?")))
            {
                double len = GetLength(value);
                if (len < 0.0)
                    v = ValueType::Length();
                else
                    v = ValueType::Length(len, "px");
            }
            else if (std::regex_match(value, std::regex("([-+]?[0-9]+)%")))
            {
                double percent = GetPercent(value);
                if (percent < 0.0)
                    v = ValueType::Length();
                else
                    v = ValueType::Length(percent, "%");
            }
        }
        else if (key == "border-radius" || key == "border-width" || key == "padding" || key == "padding-left" || key == "padding-right" || key == "padding-top" || key == "padding-bottom" || key == "margin" || key == "margin-left" || key == "margin-right" || key == "margin-top" || key == "margin-bottom" || key == "font-size" || key == "backdrop-blur")

        {
            if (std::regex_match(value, std::regex("([-+]?[0-9]+)(px)?")))
            {
                double len = GetLength(value);
                if (len < 0.0)
                    v = ValueType::Length(0, "px"); //TODO:
                else
                    v = ValueType::Length(len, "px");
            }
        }
        else if (key == "left" || key == "top")
        {
            if (std::regex_match(value, std::regex("([-+]?[0-9]+)(px)?")))
            {
                double len = GetLength(value);
                v = ValueType::Length(len, "px");
            }
        }
        else if (key == "display")
        {
            if (std::regex_match(value, std::regex("block|inline-block|flex|inline-flex")))
            {
                v = value;
            }
        }
        else if (key == "vertical-align")
        {
            if (std::regex_match(value, std::regex("top|bottom")))
            {
                v = value;
            }
        }
        else if (key == "background-color" || key == "border-color" || key == "color")
        {
            if (std::regex_match(value, std::regex("#[0-9A-Fa-f]{6,8}")))
            {
                v = GetColor(value);
            }
        }
        else if (key == "content" || key == "background-image")
        {
            v = value;
        }
        else if (key == "justify-content")
        {
            if (std::regex_match(value, std::regex("flex-start|flex-end|center|space-between|space-around")))
            {
                v = value;
            }
        }
        else if (key == "flex-wrap")
        {
            if (std::regex_match(value, std::regex("nowrap|wrap|wrap-reverse")))
            {
                v = value;
            }
        }
        else if (key == "align-items")
        {
            if (std::regex_match(value, std::regex("flex-start|flex-end|center|baseline|stretch")))
            {
                v = value;
            }
        }
        else if (key == "align-content")
        {
            if (std::regex_match(value, std::regex("flex-start|flex-end|center|space-between|space-around|stretch")))
            {
                v = value;
            }
        }
        else if (key == "position")
        {
            if (std::regex_match(value, std::regex("static|absolute|relative|fixed")))
            {
                v = value;
            }
        }

        if (v.IsNull())
        {
            assert(0);
        }
        styleMap[key] = v;
    }

    Any Get(std::string key)
    {
        if (styleMap.find(key) != styleMap.end())
        {
            return styleMap[key];
        }
        else
        {
            if (key == "width" || key == "height")
            {
                return ValueType::Length();
            }
            else if (key == "display")
            {
                return std::string("block");
            }
            else if (key == "justify-content")
            {
                return std::string("flex-start");
            }
            else if (key == "flex-wrap")
            {
                return std::string("nowrap");
            }
            else if (key == "align-items")
            {
                return std::string("flex-start");
            }
            else if (key == "align-content")
            {
                return std::string("flex-start");
            }
            else if (key == "position")
            {
                return std::string("static");
            }
            return ValueType::Unset();
        }
    }
};