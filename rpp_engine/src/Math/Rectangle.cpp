#include <Math/Rectangle.h>

using namespace rpp;

//
// RectangleInt
//

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
