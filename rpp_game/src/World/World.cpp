#include <World/World.h>

#include <algorithm>
#include <iostream>
#include <random>
#include <string>

using namespace rpp;

constexpr auto UNKNOWN_TOKEN        = '?';
constexpr auto VERTICAL_BORDER      = '|';
constexpr auto HORIZONTAL_BORDER    = '=';
constexpr auto NEW_LINE             = '\n';
constexpr auto VERTICAL_OFFSET      = 2;
constexpr auto HORIZONTAL_OFFSET    = 3;

//
// World
//

World::World(Point2Int _worldSize, std::vector<int> _layers, std::vector<std::pair<int, char>> _tokens)
    : m_layers()
    , m_tokens()
    , worldSize(_worldSize)
{
    m_quadTree = QuadTreeNode(4, 1, Rectangle(0, 0, (float)_worldSize.x, (float)_worldSize.y), &m_quadTree, nullptr);

    for (auto& layer : _layers)
        m_layers.insert({ layer, Grid(_worldSize.x, _worldSize.y) });

    for (auto& token : _tokens)
        m_tokens.insert({ token.first, Token(token.first, token.second) });
}

void World::AddChild(GameObject* _gameObject)
{
    m_quadTree.Insert(_gameObject);
}

void World::RemoveChild(GameObject* _gameObject)
{
    m_quadTree.Erase(_gameObject);
}

void World::RenderRegion(const RectangleInt& _region)
{
    // TODO : This refresh is temporary.
    m_quadTree.Refresh();

    std::unordered_set<GameObject*> gameObjects;
    m_quadTree.Query(_region, gameObjects);

    int width = _region.width + HORIZONTAL_OFFSET;
    int height = _region.height + VERTICAL_OFFSET;
    int size = width * height;
    int i = 0;

    char token = UNKNOWN_TOKEN;
    char* buffer = new char[size + 1];
    *(buffer + size) = 0;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            i = y * width + x;

            if (x + 1 == width)
                token = NEW_LINE;
            else if (y == 0 || y + VERTICAL_OFFSET - 1 == height)
                token = HORIZONTAL_BORDER;
            else if (x == 0 || x + HORIZONTAL_OFFSET - 1 == width)
                token = VERTICAL_BORDER;
            else
                token = GetToken(_region.x + x - 1, _region.y + y - 1, gameObjects);

            *(buffer + i) = token;
        }
    }

    std::cout << buffer;

    delete[] buffer;
}

const char& World::GetToken(const int& _x, const int& _y, const std::unordered_set<GameObject*>& _gameObjects)
{
    if (_x < 0 || _x >= worldSize.x || _y < 0 || _y >= worldSize.y)
        return UNKNOWN_TOKEN;

    auto firstLayer = m_layers.begin();
    auto currentLayer = m_layers.end();

    int cell = -1;
    Point2Int position;

    if (_gameObjects.size())
    {
        for (auto& go : _gameObjects)
        {
            position = go->Transform()->Position();
            if (position.x == _x && position.y == _y)
                return m_tokens.at(go->Renderer()->TokenKey()).value;
        }
    }

    while (currentLayer != firstLayer)
    {
        currentLayer--;

        cell = currentLayer->second.At(_x, _y);
        if (cell > 0 || (cell == 0 && currentLayer == firstLayer))
            return m_tokens.at(cell).value;
    }

    return UNKNOWN_TOKEN;
}
