#include "Session.h"

std::shared_ptr<PixelGrid> Session::getPixelGrid() const
{
    return _pixelGrid;
}

std::shared_ptr<const std::string> Session::getSessionID() const
{
    return _sessionID;
}

std::string Session::_generateUUID()
{
    boost::uuids::random_generator generator;
    boost::uuids::uuid id = generator();
    std::string result = boost::uuids::to_string(id); 
    return result;
}