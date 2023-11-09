#pragma once

#include <Keyboard/Keyboard.h>

namespace rpp
{
    class Game
    {
    public:

        Game();

        void Update();
        void Render();
        void RequestRender();

        bool HasRenderRequest();
        bool IsRunning();

    private:

        Keyboard m_keyboard;

        bool m_renderGame;
    };
}

