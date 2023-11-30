#include <Components/TransformComponent.h>
#include <Components/RendererComponent.h>
#include <Components/PlayerMovement.h>

#include <Ecs/ComponentFactory.h>

#include <Game/Game.h>

using namespace rpp;

int main()
{
    ComponentFactory::GetInstance()
        .Add(new TransformComponentFactory())
        .Add(new RendererComponentFactory())
        .Add(new PlayerMovementComponentFactory());

    Game game = Game(
        Point2Int(50, 50),
        Point2Int(45, 15));

    do {

        game.Update();

        if (game.HasRenderRequest())
            game.Render();

    } while (game.IsRunning());
}
