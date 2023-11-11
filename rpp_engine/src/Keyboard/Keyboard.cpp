#include <Keyboard/Keyboard.h>

using namespace rpp;

//
// Key
//

void Key::Poll()
{
    m_isUp = false;

    if (CheckKeyState(keyCode))
    {
        m_isDown = !m_isDown && !m_isHeld;
        m_isHeld = !m_isDown;
    }
    else
    {
        m_isUp = m_isDown || m_isHeld;
        m_isDown = m_isHeld = false;
    }
}

//
// Keyboard
//

Keyboard::Keyboard(std::vector<KeyCodes> _keyCodes)
    : m_keys()
{
    for (auto& keyCode : _keyCodes)
        m_keys.insert({ keyCode, Key(keyCode) });
}

void Keyboard::Poll()
{
    for (auto& key : m_keys)
        key.second.Poll();
}

bool Keyboard::IsDown(KeyCodes _keyCode)
{
    if (m_keys.count(_keyCode) == 0)
        return false;

    return m_keys.at(_keyCode).IsDown();
}

bool Keyboard::IsHeld(KeyCodes _keyCode)
{
    if (m_keys.count(_keyCode) == 0)
        return false;

    return m_keys.at(_keyCode).IsHeld();
}

bool Keyboard::IsUp(KeyCodes _keyCode)
{
    if (m_keys.count(_keyCode) == 0)
        return false;

    return m_keys.at(_keyCode).IsUp();
}
