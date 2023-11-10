#pragma once

#include <RPPConstants.h>
#include <Entity/Entity.h>
#include <Math/Point2.h>
#include <Structures/Grid.h>
#include <Structures/Token.h>

#include <map>
#include <vector>

namespace rpp
{
    class World
    {
    public:

        const Point2Int worldSize;

        World(Point2Int _worldSize, std::vector<RPPLayers> _layers, std::vector<std::pair<RPPTokens, char>> _tokens);

        void Add(Entity* _entity);
        void Remove(Entity* _entity);

        void RenderRegion(const RectangleInt& _region);

        std::map<RPPLayers, std::vector<Entity*>> GetEntitiesWithinRegion(const RectangleInt& _region);

    private:

        std::map<RPPLayers, Grid>                   m_layers;
        std::map<RPPTokens, Token>                  m_tokens;
        std::map<RPPLayers, std::vector<Entity*>>   m_entities;

        const char& GetToken(const int& _x, const int& _y, std::map<RPPLayers, std::vector<Entity*>>& _entityLayers);
    };
}
