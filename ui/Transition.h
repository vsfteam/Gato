#pragma once

#include "Any.h"
#include "Style.h"

#include <string>
#include <chrono>
#include <cmath>

enum class TransitonState
{
    READY,
    RUN,
    RESUME
};

class GraphicObject;

using std::chrono::milliseconds;
using std::chrono::steady_clock;

class TransitonReact
{
protected:
    std::weak_ptr<GraphicObject> obj;
    std::string property;

public:
    TransitonReact(std::shared_ptr<GraphicObject> o, std::string _property)
        : obj(o), property(_property)
    {
    }
    void SetGraphicObject(std::shared_ptr<GraphicObject> o)
    {
        obj = o;
    }

    void SetProperty(std::string _property)
    {
        property = _property;
    }
    virtual ~TransitonReact(){};
    virtual void OnReady() {}
    virtual void OnRun() {}
    virtual void OnResume() {}
    virtual void OnStop() {}

    virtual void OnUpdate(double ratio) {}
};

class Transiton
{
public:
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
    std::unique_ptr<TransitonReact> react;

private:
    double CubizBezierRecursive(double t, double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3);
    double CubizBezier(double t);
    void ChangeState(TransitonState newState);

public:
    Transiton();
    Transiton(std::shared_ptr<GraphicObject> o, std::string _property, double _duration, double _x1, double _y1, double _x2, double _y2, double _delay);

    void SetReact(TransitonReact *p)
    {
        react.reset(p);
    }

    void Update();
    void Run();
};

class LengthTransiton : public TransitonReact
{
private:
    ValueType::Length beginVal;
    ValueType::Length endVal;
    ValueType::Length curVal;
public:
    LengthTransiton(std::shared_ptr<GraphicObject> o, std::string property);
    void OnReady();
    void OnRun();
    void OnResume();

    void OnUpdate(double ratio);
};
#include "GraphicObject.h"