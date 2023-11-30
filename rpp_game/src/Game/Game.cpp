#include <RPPConstants.h>
#include <Game/Game.h>

#include <Components/PlayerMovement.h>

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
    , m_player("Player")
    , m_renderGame(true)
{
    m_player.AddComponent<PlayerMovement>();
    m_player.Renderer()->TokenKey(RPPTokens::PLAYER_TOKEN);

    m_world.AddChild(&m_player);

    for (int i = 0; i < 20; i++)
    {
        auto go = new GameObject("Test_" + std::to_string(i));
        go->Transform()->Position(Point2Int(rand() % _worldSize.x, rand() % _worldSize.y));
        go->Renderer()->TokenKey(RPPTokens::WALL_TOKEN);
        m_world.AddChild(go);
    }

    m_camera.MoveTo(0, 0);
    m_camera.Clamp(_worldSize);
}

void Game::Update()
{
    m_keyboard.Poll();
    m_world.Update();

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
        auto position = m_player.Transform()->Position();
        position += delta;
        position.Clamp(m_world.worldSize - Point2Int(1, 1));

        m_player.Transform()->Position(position);
        m_camera.MoveTo(position);
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
    return !m_keyboard.IsDown(KeyCodes::ESCAPE_KEY);
}
