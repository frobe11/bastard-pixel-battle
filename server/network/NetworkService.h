#pragma once
#include <memory>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <nlohmann/json.hpp>
#include "Command.h"

namespace beast = boost::beast;         // из пространства имен boost::beast
namespace websocket = beast::websocket; // из пространства имен boost::beast::websocket
namespace asio = boost::asio;           // из пространства имен boost::asio
using tcp = asio::ip::tcp;

class NetworkService
{
private:
    std::shared_ptr<asio::io_context> _ioPtr;
    std::shared_ptr<asio::thread_pool> _domainThreadPoolPtr;

public:
    NetworkService(std::shared_ptr<asio::io_context> ioPtr, std::shared_ptr<asio::thread_pool> domainThreadPoolPtr) : _ioPtr(ioPtr), _domainThreadPoolPtr(domainThreadPoolPtr) {};
    ~NetworkService() = default;
    void readMessage(std::shared_ptr<websocket::stream<tcp::socket>> ws);
    void handleNewConnection(std::shared_ptr<websocket::stream<tcp::socket>> ws);
    void startServer(uint16_t port);
    
};
