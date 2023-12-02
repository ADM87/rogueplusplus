#include <Components/TransformComponent.h>
#include <Components/RendererComponent.h>
#include <Components/PlayerMovement.h>
#include <Ecs/ComponentFactory.h>
#include <Keyboard/Keyboard.h>
#include <Game/Game.h>
#include <Game/GameLoop.h>

using namespace rpp;

int main()
{
    Game game(Point2Int(50, 50), Point2Int(45, 15));

    // Register component factories
    ComponentFactory::GetInstance()
        .Add(new TransformComponentFactory())
        .Add(new RendererComponentFactory())
        .Add(new PlayerMovementComponentFactory());

    // Register keyboard keys
    Keyboard::GetInstance()
        .Add(KeyCodes::ESCAPE_KEY)
        .Add(KeyCodes::UP_KEY)
        .Add(KeyCodes::DOWN_KEY)
        .Add(KeyCodes::LEFT_KEY)
        .Add(KeyCodes::RIGHT_KEY);

    GameLoop::GetInstance().Begin(&game);
}
