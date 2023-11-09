#pragma once

#include <Keyboard/Keyboard.h>
#include <Math/Point2.h>
#include <World/World.h>

namespace rpp
{
    class Game
    {
    public:

        Game(Point2Int _worldSize);

        void Update();
        void Render();
        void RequestRender();

        bool HasRenderRequest();
        bool IsRunning();

    private:

        Keyboard m_keyboard;
        World m_world;

        bool m_renderGame;
    };
}

