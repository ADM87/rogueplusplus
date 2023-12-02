#include <RPPConstants.h>
#include <Game/Game.h>

#include <Components/PlayerMovement.h>
#include <Keyboard/Keyboard.h>

using namespace rpp;

//
// Game
//

Game::Game(Point2Int _worldSize, Point2Int _viewSize)
    : m_world(
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
    Keyboard::GetInstance().Poll();

    m_world.Update();
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
    return !Keyboard::GetInstance().IsDown(KeyCodes::ESCAPE_KEY);
}
