#pragma once

#include <Game/GameObject.h>
#include <Math/Point2.h>
#include <Structures/Grid.h>
#include <Structures/Token.h>
#include <Structures/QuadTree.h>

#include <map>
#include <unordered_map>
#include <vector>

namespace rpp
{
    class World
    {
    public:

        const Point2Int worldSize;

        World(Point2Int _worldSize, std::vector<int> _layers, std::vector<std::pair<int, char>> _tokens);

        void AddChild(GameObject* _gameObject);
        void RemoveChild(GameObject* _gameObject);

        void RenderRegion(const RectangleInt& _region);

    private:

        QuadTreeNode                    m_quadTree;

        std::map<int, Grid>             m_layers;
        std::unordered_map<int, Token>  m_tokens;

        const char& GetToken(const int& _x, const int& _y, const std::unordered_set<TransformComponent*>& _transforms);
    };
}
