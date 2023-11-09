#include <Game.h>

using namespace rpp;

//
// Game
//

Game::Game()
    : m_keyboard(
        {
            KeyCodes::ESCAPE,
            KeyCodes::UP,
            KeyCodes::DOWN,
            KeyCodes::LEFT,
            KeyCodes::RIGHT            
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
