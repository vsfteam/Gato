#pragma once

#include "color.h"
#include "surface.h"
#include "image.h"
#include "render.h"

#include <string>

class DrawText
{
private:
    int width = 0;
    int height = 0;
    int x = 0;
    int y = 0;
    color_t color;
    std::string text;
    double fontSize;

public:
    DrawText()
    {
        color = ARGB(0);
    }

    void Set(int w, int h, int x, int y, color_t c, double _fontSize, std::string _text)
    {
        width = w;
        height = h;
        this->x = x;
        this->y = y;
        color = c;
        text = _text;
        fontSize = _fontSize;
    }

    void OnDraw(surface_t *base)
    {
        if (!text.empty())
        {
            surface_t *s = surface_alloc(width, height);
            draw_text(s, 0, 0, text.c_str(), fontSize, color);
            surface_blit(base, s, x, y);
            surface_free(s);
        }
    }
};
