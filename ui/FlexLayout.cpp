#include "Layout.h"

#include <assert.h>
void FlexLayout::JustifyContent(std::shared_ptr<GraphicObject> obj, GraphicObjectIterator begin, GraphicObjectIterator end)
{
    int width = obj->GetContentBoxWidth();
    std::string justifyContent = obj->GetStyle("justify-content").AnyCast<std::string>();
    int widthOfItems = 0;
    int countOfItems = 0;
    for (auto it = begin; it != end; it++)
    {
        std::shared_ptr<GraphicObject> item = *it;
        widthOfItems += item->GetMarginBoxWidth();
        countOfItems++;
    }

    if (countOfItems == 0)
        return;

    int x = 0;
    int spaceWidth = 0;

    if (justifyContent == "flex-start")
    {
    }
    else if (justifyContent == "flex-end")
    {
        x = width - widthOfItems;
    }
    else if (justifyContent == "center")
    {
        x = (width - widthOfItems) / 2;
    }
    else if (justifyContent == "space-between")
    {
        if (countOfItems > 1)
        {
            spaceWidth = (width - widthOfItems) / (countOfItems - 1);
        }
    }
    else if (justifyContent == "space-around")
    {
        spaceWidth = (width - widthOfItems) / (countOfItems);
        x = spaceWidth / 2;
    }

    for (auto it = begin; it != end; it++)
    {
        std::shared_ptr<GraphicObject> item = *it;
        item->SetX(x);
        x += item->GetMarginBoxWidth() + spaceWidth;
    }
}
void FlexLayout::AlignItems(std::shared_ptr<GraphicObject> obj, GraphicObjectIterator begin, GraphicObjectIterator end, int startHeight, int lineHeight)
{
    std::string alignItems = obj->style.Get("align-items").AnyCast<std::string>();

    if (alignItems == "flex-start")
    {
        for (auto it = begin; it != end; it++)
        {
            std::shared_ptr<GraphicObject> item = *it;
            item->SetY(startHeight);
        }
    }
    else if (alignItems == "flex-end")
    {
        for (auto it = begin; it != end; it++)
        {
            std::shared_ptr<GraphicObject> item = *it;
            item->SetY(startHeight + lineHeight - item->GetMarginBoxHeight());
        }
    }
    else if (alignItems == "center")
    {
        for (auto it = begin; it != end; it++)
        {
            std::shared_ptr<GraphicObject> item = *it;
            item->SetY(startHeight + (lineHeight - item->GetMarginBoxHeight()) / 2);
        }
    }
    else
    {
        assert(0);
    }
}

void FlexLayout::AlignContent(std::shared_ptr<GraphicObject> obj, LineBoxIterator begin, LineBoxIterator end)
{
    int height = obj->GetContentBoxHeight();
    std::string alignContent = obj->GetStyle("align-content").AnyCast<std::string>();
    int heightOfItems = 0;
    int countOfItems = 0;
    for (auto it = begin; it != end; it++)
    {
        LineBox &item = *it;
        heightOfItems += item.lineHeight;
        countOfItems++;
    }

    if (countOfItems == 0)
        return;

    int y = 0;
    int spaceHeight = 0;

    if (alignContent == "flex-start")
    {
    }
    else if (alignContent == "flex-end")
    {
        y = height - heightOfItems;
    }
    else if (alignContent == "center")
    {
        y = (height - heightOfItems) / 2;
    }
    else if (alignContent == "space-between")
    {
        if (countOfItems > 1)
        {
            spaceHeight = (height - heightOfItems) / (countOfItems - 1);
        }
    }
    else if (alignContent == "space-around")
    {
        spaceHeight = (height - heightOfItems) / (countOfItems);
        y = spaceHeight / 2;
    }

    for (auto item = begin; item != end; item++)
    {
        item->SetY(y);
        AlignItems(obj, item->begin, item->end, y, item->GetLineHeight());
        y += item->GetLineHeight() + spaceHeight;
    }
}

void FlexLayout::AlignInlineBlock(int height, int lineHeight, GraphicObjectIterator begin, GraphicObjectIterator end)
{
    for (auto it = begin; it != end; it++)
    {
        std::shared_ptr<GraphicObject> item = *it;
        Any align = item->style.Get("vertical-align");

        if (align.Is<ValueType::Unset>() || (align.Is<std::string>() && align.AnyCast<std::string>() == "bottom"))
        {
            item->SetY(height + lineHeight - item->GetMarginBoxHeight());
        }
        else if (align.AnyCast<std::string>() == "top")
        {
            item->SetY(height);
        }
    }
}

int FlexLayout::CalcOneLineItems(int width, int height, GraphicObjectIterator begin, GraphicObjectIterator end, GraphicObjectIterator &it)
{
    int lineWidth = 0;
    int lineHeight = 0;

    for (; it != end; it++)
    {
        std::shared_ptr<GraphicObject> item = *it;
        std::string display = item->GetStyle("display").AnyCast<std::string>();

        if (item->GetMarginBoxWidth() + lineWidth > width)
        {
            // Only one item in one line
            if (it == begin)
            {
                it++;
                lineWidth += item->GetMarginBoxWidth();
            }
            break;
        }
        else
        {
            if (item->GetMarginBoxHeight() > lineHeight)
            {
                lineHeight = item->GetMarginBoxHeight();
            }
            lineWidth += item->GetMarginBoxWidth();
        }
    }

    return lineHeight;
}

int FlexLayout::CalcInlineBlocks(int width, int height, GraphicObjectIterator begin, GraphicObjectIterator end, GraphicObjectIterator &newBegin)
{
    int lineHeight = 0;
    int lineWidth = 0;
    auto it = begin;
    for (; it != end; it++)
    {
        std::shared_ptr<GraphicObject> item = *it;
        std::string display = item->GetStyle("display").AnyCast<std::string>();
        if (display != "inline-block" && display != "inline-flex")
        {
            break;
        }
        else if (item->GetMarginBoxWidth() + lineWidth > width)
        {
            // Only one item in one line
            if (it == begin)
            {
                item->SetX(0);
                item->SetY(height);
                return item->GetMarginBoxHeight();
            }
            break;
        }
        else
        {
            newBegin = it;
            item->SetX(lineWidth);
            // item->SetY(height);

            if (item->GetMarginBoxHeight() > lineHeight)
            {
                lineHeight = item->GetMarginBoxHeight();
            }
            lineWidth += item->GetMarginBoxWidth();

            // std::cout << "X:" << item->GetX() << "  Y:" << item->GetY() << "\n";
        }
    }

    AlignInlineBlock(height, lineHeight, begin, it);
    return lineHeight;
}

// 计算block width, 和非auto height
void FlexLayout::ReflowForward(std::shared_ptr<GraphicObject> obj, std::shared_ptr<GraphicObject> parent, std::shared_ptr<GraphicObject> widthFixedParent, std::shared_ptr<GraphicObject> heightFixedParent, int level)
{
    ValueType::Length width = obj->GetStyle("width").AnyCast<ValueType::Length>();
    ValueType::Length height = obj->GetStyle("height").AnyCast<ValueType::Length>();
    std::string display = obj->GetStyle("display").AnyCast<std::string>();

    if (parent != nullptr)
    {
        if (width.isAuto)
        {
            if (display == "flex")
            {
                obj->SetMarginBoxWidth(parent->GetContentBoxWidth());
                widthFixedParent = obj;
            }
            else
            {
                // auto width of inline-block, depend on total width of child items
                obj->SetMarginBoxWidth(0);
            }
        }
        else
        {
            if (width.unit == "px")
            {
                obj->SetContentBoxWidth(width.value);
            }
            else if (width.unit == "%")
            {
                obj->SetContentBoxWidth(parent->GetContentBoxWidth() * width.value / 100.0);
            }
            widthFixedParent = obj;
        }

        if (height.isAuto)
        {
        }
        else
        {
            if (height.unit == "px")
                obj->SetContentBoxHeight(height.value);
            else if (height.unit == "%")
            {
                obj->SetContentBoxHeight(heightFixedParent->GetContentBoxHeight() * height.value / 100.0);
            }
            heightFixedParent = obj;
        }
    }

    for (auto &item : obj->children)
    {
        std::string display = item->GetStyle("display").AnyCast<std::string>();

        if (display == "flex" || display == "inline-flex")
        {
            FlexLayout::ReflowForward(item, obj, widthFixedParent, heightFixedParent, level + 1);
        }
        else
        {
            BlockLayout::ReflowForward(item, obj, widthFixedParent, heightFixedParent, level + 1);
        }
    }

    // calc auto width of inline-block
    if ((display == "inline-flex") && width.isAuto)
    {
        int childWidth = 0;
        for (auto &item : obj->children)
        {
            childWidth += item->GetMarginBoxWidth();
        }

        //TODO: 如果嵌套多个auto width, 并且padding margin不为0，可能计算有问题
        if (childWidth > widthFixedParent->GetContentBoxWidth())
            childWidth = widthFixedParent->GetContentBoxWidth();
        obj->SetContentBoxWidth(childWidth);

        for (auto &item : obj->children)
        {
            ValueType::Length width = item->GetStyle("width").AnyCast<ValueType::Length>();
            if (width.isAuto)
            {
            }
            else
            {
                if (width.unit == "%")
                {
                    item->SetContentBoxWidth(obj->GetContentBoxWidth() * width.value / 100.0);
                }
            }
        }
    }

    int childHeight = 0;

    std::string wrap = obj->GetStyle("flex-wrap").AnyCast<std::string>();

    if (wrap == "nowrap")
    {
        JustifyContent(obj, obj->children.begin(), obj->children.end());
        AlignItems(obj, obj->children.begin(), obj->children.end(), 0, obj->GetContentBoxHeight());
    }
    else
    {
        std::vector<LineBox> lineBoxList;
        for (auto it = obj->children.begin(); it != obj->children.end();)
        {
            std::shared_ptr<GraphicObject> item = *it;
            std::string display = item->GetStyle("display").AnyCast<std::string>();
            auto begin = it;
            int lineHeight = CalcOneLineItems(obj->GetContentBoxWidth(), childHeight, begin, obj->children.end(), it);
            auto end = it;
            JustifyContent(obj, begin, end);
            lineBoxList.emplace_back(begin, end, lineHeight);
            childHeight += lineHeight;
        }
        AlignContent(obj, lineBoxList.begin(), lineBoxList.end());
    }

    if (parent != nullptr)
    {
        ValueType::Length height = obj->style.Get("height").AnyCast<ValueType::Length>();
        if (height.isAuto)
        {
            if (obj->children.size() != 0)
                obj->SetContentBoxHeight(childHeight);
        }
    }

    // for (int i = 0; i < level; i++)
    //     printf("\t");

    // std::cout << "w/h(" << obj->GetWidth() << "/" << obj->GetHeight() << ")\n";
}
void FlexLayout::Reflow(std::shared_ptr<GraphicObject> root)
{
    ReflowForward(root, nullptr, root, root);
}