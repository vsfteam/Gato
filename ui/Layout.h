#pragma once

#include "GraphicObject.h"
#include <vector>
#include <memory>

using GraphicObjectIterator = std::vector<std::shared_ptr<GraphicObject>>::iterator;

class LineBox
{
public:
    GraphicObjectIterator begin;
    GraphicObjectIterator end;
    int lineHeight = 0;

    LineBox(GraphicObjectIterator _begin, GraphicObjectIterator _end, int _lineHeight)
    {
        begin = _begin;
        end = _end;
        lineHeight = _lineHeight;
    }
    int GetLineHeight()
    {
        return lineHeight;
    }

    void SetY(int y)
    {
        for(auto it = begin; it != end; it++)
        {
            (*it)->SetY(y);
        }
    }
};

using LineBoxIterator = std::vector<LineBox>::iterator;

class FlexLayout
{
public:
    static void JustifyContent(std::shared_ptr<GraphicObject> obj, GraphicObjectIterator begin, GraphicObjectIterator end);
    static void AlignItems(std::shared_ptr<GraphicObject> obj, GraphicObjectIterator begin, GraphicObjectIterator end,int startHeight,  int lineHeight);
    static void AlignContent(std::shared_ptr<GraphicObject> obj, LineBoxIterator begin, LineBoxIterator end);
    static int CalcOneLineItems(int width, int height, GraphicObjectIterator begin, GraphicObjectIterator end, GraphicObjectIterator &newBegin);
    static void AlignInlineBlock(int height, int lineHeight, GraphicObjectIterator begin, GraphicObjectIterator end);
    static int CalcInlineBlocks(int width, int height, GraphicObjectIterator begin, GraphicObjectIterator end, GraphicObjectIterator &newBegin);
    static void ReflowForward(std::shared_ptr<GraphicObject> obj, std::shared_ptr<GraphicObject> parent, std::shared_ptr<GraphicObject> widthFixedParent, std::shared_ptr<GraphicObject> heightFixedParent, int level = 0);
    static void Reflow(std::shared_ptr<GraphicObject> root);
};

class BlockLayout
{
public:
    static void AlignInlineBlock(int height, int lineHeight, GraphicObjectIterator begin, GraphicObjectIterator end);
    static int CalcInlineBlocks(int width, int height, GraphicObjectIterator begin, GraphicObjectIterator end, GraphicObjectIterator &newBegin);
    static void ReflowForward(std::shared_ptr<GraphicObject> obj, std::shared_ptr<GraphicObject> parent, std::shared_ptr<GraphicObject> widthFixedParent, std::shared_ptr<GraphicObject> heightFixedParent, int level = 0);
    static void Reflow(std::shared_ptr<GraphicObject> root);
};