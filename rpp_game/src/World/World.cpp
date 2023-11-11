#include <World/World.h>

#include <algorithm>
#include <iostream>
#include <random>
#include <string>

using namespace rpp;

//
// World
//

World::World(Point2Int _worldSize, std::vector<RPPLayers> _layers, std::vector<std::pair<RPPTokens, char>> _tokens)
    : m_layers()
    , m_tokens()
    , m_entities()
    , worldSize(_worldSize)
{
    for (auto& layer : _layers)
    {
        m_layers.insert({ layer, Grid(_worldSize.x, _worldSize.y) });
        m_entities.insert({ layer, std::vector<Entity*>() });
    }

    m_tokens.insert({ RPPTokens::UNKNOWN_TOKEN, Token(RPPTokens::UNKNOWN_TOKEN, '?') });
    for (auto& token : _tokens)
        m_tokens.insert({ token.first, Token(token.first, token.second) });

    for (int i = 0; i < _worldSize.x * _worldSize.y; i++)
        m_layers.at(RPPLayers::DEFAULT_LAYER).Set(i, rand() % 2);
}

void World::Add(Entity* _entity)
{
    if (_entity == nullptr || m_entities.count(_entity->Layer()) == 0)
        return;

    std::vector<Entity*>& entities = m_entities.at(_entity->Layer());

    if (std::find(entities.begin(), entities.end(), _entity) == entities.end())
        entities.push_back(_entity);
}

void World::Remove(Entity* _entity)
{
    if (_entity == nullptr || m_entities.count(_entity->Layer()) == 0)
        return;

    std::vector<Entity*>& entities = m_entities.at(_entity->Layer());
    std::vector<Entity*>::iterator it = std::find(entities.begin(), entities.end(), _entity);

    if (it != entities.end())
        entities.erase(it);
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
    auto entities = GetEntitiesWithinRegion(_region);

    for (int y = _region.y; y < regionEndY; y++)
    {
        for (int x = _region.x; x < regionEndX; x++)
        {
            char token = m_tokens.at(RPPTokens::UNKNOWN_TOKEN).value;

            if (x >= 0 && x < worldSize.x && y >= 0 && y < worldSize.y)
                token = GetToken(x, y, entities);

            buffer += token;
        }

        if (y + 1 < regionEndY)
            buffer += '\n';
    }

    std::cout << buffer << std::endl;
}

std::map<RPPLayers, std::vector<Entity*>> World::GetEntitiesWithinRegion(const RectangleInt& _region)
{
    auto entityLayers = std::map<RPPLayers, std::vector<Entity*>>();

    for (auto& layer : m_entities)
    {
        std::vector<Entity*> entities = std::vector<Entity*>();
        for (auto& entity : layer.second)
        {
            if (_region.Contains(entity->Transform()->Position()))
                entities.push_back(entity);
        }
        entityLayers.insert({ layer.first, entities });
    }

    return entityLayers;
}

const char& World::GetToken(const int& _x, const int& _y, std::map<RPPLayers, std::vector<Entity*>>& _entityLayers)
{
    auto firstLayer = m_layers.begin();
    auto currentLayer = m_layers.end();

    int cell = -1;
    Point2Int position;

    while (currentLayer != firstLayer)
    {
        currentLayer--;

        cell = currentLayer->second.At(_x, _y);
        if (!IsValueToken(cell))
            cell = -1;

        auto& entities = _entityLayers.at(currentLayer->first);
        for (auto& entity : entities)
        {
            position = entity->Transform()->Position();
            if (position.x == _x && position.y == _y)
                return m_tokens.at(entity->Token()).value;
        }

        if (cell > 0 || (cell == 0 && currentLayer == firstLayer))
            return m_tokens.at((RPPTokens)cell).value;
    }

    return m_tokens.at(RPPTokens::UNKNOWN_TOKEN).value;
}
