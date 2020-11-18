#pragma once

#include "color.h"

#include <random>
#include <chrono>


class Util
{
public:
    static color_t GetRandomColor()
    {
        static std::mt19937 random = std::mt19937(std::chrono::system_clock::now().time_since_epoch().count());
        color_t c;
        c.a = 255;
        c.r = random() % 256;
        c.g = random() % 256;
        c.b = random() % 256;
        return c;
    }
    static void SetDPIAware();
};