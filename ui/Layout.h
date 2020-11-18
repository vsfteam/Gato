#pragma once

#include "GraphicObject.h"
#include <vector>
#include <memory>

using GraphicObjectIterator = std::vector<std::shared_ptr<GraphicObject>>::iterator;

class FlexLayout
{
public:
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