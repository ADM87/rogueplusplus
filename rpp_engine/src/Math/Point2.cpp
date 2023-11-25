#include <Math/Point2.h>

using namespace rpp;

//
// Point2
//

Point2::Point2(const Point2Int& _point)
    : x((float)_point.x)
    , y((float)_point.y)
{

}

//
// Point2Int
//

Point2Int::Point2Int(const Point2& _point)
    : x((int)_point.x)
    , y((int)_point.y)
{}
