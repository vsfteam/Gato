#pragma once

#include "Style.h"
#include "DrawRect.h"
#include "DrawText.h"
#include "Any.h"

#include "Transition.h"
#include "Event.h"

#include <functional>
#include <memory>

class GraphicObject;
class Transiton;

using EventCallback = void(std::shared_ptr<GraphicObject>, Any e);

class GraphicObject : public std::enable_shared_from_this<GraphicObject>
{
private:
protected:
    int x = 0, y = 0;
    int absoluteX = 0, absoluteY = 0;
    int width = 0, height = 0;
    bool visiable = true;
    std::map<std::string, std::function<EventCallback>> mapOfCallback;
    bool drag = false;
    DrawRect draw;
    DrawText text;

public:
    std::map<std::string, Transiton> transitons;
    std::vector<std::shared_ptr<GraphicObject>> children;
    std::weak_ptr<GraphicObject> parent;
    Style style;
    GraphicObject() = delete;
    GraphicObject(StyleList list)
    {
        for (const auto &item : list)
        {
            SetStyle(item.first, item.second);
        }
    }
    virtual ~GraphicObject()
    {
    }

    std::shared_ptr<GraphicObject> GetSelf()
    {
        return shared_from_this();
    }

    void SetParent(std::shared_ptr<GraphicObject> obj)
    {
        parent = obj;
    }

    std::shared_ptr<GraphicObject> GetParent()
    {
        return shared_from_this();
    }
    void SetAbsolutePositon(int x, int y)
    {
        absoluteX = x;
        absoluteY = y;
    }
    int GetX() { return x; }
    int GetY() { return y; }

    int GetBorderWidth()
    {
        auto v = GetStyle("border-width");
        return v.Is<ValueType::Unset>() ? 0 : v.AnyCast<ValueType::Length>().value;
    }
    int GetPadding(std::string dir)
    {
        auto v = GetStyle("padding-" + dir);

        if (v.Is<ValueType::Unset>())
        {
            auto v = GetStyle("padding");
            return v.Is<ValueType::Unset>() ? 0 : v.AnyCast<ValueType::Length>().value;
        }
        else
        {
            return v.AnyCast<ValueType::Length>().value;
        }
        return 0;
    }

    int GetMargin(std::string dir)
    {
        auto v = GetStyle("margin-" + dir);

        if (v.Is<ValueType::Unset>())
        {
            auto v = GetStyle("margin");
            return v.Is<ValueType::Unset>() ? 0 : v.AnyCast<ValueType::Length>().value;
        }
        else
        {
            return v.AnyCast<ValueType::Length>().value;
        }
        return 0;
    }

    int GetPaddingLeft()
    {
        return GetPadding("left");
    }
    int GetPaddingRight()
    {
        return GetPadding("right");
    }
    int GetPaddingTop()
    {
        return GetPadding("top");
    }
    int GetPaddingBottom()
    {
        return GetPadding("bottom");
    }

    int GetMarginLeft()
    {
        return GetMargin("left");
    }
    int GetMarginRight()
    {
        return GetMargin("right");
    }
    int GetMarginTop()
    {
        return GetMargin("top");
    }
    int GetMarginBottom()
    {
        return GetMargin("bottom");
    }

    void SetX(int x) { this->x = x; }
    void SetY(int y) { this->y = y; }

    int GetWidth() { return width; }
    int GetContentBoxWidth() { return GetWidth(); }
    int GetPaddingBoxWidth() { return GetWidth() + GetPaddingLeft() + GetPaddingRight(); }
    int GetBorderBoxWidth() { return GetWidth() + GetPaddingLeft() + GetPaddingRight() + GetBorderWidth(); }
    int GetMarginBoxWidth() { return GetWidth() + GetPaddingLeft() + GetPaddingRight() + GetMarginLeft() + GetMarginRight() + GetBorderWidth(); }

    void SetWidth(int width) { this->width = width; }
    void SetContentBoxWidth(int width) { SetWidth(width); }
    void SetPaddingBoxWidth(int width) { SetWidth(width - (GetPaddingLeft() + GetPaddingRight())); }
    void SetBorderBoxWidth(int width) { SetWidth(width - (GetPaddingLeft() + GetPaddingRight() + GetBorderWidth())); }
    void SetMarginBoxWidth(int width) { SetWidth(width - (GetPaddingLeft() + GetPaddingRight() + GetMarginLeft() + GetMarginRight() + GetBorderWidth())); }

    int GetHeight() { return height; }
    int GetContentBoxHeight() { return GetHeight(); }
    int GetPaddingBoxHeight() { return GetHeight() + GetPaddingTop() + GetPaddingBottom(); }
    int GetBorderBoxHeight() { return GetHeight() + GetPaddingTop() + GetPaddingBottom() + GetBorderWidth(); }
    int GetMarginBoxHeight() { return GetHeight() + GetPaddingTop() + GetPaddingBottom() + GetMarginTop() + GetMarginBottom() + GetBorderWidth(); }

    void SetHeight(int height) { this->height = height; }
    void SetContentBoxHeight(int height) { SetHeight(height); }
    void SetPaddingBoxHeight(int height) { SetHeight(height - (GetPaddingTop() + GetPaddingBottom())); }
    void SetBorderBoxHeight(int height) { SetHeight(height - (GetPaddingTop() + GetPaddingBottom() + GetBorderWidth())); }
    void SetMarginBoxHeight(int height) { SetHeight(height - (GetPaddingTop() + GetPaddingBottom() + GetMarginTop() + GetMarginBottom() + GetBorderWidth())); }

    void Hide() { visiable = false; }
    void Show() { visiable = true; }
    bool GetVisibility() { return visiable; }
    void SetVisibility(bool b) { visiable = b; }

    int GetAbsoluteX()
    {
        return absoluteX;
    }
    int GetAbsoluteY()
    {
        return absoluteY;
    }

    void SetStyle(std::string key, std::string value)
    {
        if (transitons.find(key) != transitons.end())
        {
            style.Set(key, value);
            transitons[key].Run();
        }
        else
        {
            style.Set(key, value);
        }
    }

    Any GetStyle(std::string key)
    {
        return style.Get(key);
    }

    void SetCallback(std::string name, std::function<EventCallback> cb)
    {
        mapOfCallback[name] = cb;
    }

    bool CheckCallbackExist(std::string name)
    {
        return (mapOfCallback.find(name) != mapOfCallback.end());
    }

    void Render(GraphicObject &parent, surface_t *base)
    {
        if (visiable)
        {
            OnRender(parent, base);

            for (auto &item : children)
            {
                // std::cout
                //     << "GetAbsoluteX() + GetBorderWidth() + GetPaddingLeft() + item->GetX() : " << GetAbsoluteX() + GetBorderWidth() + GetPaddingLeft() + item->GetX() << ",   "
                //     << "        GetPaddingLeft(): " << GetPaddingLeft() << ",   "
                //     << "        item->GetX(): " << item->GetX() << ",   "

                //     << " GetAbsoluteY() + GetBorderWidth() + GetPaddingTop() + item->GetY(): " << GetAbsoluteY() + GetBorderWidth() + GetPaddingTop() + item->GetY() << ",   "
                //     << "        GetPaddingTop(): " << GetPaddingTop() << ",   "
                //     << "        item->GetY(): " << item->GetY() << ",   "
                //     << "\n";

                int x = GetAbsoluteX() + GetMarginLeft() + GetBorderWidth() + GetPaddingLeft() + item->GetX();
                int y = GetAbsoluteY() + GetMarginTop() + GetBorderWidth() + GetPaddingTop() + item->GetY();

                std::string position = GetStyle("position").AnyCast<std::string>();

                if (position == "static")
                {
                }
                else if (position == "relative")
                {
                    int left = GetStyle("left").Is<ValueType::Length>() ? GetStyle("left").AnyCast<ValueType::Length>().value : 0;
                    int top = GetStyle("top").Is<ValueType::Length>() ? GetStyle("top").AnyCast<ValueType::Length>().value : 0;
                    x += left;
                    y += top;
                }

                item->SetAbsolutePositon(x, y);
                item->Render(*this, base);
            }
        }
    }
    virtual void OnRender(GraphicObject &parent, surface_t *base)
    {
        double borderRadius = GetStyle("border-radius").Is<ValueType::Unset>() ? 0 : GetStyle("border-radius").AnyCast<ValueType::Length>().value;
        double borderWidth = GetStyle("border-width").Is<ValueType::Unset>() ? 0 : GetStyle("border-width").AnyCast<ValueType::Length>().value;
        double blur = GetStyle("backdrop-blur").Is<ValueType::Unset>() ? 0 : GetStyle("backdrop-blur").AnyCast<ValueType::Length>().value;

        ValueType::Color bgColor = GetStyle("background-color").Is<ValueType::Unset>() ? ValueType::Color(0, 0, 0, 0) : GetStyle("background-color").AnyCast<ValueType::Color>();
        ValueType::Color borderColor = GetStyle("border-color").Is<ValueType::Unset>() ? ValueType::Color(0, 0, 0, 0) : GetStyle("border-color").AnyCast<ValueType::Color>();

        draw.Set(GetBorderBoxWidth() - GetBorderWidth(), GetBorderBoxHeight() - GetBorderWidth(), GetAbsoluteX() + GetMarginLeft() + GetBorderWidth() / 2, GetAbsoluteY() + GetMarginTop() + GetBorderWidth() / 2, Style::ToColorT(bgColor));
        draw.SetBorder(borderRadius, borderWidth, Style::ToColorT(borderColor));
        draw.SetBlur(blur);

        if (GetStyle("background-image").Is<std::string>())
        {
            draw.SetBgImage(GetStyle("background-image").AnyCast<std::string>(), GetPaddingBoxWidth(), GetPaddingBoxHeight());
        }
        draw.OnDraw(base);

        if (GetStyle("content").Is<std::string>())
        {
            double fontSize = 12;
            Color color = RGB(0);
            if (GetStyle("font-size").Is<ValueType::Length>())
            {
                fontSize = GetStyle("font-size").AnyCast<ValueType::Length>().value;
            }

            if (GetStyle("color").Is<ValueType::Color>())
            {
                color = Style::ToColorT(GetStyle("color").AnyCast<ValueType::Color>());
            }

            text.Set(GetContentBoxWidth(), GetContentBoxHeight(), GetAbsoluteX() + GetMarginLeft() + GetBorderWidth(), GetAbsoluteY() + GetMarginTop() + GetBorderWidth(), color, fontSize, GetStyle("content").AnyCast<std::string>());
            text.OnDraw(base);
        }
    }

    virtual void OnEvent() {}
    virtual void OnFocus() {}
    virtual void OnRelease() {}
    virtual void OnPress() {}
    virtual void OnHover() {}

    void AppendChild(std::shared_ptr<GraphicObject> obj)
    {
        obj->SetParent(GetSelf());
        children.push_back(obj);
    }

    void AppendChild(StyleList list)
    {
        auto obj = std::make_shared<GraphicObject>(list);
        obj->SetParent(GetSelf());
        children.push_back(obj);
    }

    void AddTransiton(std::string property, double duration, double x1, double y1, double x2, double y2, double delay)
    {
        transitons[property] = Transiton(GetSelf(), property, duration, x1, y1, x2, y2, delay);
    }

    virtual void UpdateTranstion()
    {
        for (auto &item : children)
        {
            item->UpdateTranstion();
        }
        for (auto &tran : transitons)
        {
            if (tran.second.state == TransitonState::RUN)
                tran.second.Update();
        }
    }
    virtual void EventCapture(EVENT_TYPE type, int x, int y)
    {
        for (auto &item : children)
        {
            item->EventCapture(type, x, y);
        }

        if (drag)
        {
            if (type == EVENT_TYPE::MOUSE_BTN_UP)
            {
                if (CheckCallbackExist("ondragend"))
                {
                    mapOfCallback["ondragend"](GetSelf(), std::pair<int, int>(x, y));
                }
                drag = false;
            }
            else if (type == EVENT_TYPE::MOUSE_MOTION)
            {
                if (CheckCallbackExist("ondragover"))
                {
                    mapOfCallback["ondragover"](GetSelf(), std::pair<int, int>(x, y));
                }
            }
        }
        if ((x >= GetAbsoluteX() && x < (GetAbsoluteX() + width)) && (y >= GetAbsoluteY() && y < (GetAbsoluteY() + height)))
        {
            OnEvent();

            if (type == EVENT_TYPE::MOUSE_BTN_UP)
            {
                OnRelease();
                if (CheckCallbackExist("onclick"))
                {
                    mapOfCallback["onclick"](GetSelf(), std::pair<int, int>(x, y));
                }

                if (CheckCallbackExist("onmouseup"))
                {
                    mapOfCallback["onmouseup"](GetSelf(), std::pair<int, int>(x, y));
                }
            }
            else if (type == EVENT_TYPE::MOUSE_BTN_DOWN)
            {
                if (CheckCallbackExist("onmousedown"))
                {
                    mapOfCallback["onmousedown"](GetSelf(), std::pair<int, int>(x, y));
                }
                drag = true;
            }
            else if (type == EVENT_TYPE::MOUSE_MOTION)
            {
                OnFocus();
                if (CheckCallbackExist("onmousemove"))
                {
                    mapOfCallback["onmousemove"](GetSelf(), std::pair<int, int>(x, y));
                }
            }
        }
    }
};
