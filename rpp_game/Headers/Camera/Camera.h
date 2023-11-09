#pragma once

#include <Math/Point2.h>
#include <Math/Rectangle.h>

namespace rpp
{
    class Camera : public RectangleInt
    {
    public:

        Camera(Point2Int _viewSize)
            : RectangleInt(0, 0, _viewSize.x, _viewSize.y)
        {}

        void MoveTo(const int& _x, const int& _y);
        void MoveTo(const Point2Int& _location);

        void Move(const int& _dx, const int& _dy);
        void Move(const Point2Int& _delta);

        void Clamp(const Point2Int& _bounds);
        void Clamp(const RectangleInt& _bounds);
    };
}
