#pragma once

#include <vector>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "PixelGrid.h"

class Session
{
public:
    Session() = delete;
    Session(size_t width, size_t height)
    {
        _pixelGrid = std::make_shared<PixelGrid>(width, height);
        _sessionID = std::make_shared<const std::string>(_generateUUID());
    };
    Session(Session &other) : _pixelGrid(other.getPixelGrid())
    {
        _sessionID = std::make_shared<const std::string>(_generateUUID());
    };
    std::shared_ptr<PixelGrid> getPixelGrid() const;
    std::shared_ptr<const std::string> getSessionID() const;

private:
    std::shared_ptr<PixelGrid> _pixelGrid;
    std::shared_ptr<const std::string> _sessionID;
    std::string _generateUUID();
};