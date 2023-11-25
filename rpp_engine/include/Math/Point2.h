#pragma once

namespace rpp
{
    struct Point2Int;
    struct Point2
    {
        float x;
        float y;

        Point2()
            : x(0.f)
            , y(0.f)
        {}
        Point2(const float& _x, const float& _y)
            : x(_x)
            , y(_y)
        {}
        Point2(const Point2& _point)
            : x(_point.x)
            , y(_point.y)
        {}
        Point2(const Point2Int& _point);

        friend Point2 operator+(Point2 _lhs, const Point2& _rhs)
        {
            _lhs += _rhs;
            return _lhs;
        }

        friend Point2 operator-(Point2 _lhs, const Point2& _rhs)
        {
            _lhs -= _rhs;
            return _lhs;
        }

        void operator=(const Point2& _point)
        {
            x = _point.x;
            y = _point.y;
        }

        Point2& operator+=(const Point2& _rhs)
        {
            x += _rhs.x;
            y += _rhs.y;
            return *this;
        }

        Point2& operator-=(const Point2& _rhs)
        {
            x -= _rhs.x;
            y -= _rhs.y;
            return *this;
        }

        void Clamp(const Point2& _max)
        {
            Clamp(Point2(), _max);
        }

        void Clamp(const Point2& _min, const Point2& _max)
        {
            if (x < _min.x) x = _min.x;
            if (y < _min.y) y = _min.y;
            if (x > _max.x) x = _max.x;
            if (y > _max.y) y = _max.y;
        }
    };

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
        Point2Int(const Point2& _point);

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
