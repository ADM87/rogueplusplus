#include <Structures/Grid.h>

using namespace rpp;

//
// Grid
//

Grid::Grid(unsigned int _width, unsigned int _height, int _fill)
    : RectangleInt(0, 0, _width, _height)
    , m_matrix(new int[_width * _height])
{
    Fill(_fill);
}

Grid::Grid(const Grid& _grid)
    : RectangleInt(_grid)
    , m_matrix(new int[_grid.width * _grid.height])
{
    int area = _grid.Area();
    for (int i = 0; i < area; i++)
        *(m_matrix + i) = *(_grid.m_matrix + i);
}

Grid::~Grid()
{
    delete[] m_matrix;
    m_matrix = nullptr;
}

void Grid::Fill(int _fill)
{
    int area = Area();
    for (int i = 0; i < area; i++)
        *(m_matrix + i) = _fill;
}

void Grid::Set(const unsigned int& _x, const unsigned int& _y, int _fill)
{
    Set(_y * width + _x, _fill);
}

void Grid::Set(const unsigned int& _i, int _fill)
{
    if (_i >= Area())
        return;

    *(m_matrix + _i) = _fill;
}

const int Grid::At(const unsigned int& _x, const unsigned int& _y)
{
    return At(_y * width + _x);
}

const int Grid::At(const unsigned int& _i)
{
    if (_i >= Area())
        return -1;

    return *(m_matrix + _i);
}
