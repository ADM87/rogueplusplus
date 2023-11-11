#pragma once

#include <Math/Rectangle.h>

namespace rpp
{
    class Grid : public RectangleInt
    {
    public:

        Grid() = default;
        Grid(unsigned int _width, unsigned int _height, int _fill = 0);
        Grid(const Grid& _grid);

        ~Grid();

        void Fill(int _fill);

        void Set(const unsigned int& _x, const unsigned int& _y, int _fill);
        void Set(const unsigned int& _i, int _fill);

        const int At(const unsigned int& _x, const unsigned int& _y);
        const int At(const unsigned int& _i);     

    private:

        int* m_matrix;
    };
}
