#ifndef CLIENT_NET_SERVICE_H
#define CLIENT_NET_SERVICE_H

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <nlohmann/json.hpp>
#include <string>
#include <sstream>
#include <vector>
#include <QVector>
#include <QColor>
#include <cstdint>
#include <iostream>

namespace beast = boost::beast;         // из пространства имен boost::beast
namespace websocket = beast::websocket; // из пространства имен boost::beast::websocket
namespace asio = boost::asio;           // из пространства имен boost::asio
using tcp = asio::ip::tcp;

struct Color
{
    Color() : r(0), g(0), b(0) {}
    Color(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {}
    uint8_t r, g, b;
};

// Сериализация Color в JSON
inline void to_json(nlohmann::json &j, const Color &color)
{
    j = nlohmann::json{{"r", color.r}, {"g", color.g}, {"b", color.b}};
}

// Десериализация Color из JSON
inline void from_json(const nlohmann::json &j, Color &color)
{
    j.at("r").get_to(color.r);
    j.at("g").get_to(color.g);
    j.at("b").get_to(color.b);
}

class ClientNetworkService
{
public:
    ClientNetworkService(std::shared_ptr<asio::io_context> ioPtr) : _ioPtr(ioPtr), _ws(*ioPtr) {};
    ~ClientNetworkService() = default;

    void connectToServer(QString domainName, QString port);

    bool tryConnectToSession(QString session); /*{ return true;}*/                                   // -> getGrid(session) и если гуд то _currentSessionId записываем
    std::shared_ptr<QVector<QVector<QColor>>> getGrid(); /* {return QVector<QVector<QColor>> {}; }*/ // getGrid(_currentSessionId)
    bool setPixel(size_t x, size_t y, QColor color); /*{ return true; }*/                            // -> по _currentSessionId ставим пиксель в грид там
    QString createNewGame(uint height, uint width);                                                  /*{ return "1234567890"; }*/

private:
    std::shared_ptr<QVector<QVector<QColor>>> _convertToQVector(const std::vector<std::vector<Color>> &data);
    std::shared_ptr<QVector<QVector<QColor>>> _getGrid(std::string session);

private:
    std::shared_ptr<asio::io_context> _ioPtr;
    QString _currentSessionID;
    websocket::stream<tcp::socket> _ws;
    bool _connected = false;
};
// =======
//     ClientNetworkService(/* args */);
//     ~ClientNetworkService();
//     void connectToServer();
//     std::vector<std::vector<QColor>> getGrid(std::string session_id);
//     bool setPixel(size_t x, size_t y, QColor color);
//     std::string createNewGame(size_t height, size_t width);
// };

#endif