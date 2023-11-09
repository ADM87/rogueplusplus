#pragma once

namespace rpp
{
    struct Token
    {
        const int key;
        const char value;

        Token() 
            : key(0)
            , value(0)
        {}
        Token(int _key, char _value)
            : key(_key)
            , value(_value)
        {}
        Token(const Token& _token)
            : key(_token.key)
            , value(_token.value)
        {}
    };
}
