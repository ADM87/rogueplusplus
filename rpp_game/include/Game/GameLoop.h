#pragma once

#include <Game/Game.h>

namespace rpp
{
    class GameLoop
    {
    public:

        static GameLoop& GetInstance()
        {
            static GameLoop instance;
            return instance;
        }

        void Begin(Game* _game);

    private:

        GameLoop() = default;
    };
}