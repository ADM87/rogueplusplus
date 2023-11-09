#include <Game/Game.h>
#include <Game/GameConstants.h>

using namespace rpp;

//
// Game
//

Game::Game(Point2Int _worldSize)
    : m_keyboard(
        {
            KeyCodes::ESCAPE,
            KeyCodes::UP,
            KeyCodes::DOWN,
            KeyCodes::LEFT,
            KeyCodes::RIGHT            
        })
    , m_world(
        _worldSize,
        {
            GameLayers::BACKGROUND
        },
        {
            { GameTokenKeys::EMPTY, ' ' },
            { GameTokenKeys::WALL,  '#' }
        })
    , m_renderGame(true)
{

}

void Game::Update()
{
    m_keyboard.Poll();
}

void Game::Render()
{
    system("cls");

    m_world.RenderRegion(RectangleInt(0, 0, m_world.worldSize.x, m_world.worldSize.y));
    m_renderGame = false;
}

void Game::RequestRender()
{
    m_renderGame = true;
}

bool Game::HasRenderRequest()
{
    return m_renderGame;
}

bool Game::IsRunning()
{
    return !m_keyboard.IsDown(KeyCodes::ESCAPE);
}
