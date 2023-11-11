#pragma once

namespace rpp
{
    struct Point2Int
    {
        static Point2Int& Zero()
        {
            static Point2Int zero = Point2Int(0, 0);
            return zero;
        }

        static Point2Int& One()
        {
            static Point2Int one = Point2Int(1, 1);
            return one;
        }

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

        friend Point2Int operator+(Point2Int _lhs, const Point2Int& _rhs)
        {
            _lhs += _rhs;
            return _lhs;
        }

        friend Point2Int operator-(Point2Int _lhs, const Point2Int& _rhs)
        {
            _lhs -= _rhs;
            return _lhs;
        }

        void operator=(const Point2Int& _point)
        {
            x = _point.x;
            y = _point.y;
        }

        Point2Int& operator+=(const Point2Int& _rhs)
        {
            x += _rhs.x;
            y += _rhs.y;
            return *this;
        }

        Point2Int& operator-=(const Point2Int& _rhs)
        {
            x -= _rhs.x;
            y -= _rhs.y;
            return *this;
        }

        void Clamp(const Point2Int& _max)
        {
            Clamp(Point2Int(), _max);
        }

        void Clamp(const Point2Int& _min, const Point2Int& _max)
        {
            if (x < _min.x) x = _min.x;
            if (y < _min.y) y = _min.y;
            if (x > _max.x) x = _max.x;
            if (y > _max.y) y = _max.y;
        }
    };
}
