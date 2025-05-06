#include <boost/beast/core.hpp>
#include <boost/asio.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <mutex>
#include "NetworkService.h"

namespace beast = boost::beast;         // из пространства имен boost::beast
namespace websocket = beast::websocket; // из пространства имен boost::beast::websocket
namespace asio = boost::asio;            // из пространства имен boost::asio
using tcp = asio::ip::tcp;               // из пространства имен boost::asio::ip::tcp

int main()
{
    const uint16_t PORT = 9808;
    std::shared_ptr<asio::io_context> io = std::make_shared<asio::io_context>();
    std::shared_ptr<asio::thread_pool> pool = std::make_shared<asio::thread_pool>(8);
    NetworkService networkService(io,pool);
    // io->run();
    // бесконечный цикл ниже, если появится доп логика закидывать в поток
    std::cout << "starting Server...\n";
    networkService.startServer(PORT);
}
