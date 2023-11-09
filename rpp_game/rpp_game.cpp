#include <Game.h>

int main()
{
    rpp::Game game;

    do {

        game.Update();

        if (game.HasRenderRequest())
            game.Render();

    } while (game.IsRunning());
}
