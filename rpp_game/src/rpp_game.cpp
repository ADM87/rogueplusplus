#include <Components/TypeFactories/TransformTypeFactory.h>
#include <Ecs/ComponentFactory.h>
#include <Game/Game.h>

using namespace rpp;

int main()
{
    ComponentFactory::GetInstance()
        .AddType(new TransformTypeFactory("Transform"));

    Game game = Game(
        Point2Int(50, 50),
        Point2Int(45, 15));

    do {

        game.Update();

        if (game.HasRenderRequest())
            game.Render();

    } while (game.IsRunning());
}
