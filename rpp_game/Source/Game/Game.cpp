#include <Game/Game.h>
#include <Game/GameConstants.h>

using namespace rpp;

//
// Game
//

Game::Game(Point2Int _worldSize, Point2Int _viewSize)
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
    , m_camera(_viewSize)
    , m_renderGame(true)
{

}

void Game::Update()
{
    m_keyboard.Poll();

    Point2Int delta;

    if (m_keyboard.IsDown(KeyCodes::UP))
        delta.y = -1;
    if (m_keyboard.IsDown(KeyCodes::DOWN))
        delta.y = 1;
    if (m_keyboard.IsDown(KeyCodes::LEFT))
        delta.x = -1;
    if (m_keyboard.IsDown(KeyCodes::RIGHT))
        delta.x = 1;

    if (delta.x != 0 || delta.y != 0)
    {
        m_camera.Move(delta);
        m_camera.Clamp(m_world.worldSize);

        RequestRender();
    }
}

void Game::Render()
{
    system("cls");

    m_world.RenderRegion(m_camera);
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
