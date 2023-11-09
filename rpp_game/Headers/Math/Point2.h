#pragma once

namespace rpp
{
    struct Point2Int
    {
        int x; 
        int y;

        Point2Int()
            : x(0)
            , y(0)
        {}
        Point2Int(int _x, int _y)
            : x(_x)
            , y(_y)
        {}
        Point2Int(const Point2Int& _point)
            : x(_point.x)
            , y(_point.y)
        {}
    };
}
