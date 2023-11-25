#include <Math/Rectangle.h>

using namespace rpp;

//
// Rectangle
//

Rectangle::Rectangle(const RectangleInt& _rectangle)
    : x((float)_rectangle.x)
    , y((float)_rectangle.y)
    , width((float)_rectangle.width)
    , height((float)_rectangle.height)
{

}

bool Rectangle::Contains(const Point2& _point) const
{
    return Contains(_point.x, _point.y);
}

bool Rectangle::Contains(const float& _x, const float& _y) const
{
    float right = x + width;
    float bottom = y + height;
    return _x >= x && _x <= right && _y >= y && _y <= bottom;
}

//
// RectangleInt
//

RectangleInt::RectangleInt(const Rectangle& _rectangle)
    : x((int)_rectangle.x)
    , y((int)_rectangle.y)
    , width((int)_rectangle.width)
    , height((int)_rectangle.height)
{

}

bool RectangleInt::Contains(const Point2Int& _point) const
{
    return Contains(_point.x, _point.y);
}

bool RectangleInt::Contains(const int& _x, const int& _y) const
{
    int right = x + width;
    int bottom = y + height;
    return _x >= x && _x <= right && _y >= y && _y <= bottom;
}
