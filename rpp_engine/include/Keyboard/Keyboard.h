#pragma once

#include <Keyboard/KeyCodes.h>

#include <unordered_map>
#include <unordered_set>

namespace rpp
{
    class Key
    {
    public:

        const KeyCodes keyCode;

        Key(KeyCodes _keyCode)
            : keyCode(_keyCode)
            , m_isDown(false)
            , m_isHeld(false)
            , m_isUp(false)
        {}
        Key(const Key& _key)
            : keyCode(_key.keyCode)
            , m_isDown(_key.m_isDown)
            , m_isHeld(_key.m_isHeld)
            , m_isUp(_key.m_isUp)
        {}

        void Poll();

        inline bool IsDown()	{ return m_isDown; }
        inline bool IsHeld()	{ return m_isHeld; }
        inline bool IsUp()      { return m_isUp; }

    private:

        bool m_isDown;
        bool m_isHeld;
        bool m_isUp;
    };

    class Keyboard
    {
    public:

        static Keyboard& GetInstance()
        {
            static Keyboard instance;
            return instance;
        }

        void Poll();

        bool IsDown(KeyCodes _keyCode);
        bool IsHeld(KeyCodes _keyCode);
        bool IsUp(KeyCodes _keyCode);

        Keyboard& Add(const KeyCodes& _keyCode);

    private:

        std::unordered_map<KeyCodes, Key> m_keys;

        Keyboard() = default;
    };
}

