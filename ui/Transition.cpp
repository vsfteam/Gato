#include "Transition.h"

Transiton::Transiton()
{
}

Transiton::Transiton(std::shared_ptr<GraphicObject> o, std::string property, double _duration, double _x1, double _y1, double _x2, double _y2, double _delay)
    : duration(_duration),
      x1(_x1),
      y1(_y1),
      x2(_x2),
      y2(_y2),
      delay(_delay)
{
    if (property == "width" || property == "height")
    {
        react.reset(new LengthTransiton(o, property));
    }
    else
    {
        react.reset(new TransitonReact(o, property));
    }

    ChangeState(TransitonState::RESUME);
}

double Transiton::CubizBezierRecursive(double t, double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3)
{
    double x01 = (x0 + x1) / 2.0;
    double y01 = (y0 + y1) / 2.0;
    double x12 = (x1 + x2) / 2.0;
    double y12 = (y1 + y2) / 2.0;
    double x23 = (x2 + x3) / 2.0;
    double y23 = (y2 + y3) / 2.0;

    double x012 = (x01 + x12) / 2;
    double y012 = (y01 + y12) / 2;
    double x123 = (x12 + x23) / 2;
    double y123 = (y12 + y23) / 2;

    double x0123 = (x012 + x123) / 2;
    double y0123 = (y012 + y123) / 2;

    if (std::fabs(t - x0123) < 0.0000001)
    {
        return y0123;
    }

    if (t < x0123)
    {
        return CubizBezierRecursive(t, x0, y0, x01, y01, x012, y012, x0123, y0123);
    }
    else
    {
        return CubizBezierRecursive(t, x0123, y0123, x123, y123, x23, y23, x3, y3);
    }
}

double Transiton::CubizBezier(double t)
{
    return CubizBezierRecursive(t, 0, 0, x1, y1, x2, y2, 1, 1);
}

void Transiton::Update()
{
    auto now = std::chrono::steady_clock::now();
    double ratio = 0.0f;
    if (now > end)
    {
        printf("STOP\n");
        ratio = 0.0f;
        ChangeState(TransitonState::READY);
    }
    else
    {
        std::chrono::milliseconds dt = std::chrono::duration_cast<std::chrono::milliseconds>(now - start);
        std::chrono::milliseconds total = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        double t = dt.count() * 1.0f / total.count();
        ratio = CubizBezier(t);
        react->OnUpdate(ratio);
    }
}

void Transiton::Run()
{
    if (state == TransitonState::RUN)
    {
        auto now = std::chrono::steady_clock::now();

        std::chrono::milliseconds msec((int)(duration * 1000));
        msec = std::chrono::duration_cast<std::chrono::milliseconds>(end - now);
        start = now;
        end = start + msec;
        ChangeState(TransitonState::RESUME);
    }
    else
    {
        auto now = std::chrono::steady_clock::now();

        std::chrono::milliseconds msec((int)(duration * 1000));
        start = now;
        end = start + msec;
        ChangeState(TransitonState::RUN);
    }
}

void Transiton::ChangeState(TransitonState newState)
{
    switch (newState)
    {
    case TransitonState::READY:
        react->OnReady();
        break;
    case TransitonState::RUN:
        react->OnRun();
        break;
    case TransitonState::RESUME:
        react->OnResume();
        newState = TransitonState::RUN;
        break;
    default:
        break;
    }
    state = newState;
}

LengthTransiton::LengthTransiton(std::shared_ptr<GraphicObject> o, std::string property)
    : TransitonReact(o, property)
{
    beginVal = endVal = o->style.Get(property).AnyCast<ValueType::Length>();
}

void LengthTransiton::OnReady()
{
    std::shared_ptr<GraphicObject> o = obj.lock();
    o->style.Set(property, std::to_string((int)endVal.value) + "px"); //TODO: support float
    beginVal = endVal;
}

void LengthTransiton::OnRun()
{
    std::shared_ptr<GraphicObject> o = obj.lock();
    endVal = o->style.Get(property).AnyCast<ValueType::Length>();
}

void LengthTransiton::OnResume()
{
    beginVal = curVal;
    std::shared_ptr<GraphicObject> o = obj.lock();
    endVal = o->style.Get(property).AnyCast<ValueType::Length>();
}

void LengthTransiton::OnUpdate(double ratio)
{
    double bv = beginVal.value;
    double ev = endVal.value;
    std::shared_ptr<GraphicObject> o = obj.lock();
    curVal = ValueType::Length(bv + (ev - bv) * (ratio), "px");
    // printf("curVal %f\n", curVal.value);
    o->style.Set(property, std::to_string((int)curVal.value) + "px"); //TODO: support float
}