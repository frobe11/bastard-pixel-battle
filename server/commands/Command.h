#pragma once
#include <mutex>
#include <string>
#include <memory>
#include <vector>
#include <cstddef>
#include <mutex>
#include <condition_variable>
#include <iostream>
#include "Color.h"
#include "SessionHolder.h"
class Command
{
protected:
    mutable std::mutex _mutex;
    std::condition_variable _condVar;
    bool _executed;

public:
    Command() : _mutex(), _executed(false) {};
    ~Command() = default;
    Command &operator=(const Command &) = delete;
    Command(const Command &) = delete;
    std::mutex &getMutex() const;
    virtual void execute() = 0;
    void waitForExecution();
    bool isExecuted() const;
};

class CommandgetGrid : public Command
{
private:
    std::string _sessionID;
    std::shared_ptr<const PixelGrid> _grid;

public:
    CommandgetGrid() = delete;
    CommandgetGrid(const std::string &sessionID) : _grid(), _sessionID(sessionID) {};
    ~CommandgetGrid() = default;
    const std::string &getSessionID();
    std::shared_ptr<const PixelGrid> getResult() const;
    void execute() override;
};

class CommandNewGame : public Command
{
private:
    std::string _sessionID;
    size_t _x;
    size_t _y;

public:
    CommandNewGame(size_t x, size_t y) : Command(), _sessionID(), _x(x), _y(x) {};
    const std::string &getResult();
    size_t getX();
    ~CommandNewGame() = default;
    size_t getY();
    void execute() override;
};

class CommandsetPixel : public Command
{
private:
    std::string _sessionID;
    size_t _x;
    size_t _y;
    Color _color;
    bool _result = false;

public:
    CommandsetPixel() = delete;
    CommandsetPixel(std::string sessionID, size_t x, size_t y, Color color)
        : Command(), _sessionID(sessionID), _x(x), _y(y), _color(color) {};
    ~CommandsetPixel() = default;
    const std::string &getSessionID();
    size_t getX();
    size_t getY();
    const Color &getColor();
    bool getResult();
    void execute() override;
};
