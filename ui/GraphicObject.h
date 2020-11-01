#pragma once

#include "Style.h"
#include "DrawRect.h"
#include "Transition.h"
#include "Event.h"

#include <functional>
#include <memory>

class GraphicObject;
class Transiton;

using EventCallback = void(std::shared_ptr<GraphicObject>);

class GraphicObject : public std::enable_shared_from_this<GraphicObject>
{
private:
protected:
    int x = 0, y = 0;
    int absoluteX = 0, absoluteY = 0;
    int width = 0, height = 0;
    bool visiable = true;
    std::function<EventCallback> onClickCallback;
    DrawRect draw;

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
        return v.Is<ValueType::Auto>() ? 0 : v.AnyCast<ValueType::Length>().value;
    }

    int GetPaddingLeft()
    {
        auto v = GetStyle("padding-left");
        return v.Is<ValueType::Auto>() ? 0 : v.AnyCast<ValueType::Length>().value;
    }
    int GetPaddingRight()
    {
        auto v = GetStyle("padding-right");
        return v.Is<ValueType::Auto>() ? 0 : v.AnyCast<ValueType::Length>().value;
    }
    int GetPaddingTop()
    {
        auto v = GetStyle("padding-top");
        return v.Is<ValueType::Auto>() ? 0 : v.AnyCast<ValueType::Length>().value;
    }
    int GetPaddingBottom()
    {
        auto v = GetStyle("padding-bottom");
        return v.Is<ValueType::Auto>() ? 0 : v.AnyCast<ValueType::Length>().value;
    }

    void SetX(int x) { this->x = x; }
    void SetY(int y) { this->y = y; }

    int GetWidth() { return width; }
    int GetContentBoxWidth() { return width; }
    int GetPaddingBoxWidth() { return width + GetPaddingLeft() + GetPaddingRight(); }
    int GetBorderBoxWidth() { return width + GetPaddingLeft() + GetPaddingRight() + GetBorderWidth(); }
    void SetWidth(int width) { this->width = width; }
    void SetContentBoxWidth(int width) { this->width = width; }
    void SetPaddingBoxWidth(int width) { this->width = width - (GetPaddingLeft() + GetPaddingRight()); }
    void SetBorderBoxWidth(int width) { this->width = width - (GetPaddingLeft() + GetPaddingRight() + GetBorderWidth()); }

    int GetHeight() { return height; }
    int GetContentBoxHeight() { return height; }
    int GetPaddingBoxHeight() { return height + GetPaddingTop() + GetPaddingBottom(); }
    int GetBorderBoxHeight() { return height + GetPaddingTop() + GetPaddingBottom() + GetBorderWidth(); }
    void SetHeight(int height) { this->height = height; }

    void SetContentBoxHeight(int height) { this->height = height; }
    void SetPaddingBoxHeight(int height) { this->height = height - (GetPaddingTop() + GetPaddingBottom()); }
    void SetBorderBoxHeight(int height) { this->height = height - (GetPaddingTop() + GetPaddingBottom() + GetBorderWidth()); }

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
        style.Set(key, value);

        if (transitons.find(key) != transitons.end())
        {
            transitons[key].Run(*this);
        }
    }

    Any GetStyle(std::string key)
    {
        return style.Get(key);
    }

    void SetOnClickCallback(std::function<EventCallback> cb)
    {
        onClickCallback = cb;
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
                item->SetAbsolutePositon(GetAbsoluteX() + GetBorderWidth() + GetPaddingLeft() + item->GetX(), GetAbsoluteY() + GetBorderWidth() + GetPaddingTop() + item->GetY());
                item->Render(*this, base);
            }
        }
    }
    virtual void OnRender(GraphicObject &parent, surface_t *base)
    {
        double borderRadius = GetStyle("border-radius").Is<ValueType::Auto>() ? 0 : GetStyle("border-radius").AnyCast<ValueType::Length>().value;
        double borderWidth = GetStyle("border-width").Is<ValueType::Auto>() ? 0 : GetStyle("border-width").AnyCast<ValueType::Length>().value;
        ValueType::Color bgColor = GetStyle("background-color").Is<ValueType::Auto>() ? ValueType::Color(0, 0, 0, 0) : GetStyle("background-color").AnyCast<ValueType::Color>();
        ValueType::Color borderColor = GetStyle("border-color").Is<ValueType::Auto>() ? ValueType::Color(0, 0, 0, 0) : GetStyle("border-color").AnyCast<ValueType::Color>();

        draw.Set(GetBorderBoxWidth() - GetBorderWidth(), GetBorderBoxHeight() - GetBorderWidth(), GetAbsoluteX() + GetBorderWidth() / 2, GetAbsoluteY() + GetBorderWidth() / 2, Style::ToColorT(bgColor));
        draw.SetBorder(borderRadius, borderWidth, Style::ToColorT(borderColor));

        draw.OnDraw(base);
    }

    virtual void OnEvent() {}
    virtual void OnFocus() {}
    virtual void OnRelease() {}
    virtual void OnPress() {}
    virtual void OnHover() {}
    virtual void OnClick()
    {
        // if (GetStyle("width") != "300")
        // {
        //     SetStyle("width", "300");
        // }
        // else
        // {
        //     SetStyle("width", "100");
        // }

        // if (GetStyle("height") != "100")
        // {
        //     SetStyle("height", "100");
        // }
        // else
        // {
        //     SetStyle("height", "50");
        // }
        if (onClickCallback)
            onClickCallback(GetSelf());
    }

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

    void AddTransiton(Transiton tran)
    {
        transitons[tran.property] = tran;
        transitons[tran.property].Init(GetStyle(tran.property));
    }

    virtual void UpdateTranstion()
    {
        for (auto &item : children)
        {
            item->UpdateTranstion();
        }
        for (auto &tran : transitons)
            tran.second.Update(*this);
    }
    virtual void EventCapture(EVENT_TYPE type, int x, int y)
    {
        for (auto &item : children)
        {
            item->EventCapture(type, x, y);
        }

        if ((x >= GetAbsoluteX() && x < (GetAbsoluteX() + width)) && (y >= GetAbsoluteY() && y < (GetAbsoluteY() + height)))
        {
            OnEvent();

            if (type == EVENT_TYPE::MOUSE_BTN_UP)
            {
                OnRelease();
                OnClick();
            }
            else if (type == EVENT_TYPE::MOUSE_BTN_DOWN)
            {
                OnPress();
            }
            else if (type == EVENT_TYPE::MOUSE_MOTION)
            {
                OnFocus();
            }
        }
    }
};
