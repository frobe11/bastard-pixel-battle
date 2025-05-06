#include "Command.h"

std::mutex &Command::getMutex() const
{
    return _mutex;
}

void Command::waitForExecution()
{
    std::unique_lock<std::mutex> lock(_mutex);
    std::cout << "waiting" << std::endl;
    _condVar.wait(lock, [this]()
                   { return _executed; });
    std::cout << "waited" << std::endl;
}

bool Command::isExecuted() const
{
    return _executed;
}

//  передавать callback в Command и вызывать его при окончании execute() threadpool вместо порождения потоков
// GET GRID
const std::string &CommandgetGrid::getSessionID()
{
    return _sessionID;
}

std::shared_ptr<const PixelGrid> CommandgetGrid::getResult() const
{
    std::lock_guard<std::mutex> lock(getMutex());
    return _grid;
}

void CommandgetGrid::execute()
{
    auto session_ptr = SessionHolder::FindSession(_sessionID);
    _grid = session_ptr->getPixelGrid();
    {
        std::lock_guard<std::mutex> lock(_mutex);
        _executed = true;
        _condVar.notify_one();
    }
}

// CREATE NEW GAME
const std::string &CommandNewGame::getResult()
{
    return _sessionID;
}

size_t CommandNewGame::getX()
{
    return _x;
}

size_t CommandNewGame::getY()
{
    return _y;
}

void CommandNewGame::execute()
{
    _sessionID = *SessionHolder::CreateSession(_x, _y);
    std::cout << "session Created" << std::endl;
    {
        std::lock_guard<std::mutex> lock(_mutex);
        std::cout << "executed" << std::endl;
        _executed = true;
        _condVar.notify_one();
    }
}

// CHANGE PIXEL ON GRID IN SOME SECTION
const std::string &CommandsetPixel::getSessionID()
{
    return _sessionID;
}


size_t CommandsetPixel::getX()
{
    return _x;
}

size_t CommandsetPixel::getY()
{
    return _y;
}

const Color &CommandsetPixel::getColor()
{
    return _color;
}

bool CommandsetPixel::getResult()
{
    return _result;
}

void CommandsetPixel::execute()
{
    std::cout << "finding session" << std::endl;
    auto session_ptr = SessionHolder::FindSession(_sessionID);
    if (session_ptr == nullptr)
    {
        std::cout << "session NOT finded" << std::endl;
        _result = false;
        {
            std::lock_guard<std::mutex> lock(_mutex);
            _executed = true;
            _condVar.notify_one();
        }
        return;
    }

    std::cout << "session finded" << std::endl;
    session_ptr->getPixelGrid()->setPixel(_x, _y, _color);
    std::cout << "pixel seted" << std::endl;
    _result = true;
    {
        std::lock_guard<std::mutex> lock(_mutex);
        _executed = true;
        _condVar.notify_one();
    }
}
