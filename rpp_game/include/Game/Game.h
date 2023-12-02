#pragma once

#include <Math/Point2.h>
#include <World/World.h>

namespace rpp
{
    class Game
    {
    public:

        Game(Point2Int _worldSize, Point2Int _viewSize);

        void Start();
        void End();
        void Update();
        void Render();
        void RequestRender();

        bool HasRenderRequest();
        bool IsRunning();

    private:

        World m_world;

        bool m_renderGame;
    };
}

