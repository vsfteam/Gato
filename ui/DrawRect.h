#pragma once

#include "color.h"
#include "render.h"

#include <string>
#include <vector>

class DrawRect
{
private:
    int width = 0;
    int height = 0;
    int x = 0;
    int y = 0;
    float radius = 0;
    float border_width = 0;
    color_t background_color;
    color_t border_color;
    std::vector<shadow_t> shadows;

public:
    DrawRect()
    {
        background_color = ARGB(0);
        border_color = ARGB(0);
    }

    void Set(int w, int h, int x, int y, color_t c)
    {
        width = w;
        height = h;
        this->x = x;
        this->y = y;
        background_color = c;
    }

    void SetBorder(float r, float w, color_t c)
    {
        radius = r;
        border_width = w;
        border_color = c;
    }

    void SetShadow(std::vector<shadow_t> s)
    {
        shadows = s;
    }
    void OnDraw(surface_t *base)
    {

        style_t style = {0};
        style.fill_color = background_color;
        style.stroke_color = border_color;
        style.stroke_width = border_width;
        style.border_radius[0] = 1;
        style.border_radius[1] = 1;
        style.border_radius[2] = 1;
        style.border_radius[3] = 1;

        if (!shadows.empty())
        {
            style.n_shadow = shadows.size();
        }

        std::unique_ptr<shadow_t[]> s(new shadow_t[shadows.size()]);
        std::copy(shadows.begin(), shadows.end(), s.get());
        style.shadow = s.get();
        draw_rectangle(base, x, y, width, height, radius, style);
    }
};
