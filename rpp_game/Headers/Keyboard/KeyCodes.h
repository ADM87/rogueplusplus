#pragma once

#include <Windows.h>

namespace rpp
{
    enum KeyCodes
    {
        ESCAPE  = VK_ESCAPE,
        UP      = VK_UP,
        DOWN    = VK_DOWN,
        LEFT    = VK_LEFT,
        RIGHT   = VK_RIGHT
    };

    static bool CheckKeyState(KeyCodes _keyCode)
    {
        return GetKeyState(_keyCode) & 0x8000;
    }
}
