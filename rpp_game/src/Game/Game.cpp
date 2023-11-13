#include <RPPConstants.h>
#include <Components/ComponentTypeIds.h>
#include <Components/Rendering/WorldRendererComponent.h>
#include <Game/Game.h>

using namespace rpp;

//
// Game
//

Game::Game(Point2Int _worldSize, Point2Int _viewSize)
    : m_keyboard(
        {
            KeyCodes::ESCAPE_KEY,
            KeyCodes::UP_KEY,
            KeyCodes::DOWN_KEY,
            KeyCodes::LEFT_KEY,
            KeyCodes::RIGHT_KEY
        })
    , m_world(
        _worldSize,
        {
            RPPLayers::DEFAULT_LAYER
        },
        {
            { RPPTokens::EMPTY_TOKEN,   ' ' },
            { RPPTokens::WALL_TOKEN,    '#' },
            { RPPTokens::PLAYER_TOKEN,  '&' }
        })
    , m_camera(_viewSize)
    , m_player()
    , m_renderGame(true)
{
    m_player.AddComponent(new WorldRendererComponent(RPPLayers::DEFAULT_LAYER, RPPTokens::PLAYER_TOKEN));

    m_camera.MoveTo(0, 0);
}

void Game::Update()
{
    m_keyboard.Poll();

    Point2Int delta;

    if (m_keyboard.IsDown(KeyCodes::UP_KEY))
        delta.y = -1;
    if (m_keyboard.IsDown(KeyCodes::DOWN_KEY))
        delta.y = 1;
    if (m_keyboard.IsDown(KeyCodes::LEFT_KEY))
        delta.x = -1;
    if (m_keyboard.IsDown(KeyCodes::RIGHT_KEY))
        delta.x = 1;

    if (delta.x != 0 || delta.y != 0)
    {
        Point2Int position = m_player.Transform()->Position();
        position += delta;
        position.Clamp(m_world.worldSize);

        m_player.Transform()->Position(position);
        m_camera.MoveTo(position);

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
    return !m_keyboard.IsDown(KeyCodes::ESCAPE_KEY);
}
