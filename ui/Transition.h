#pragma once

#include "Any.h"

#include <string>
#include <chrono>
#include <cmath>

enum class TransitonState
{
    READY,
    RUN,
    STOP
};

class GraphicObject;

using std::chrono::milliseconds;
using std::chrono::steady_clock;

class Transiton
{
public:
    std::string property;
    double duration = 0;
    std::string timingFunc;
    double delay = 0;
    double x1 = 0;
    double y1 = 0;
    double x2 = 0;
    double y2 = 0;
    TransitonState state = TransitonState::READY;
    double progress = 0;
    std::chrono::steady_clock::time_point start;
    std::chrono::steady_clock::time_point end;

    Any beginVal;
    Any endVal;
    Any curVal;

public:
    Transiton() = default;
    Transiton(std::string _property, double _duration, std::string _timingFunc, double _delay);
    Transiton(std::string _property, double _duration, double _x1, double _y1, double _x2, double _y2, double _delay);

    double CubizBezierRecursive(double t, double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3);
    double CubizBezier(double t);
    void Update(GraphicObject &obj);
    void Run(GraphicObject &obj);
    void Init(Any styleVal);
};

#include "GraphicObject.h"