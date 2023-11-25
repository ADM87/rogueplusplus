#pragma once

#include <Math/Point2.h>

namespace rpp
{
    struct RectangleInt;
    struct Rectangle
    {
        float x;
        float y;
        float width;
        float height;

        Rectangle()
            : x(0)
            , y(0)
            , width(0)
            , height(0)
        {}
        Rectangle(float _x, float _y, float _width, float _height)
            : x(_x)
            , y(_y)
            , width(_width)
            , height(_height)
        {}
        Rectangle(const Rectangle& _rectangle)
            : x(_rectangle.x)
            , y(_rectangle.y)
            , width(_rectangle.width)
            , height(_rectangle.height)
        {}
        Rectangle(const RectangleInt& _rectangle);

        inline float Area() const { return width * height; }

        bool Contains(const float& _x, const float& _y) const;
        bool Contains(const Point2& _point) const;
    };

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
        RectangleInt(const Rectangle& _rectangle);

        inline unsigned Area() const { return width * height; }

        bool Contains(const int& _x, const int& _y) const;
        bool Contains(const Point2Int& _point) const;
    };
}
