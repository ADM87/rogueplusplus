#include <Game/GameLoop.h>

using namespace rpp;

//
// GameLoop
//

void GameLoop::Begin(Game* _game)
{
    _game->Start();

    do {

        _game->Update();

        if (_game->HasRenderRequest())
            _game->Render();

    } while (_game->IsRunning());

    _game->End();
}
