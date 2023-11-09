#pragma once

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

        World(Point2Int _worldSize, std::vector<int> _layers, std::vector<std::pair<unsigned int, char>> _tokens);

        void RenderRegion(const RectangleInt& _region);

    private:

        std::map<int, Grid> m_layers;
        std::map<int, Token> m_tokens;

        const char& GetToken(const int& _x, const int& _y);
    };
}
