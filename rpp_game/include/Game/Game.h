#pragma once

#include <Camera/Camera.h>
#include <Ecs/Entity.h>
#include <Keyboard/Keyboard.h>
#include <Math/Point2.h>
#include <World/World.h>

namespace rpp
{
    class Game
    {
    public:

        Game(Point2Int _worldSize, Point2Int _viewSize);

        void Update();
        void Render();
        void RequestRender();

        bool HasRenderRequest();
        bool IsRunning();

    private:

        Keyboard m_keyboard;
        World m_world;
        Camera m_camera;
        Entity m_player;

        bool m_renderGame;
    };
}

