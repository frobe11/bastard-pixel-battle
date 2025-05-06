#include "PixelGrid.h"

PixelGrid::PixelGrid(size_t width, size_t height)
{
    _height = height;
    _width = width;
    _grid = std::make_shared<std::vector<std::vector<Color>>>(_height, std::vector<Color>(_width, {255,255,255}));
}

// PixelGrid::PixelGrid(PixelGrid &other)
// {
//     _height = other.getHeight();
//     _width = other.getWidth();
//     _grid = std::make_shared<std::vector<std::vector<Color>>>(_height, std::vector<Color>(_width, {255, 255, 255}));
//     auto otherGrid = other.getGrid();
//     for (size_t y = 0; y < _height; y++)
//     {
//         for (size_t x = 0; x < _width; x++)
//         {
//             (*_grid.get())[y][x] = (*otherGrid.get())[y][x];
//         }
//     }
// }

void PixelGrid::setPixel(size_t x, size_t y, Color color)
{

    if ((x > _width) || (y > _height))
    {
        return;
    }
    std::lock_guard<std::mutex> lock(_mutex);

    (*_grid)[y][x] = color;
}

size_t PixelGrid::getHeight() const
{
    return _height;
}

size_t PixelGrid::getWidth() const
{
    return _width;
}

std::vector<std::vector<Color>> PixelGrid::getGrid() const
{
    std::lock_guard<std::mutex> lock(_mutex);
    return *_grid;
}
