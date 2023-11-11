#pragma once

#include <Windows.h>

namespace rpp
{
    enum KeyCodes
    {
        ESCAPE_KEY  = VK_ESCAPE,
        UP_KEY      = VK_UP,
        DOWN_KEY    = VK_DOWN,
        LEFT_KEY    = VK_LEFT,
        RIGHT_KEY   = VK_RIGHT
    };

    static bool CheckKeyState(KeyCodes _keyCode)
    {
        return GetKeyState(_keyCode) & 0x8000;
    }
}
