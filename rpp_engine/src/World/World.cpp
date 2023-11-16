#include <World/World.h>

#include <algorithm>
#include <iostream>
#include <random>
#include <string>

using namespace rpp;

#define UNKNOWN_TOKEN '?'

//
// World
//

World::World(Point2Int _worldSize, std::vector<int> _layers, std::vector<std::pair<int, char>> _tokens)
    : m_layers()
    , m_tokens()
    , worldSize(_worldSize)
{
    for (auto& layer : _layers)
        m_layers.insert({ layer, Grid(_worldSize.x, _worldSize.y) });

    for (auto& token : _tokens)
        m_tokens.insert({ token.first, Token(token.first, token.second) });
}

//***********************************************************************
// TODO - Now that entities exist, world rendering should be refactored.
// Currently each cell being rendered with the region will iterate over 
// all entities also within the region to check if they are in that cell.
//***********************************************************************
void World::RenderRegion(const RectangleInt& _region)
{
    int regionEndX = _region.x + _region.width;
    int regionEndY = _region.y + _region.height;

    std::string buffer;

    for (int y = _region.y; y < regionEndY; y++)
    {
        for (int x = _region.x; x < regionEndX; x++)
        {
            char token = UNKNOWN_TOKEN;

            if (x >= 0 && x < worldSize.x && y >= 0 && y < worldSize.y)
                token = GetToken(x, y);

            buffer += token;
        }

        if (y + 1 < regionEndY)
            buffer += '\n';
    }

    std::cout << buffer << std::endl;
}

const char& World::GetToken(const int& _x, const int& _y)
{
    auto firstLayer = m_layers.begin();
    auto currentLayer = m_layers.end();

    int cell = -1;

    while (currentLayer != firstLayer)
    {
        currentLayer--;

        cell = currentLayer->second.At(_x, _y);
        if (cell > 0 || (cell == 0 && currentLayer == firstLayer))
            return m_tokens.at(cell).value;
    }

    return UNKNOWN_TOKEN;
}
