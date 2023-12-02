#include <Game/GameLoop.h>

using namespace rpp;

//
// GameLoop
//

void GameLoop::Begin(Game* _game)
{
    do {

        _game->Update();

        if (_game->HasRenderRequest())
            _game->Render();

    } while (_game->IsRunning());

    delete _game;
}