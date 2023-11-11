#pragma once

#include <Math/Point2.h>

namespace rpp
{
    struct RectangleInt
    {
        int x;
        int y;
        int width;
        int height;

        RectangleInt()
            : x(0)
            , y(0)
            , width(0)
            , height(0)
        {}
        RectangleInt(int _x, int _y, int _width, int _height)
            : x(_x)
            , y(_y)
            , width(_width)
            , height(_height)
        {}
        RectangleInt(const RectangleInt& _rectangle)
            : x(_rectangle.x)
            , y(_rectangle.y)
            , width(_rectangle.width)
            , height(_rectangle.height)
        {}

        inline int Area() const { return width * height; }

        bool Contains(const int& _x, const int& _y) const;
        bool Contains(const Point2Int& _point) const;
    };
}
