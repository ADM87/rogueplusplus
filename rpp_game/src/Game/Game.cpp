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
    , m_renderGame(true)
{

}

void Game::Start()
{

}

void Game::End()
{

}

void Game::Update()
{
    Keyboard::GetInstance().Poll();
}

void Game::Render()
{
    system("cls");

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
