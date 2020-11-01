#pragma once

#include "color.h"

#include <random>
#include <chrono>


class Util
{
private:
    int radius;
    color_t fill_color;
    std::mt19937 random;

public:
    color_t GetRandomColor()
    {
        std::mt19937 random = std::mt19937(std::chrono::system_clock::now().time_since_epoch().count());
        color_t c;
        c.a = 255;
        c.r = random() % 256;
        c.g = random() % 256;
        c.b = random() % 256;
        return c;
    }
};