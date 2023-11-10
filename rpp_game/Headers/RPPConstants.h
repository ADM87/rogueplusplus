#pragma once

namespace rpp
{
    enum RPPLayers
    {
        UNKNOWN_LAYER   = -1,
        DEFAULT_LAYER   = 0
    };

    enum RPPTokens
    {
        UNKNOWN_TOKEN = -1,
        EMPTY_TOKEN   = 0,
        WALL_TOKEN    = 1,
        PLAYER_TOKEN  = 2
    };

    static bool IsValueToken(const int& _token)
    {
        return _token == RPPTokens::UNKNOWN_TOKEN
            || _token == RPPTokens::EMPTY_TOKEN
            || _token == RPPTokens::WALL_TOKEN
            || _token == RPPTokens::PLAYER_TOKEN;
    }

    enum RPPComponentTypes
    {
        TRANSFORM_CMP = 1 << 0
    };
}
