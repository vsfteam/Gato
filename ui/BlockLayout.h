#pragma once

#include "GraphicObject.h"

#include <memory>

class BlockLayout
{
public:
    using GraphicObjectIterator = std::vector<std::shared_ptr<GraphicObject>>::iterator;
    void AlignInlineBlock(int height, int lineHeight, GraphicObjectIterator begin, GraphicObjectIterator end)
    {
        for (auto it = begin; it != end; it++)
        {
            std::shared_ptr<GraphicObject> item = *it;
            Any align = item->style.Get("vertical-align");

            if (align.Is<ValueType::Auto>() || (align.Is<std::string>() && align.AnyCast<std::string>() == "bottom"))
            {
                item->SetY(height + lineHeight - item->GetBorderBoxHeight());
            }
            else if (align.AnyCast<std::string>() == "top")
            {
                item->SetY(height);
            }
        }
    }

    int CalcInlineBlocks(int width, int height, GraphicObjectIterator begin, GraphicObjectIterator end, GraphicObjectIterator &newBegin)
    {
        int lineHeight = 0;
        int lineWidth = 0;
        auto it = begin;
        for (; it != end; it++)
        {
            std::shared_ptr<GraphicObject> item = *it;
            Any display = item->GetStyle("display");
            if(display.AnyCast<std::string>() != "inline-block")
            {
                break;
            }
            else if (item->GetBorderBoxWidth() + lineWidth > width)
            {
                // Only one item in one line
                if (it == begin)
                {
                    item->SetX(0);
                    item->SetY(height);
                    return item->GetBorderBoxHeight();
                }
                break;
            }
            else
            {
                newBegin = it;
                item->SetX(lineWidth);
                // item->SetY(height);

                if (item->GetBorderBoxHeight() > lineHeight)
                {
                    lineHeight = item->GetBorderBoxHeight();
                }
                lineWidth += item->GetBorderBoxWidth();

                // std::cout << "X:" << item->GetX() << "  Y:" << item->GetY() << "\n";
            }
        }

        AlignInlineBlock(height, lineHeight, begin, it);
        return lineHeight;
    }

    void BorderBox()
    {

    } 
    void PaddingBox()
    {

    }
    
    void ContentBox()
    {

    }

    // 计算block width, 和非auto height
    void ReflowForward(std::shared_ptr<GraphicObject> obj, std::shared_ptr<GraphicObject> parent, std::shared_ptr<GraphicObject> widthFixedParent, std::shared_ptr<GraphicObject> heightFixedParent, int level = 0)
    {
        Any width = obj->GetStyle("width");
        Any height = obj->GetStyle("height");
        Any display = obj->GetStyle("display");

        if (parent != nullptr)
        {
            if (width.Is<ValueType::Auto>())
            {
                if (display.Is<ValueType::Auto>() || display.AnyCast<std::string>() == "block")
                {
                    obj->SetBorderBoxWidth(parent->GetContentBoxWidth());
                    widthFixedParent = obj;
                }
                else
                {
                    // auto width of inline-block, depend on total width of child items
                    obj->SetBorderBoxWidth(0);
                }
            }
            else
            {
                if (width.Is<ValueType::Length>())
                {
                    obj->SetContentBoxWidth(width.AnyCast<ValueType::Length>().value);
                }
                else if (width.Is<ValueType::Percentage>())
                {
                    obj->SetContentBoxWidth(parent->GetContentBoxWidth() * width.AnyCast<ValueType::Percentage>().value / 100.0);
                }
                widthFixedParent = obj;
            }

            if (height.Is<ValueType::Auto>())
            {
            }
            else
            {
                if (height.Is<ValueType::Length>())
                    obj->SetContentBoxHeight(height.AnyCast<ValueType::Length>().value);
                else if (height.Is<ValueType::Percentage>())
                {
                    obj->SetContentBoxHeight(heightFixedParent->GetContentBoxHeight() * height.AnyCast<ValueType::Percentage>().value / 100.0);
                }
                heightFixedParent = obj;
            }
        }

        for (auto &item : obj->children)
        {
            ReflowForward(item, obj, widthFixedParent, heightFixedParent, level + 1);
        }

        // calc auto width of inline-block
        if ((display.Is<std::string>() && display.AnyCast<std::string>() == "inline-block") && width.Is<ValueType::Auto>())
        {
            int childWidth = 0;
            for (auto &item : obj->children)
            {
                childWidth += item->GetBorderBoxWidth();
            }

            if (childWidth > widthFixedParent->GetContentBoxWidth())
                childWidth = widthFixedParent->GetContentBoxWidth();
            obj->SetBorderBoxWidth(childWidth);

            for (auto &item : obj->children)
            {
                Any width = item->GetStyle("width");
                if (width.Is<ValueType::Auto>())
                {
                }
                else
                {
                    if (width.Is<ValueType::Percentage>())
                    {
                        item->SetContentBoxWidth(obj->GetContentBoxWidth() * width.AnyCast<ValueType::Percentage>().value / 100.0);
                    }
                }
            }
        }

        int childHeight = 0;

        for (auto it = obj->children.begin(); it != obj->children.end(); it++)
        {
            std::shared_ptr<GraphicObject> item = *it;
            Any display = item->GetStyle("display");

            if (display.Is<std::string>() && display.AnyCast<std::string>() == "inline-block")
            {
                childHeight += CalcInlineBlocks(obj->GetContentBoxWidth(), childHeight, it, obj->children.end(), it);
            }
            else
            {
                item->SetY(childHeight);
                childHeight += item->GetBorderBoxHeight();
            }
        }

        if (parent != nullptr)
        {
            Any height = obj->style.Get("height");
            if (height.Is<ValueType::Auto>())
            {
                if (obj->children.size() != 0)
                    obj->SetBorderBoxHeight(childHeight);
            }
        }

        // for (int i = 0; i < level; i++)
        //     printf("\t");

        // std::cout << "w/h(" << obj->GetWidth() << "/" << obj->GetHeight() << ")\n";
    }
    void Reflow(std::shared_ptr<GraphicObject> root)
    {
        ReflowForward(root, nullptr, root, root);
    }
};