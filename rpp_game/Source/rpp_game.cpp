#include <Game/Game.h>

int main()
{
    rpp::Game game = rpp::Game(
        rpp::Point2Int(50, 50),
        rpp::Point2Int(45, 15));

    do {

        game.Update();

        if (game.HasRenderRequest())
            game.Render();

    } while (game.IsRunning());
}
