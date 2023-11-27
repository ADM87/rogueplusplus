#include <World/World.h>

#include <algorithm>
#include <iostream>
#include <random>
#include <string>

using namespace rpp;

#define UNKNOWN_TOKEN '?'
#define VERTICAL_BORDER '|'
#define HORIZONTAL_BORDER '='

//
// World
//

World::World(Point2Int _worldSize, std::vector<int> _layers, std::vector<std::pair<int, char>> _tokens)
    : m_layers()
    , m_tokens()
    , worldSize(_worldSize)
{
    m_quadTree = QuadTreeNode(4, 1, Rectangle(0, 0, (float)_worldSize.x, (float)_worldSize.y), &m_quadTree);

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

//***********************************************************************
// TODO - Now that entities exist, world rendering should be refactored.
// Currently each cell being rendered with the region will iterate over 
// all entities also within the region to check if they are in that cell.
//***********************************************************************
void World::RenderRegion(const RectangleInt& _region)
{
    int regionStartX = _region.x - 1;
    int regionStartY = _region.y - 1;
    int regionEndX = _region.x + _region.width;
    int regionEndY = _region.y + _region.height;

    std::string buffer;
    std::unordered_set<GameObject*> gameObjects;

    m_quadTree.Query(_region, gameObjects);

    for (int y = regionStartY; y <= regionEndY; y++)
    {
        for (int x = regionStartX; x <= regionEndX; x++)
        {
#pragma region DrawWorldBorder
            if (y == regionStartY || y == regionEndY)
            {
                buffer += HORIZONTAL_BORDER;
                continue;
            }
            if (x == regionStartX || x == regionEndX)
            {
                buffer += VERTICAL_BORDER;
                continue;
            }
#pragma endregion

            char token = UNKNOWN_TOKEN;

            if (x >= 0 && x < worldSize.x && y >= 0 && y < worldSize.y)
                token = GetToken(x, y, gameObjects);

            buffer += token;
        }

        if (y < regionEndY)
            buffer += '\n';
    }

    std::cout << buffer << std::endl;
    std::cout << " GameObjects: " << std::to_string(gameObjects.size()) << std::endl;
}

const char& World::GetToken(const int& _x, const int& _y, const std::unordered_set<GameObject*>& _gameObjects)
{
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
