#pragma once
#include <vector>
#include <string>
#include <mutex>
#include <memory>
#include "Color.h"

class PixelGrid
{
public:
    PixelGrid(size_t width, size_t height);
    // PixelGrid(PixelGrid& other);
    void setPixel(size_t x, size_t y, Color color);
    size_t getHeight() const;
    size_t getWidth() const;
    // string -> Color
    std::vector<std::vector<Color>> getGrid() const;

private:
    size_t _width, _height;
    std::shared_ptr<std::vector<std::vector<Color>>> _grid;
    mutable std::mutex _mutex;
};