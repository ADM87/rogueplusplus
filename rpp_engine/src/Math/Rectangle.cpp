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

Point2 Rectangle::Min() const
{
    return Point2(x, y);
}

Point2 Rectangle::Max() const
{
    return Point2(x + width, y + height);
}

bool Rectangle::Contains(const Point2& _point) const
{
    return Contains(_point.x, _point.y);
}

bool Rectangle::Contains(const float& _x, const float& _y) const
{
    float right = x + width;
    float bottom = y + height;
    return _x >= x 
        && _x < right 
        && _y >= y 
        && _y < bottom;
}

bool Rectangle::Overlaps(const Rectangle& _rectangle) const
{
    auto minA = Min();
    auto maxA = Max();
    auto minB = _rectangle.Min();
    auto maxB = _rectangle.Max();

    // Rects take up the same space.
    if (minA.x == minB.x && minA.y == minB.y
        && maxA.x == maxB.x && maxA.y == maxB.y)
        return true;

    // Rects are partially overlapping.
    if ((minA.x < maxB.x && maxA.x > minB.x)
        && (minA.y < maxB.y && maxA.y > minB.y))
        return true;

    // Rects completely contains the other.
    if ((minA.x >= minB.x && maxA.x >= maxB.x && minA.y >= minB.y && maxA.y >= maxB.y)
        || (minB.x >= minA.x && maxB.x >= maxA.x && minB.y >= minA.y && maxB.y >= maxA.y))
        return true;

    return false;
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

Point2Int RectangleInt::Min() const
{
    return Point2Int(x, y);
}

Point2Int RectangleInt::Max() const
{
    return Point2Int(x + width, y + height);
}

bool RectangleInt::Contains(const Point2Int& _point) const
{
    return Contains(_point.x, _point.y);
}

bool RectangleInt::Contains(const int& _x, const int& _y) const
{
    int right = x + width;
    int bottom = y + height;
    return _x >= x
        && _x <= right 
        && _y >= y
        && _y <= bottom;
}

bool RectangleInt::Overlaps(const RectangleInt& _rectangle) const
{
    auto minA = Min();
    auto maxA = Max();
    auto minB = _rectangle.Min();
    auto maxB = _rectangle.Max();

    // Rects take up the same space.
    if (minA.x == minB.x && minA.y == minB.y
        && maxA.x == maxB.x && maxA.y == maxB.y)
        return true;

    // Rects are partially overlapping.
    if ((minA.x < maxB.x && maxA.x > minB.x)
        && (minA.y < maxB.y && maxA.y > minB.y))
        return true;

    // Rects completely contains the other.
    if ((minA.x >= minB.x && maxA.x >= maxB.x && minA.y >= minB.y && maxA.y >= maxB.y)
        || (minB.x >= minA.x && maxB.x >= maxA.x && minB.y >= minA.y && maxB.y >= maxA.y))
        return true;

    return false;
}
