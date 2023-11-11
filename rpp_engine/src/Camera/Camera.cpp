#include <Camera/Camera.h>

using namespace rpp;

//
// Camera
//

void Camera::MoveTo(const int& _x, const int& _y)
{
    x = _x - width / 2;
    y = _y - height / 2;
}

void Camera::MoveTo(const Point2Int& _location)
{
    MoveTo(_location.x, _location.y);
}

void Camera::Move(const int& _dx, const int& _dy)
{
    x += _dx;
    y += _dy;
}

void Camera::Move(const Point2Int& _delta)
{
    Move(_delta.x, _delta.y);
}

void Camera::Clamp(const Point2Int& _bounds)
{
    Clamp(RectangleInt(0, 0, _bounds.x, _bounds.y));
}

void Camera::Clamp(const RectangleInt& _bounds)
{
    if (x < _bounds.x)
        x = _bounds.x;
    if (y < _bounds.y)
        y = _bounds.y;

    int right = _bounds.x + _bounds.width;
    int bottom = _bounds.y + _bounds.height;

    if (x + width > right)
        x = right - width;
    if (y + height > bottom)
        y = bottom - height;
}
