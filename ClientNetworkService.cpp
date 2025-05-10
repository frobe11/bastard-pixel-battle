#include "ClientNetworkService.h"
#include <iostream>

void ClientNetworkService::connectToServer(QString domainName, QString port)
{
    try
    {
        tcp::resolver resolver(*_ioPtr);
        std::cout << "preresolve\n";
        auto const results = resolver.resolve(domainName.toStdString(), port.toStdString());
        std::cout << "Resolved\n";
        asio::connect(_ws.next_layer(), results.begin(), results.end());
        std::cout << "Conected\n";

        _ws.handshake(domainName.toStdString(),"/");
        std::cout << "handshaked\n";

        _connected = true;
    }
    catch (std::exception const &e)
    {
        std::cerr << "Error while handshake: " << e.what() << std::endl;
    }
}

bool ClientNetworkService::tryConnectToSession(QString session)
{
    std::cout << "Trying to connect to session" << std::endl;
    auto result = _getGrid(session.toStdString());
    if (result == nullptr)
    {
        std::cout << "FAILURE: connected to session" << std::endl;

        return false;
    }
    std::cout << "SUCSESS: connected to session" << std::endl;
    _currentSessionID = session;
    return true;
}

std::shared_ptr<QVector<QVector<QColor>>> ClientNetworkService::getGrid()
{
    return _getGrid(_currentSessionID.toStdString());
}

bool ClientNetworkService::setPixel(size_t x, size_t y, QColor color)
{
    if (!_connected)
    {
        return false;
    }
    try
    {

        std::ostringstream oss;
        oss << "SETPIXEL" << " " << _currentSessionID.toStdString() << " " << y << " " << x << " " << color.red() << " " << color.green() << " " << color.blue();
        std::string req = oss.str();
        std::cout << req << std::endl;
        _ws.write(asio::buffer(req));
        beast::flat_buffer buffer;
        _ws.read(buffer);

        std::string response = beast::buffers_to_string(buffer.data());
        std::cout << "RESP: " << response << std::endl;

        std::istringstream iss(response);
        std::string status;
        iss >> status;
        if (status == "OK")
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

QString ClientNetworkService::createNewGame(uint height, uint width)
{
    if (!_connected)
    {
        return nullptr;
    }
    try
    {
        std::ostringstream oss;
        oss << "NEWGAME" << " " << height << " " << width;
        std::string req = oss.str();
        std::cout << req << std::endl;
        _ws.write(asio::buffer(req));
        beast::flat_buffer buffer;
        _ws.read(buffer);

        std::string response = beast::buffers_to_string(buffer.data());
        std::cout << "RESP: " << response << std::endl;

        std::istringstream iss(response);
        std::string status;
        std::string sessionId;
        iss >> status;

        if (status == "SESSION_ID")
        {
            iss >> sessionId;
            return QString::fromStdString(sessionId);
        }
        else
        {
            QString *result = new QString();
            return QString::fromStdString("");
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

std::shared_ptr<QVector<QVector<QColor>>> ClientNetworkService::_convertToQVector(const std::vector<std::vector<Color>> &data)
{
    std::shared_ptr<QVector<QVector<QColor>>> result = std::make_shared<QVector<QVector<QColor>>>();

    for (const auto &row : data)
    {
        QVector<QColor> qRow;
        for (const auto &color : row)
        {
            qRow.append(QColor(color.r, color.g, color.b));
        }
        result->append(qRow);
    }

    return result;
}

std::shared_ptr<QVector<QVector<QColor>>> ClientNetworkService::_getGrid(std::string session)
{
    if (!_connected)
    {
        return nullptr;
    }
    try
    {
        std::string req = "GETGRID " + session;
        std::cout << req << std::endl;
        _ws.write(asio::buffer(req));
        beast::flat_buffer buffer;
        _ws.read(buffer);

        std::string response = beast::buffers_to_string(buffer.data());
        std::cout << "RESP: " << response << std::endl;

        std::istringstream iss(response);
        std::string status;
        iss >> status;
        if (status == "GRID")
        {
            std::string json;
            iss >> json;
            try
            {
                std::cout << "start parsing JSON " << std::endl;

                // Парсим JSON в std::vector<std::vector<Color>>
                nlohmann::json json_data = nlohmann::json::parse(json);
                std::vector<std::vector<Color>> colors = json_data.get<std::vector<std::vector<Color>>>();

                std::cout << "JSON parsed " << std::endl;

                // Преобразуем в QVector<QVector<QColor>>
                std::shared_ptr<QVector<QVector<QColor>>> qColors = _convertToQVector(colors);
                std::cout << "converted" << std::endl;

                return qColors;
            }
            catch (const std::exception &e)
            {
                std::cerr << "Error while parsing JSON: " << e.what() << std::endl;
            }
        }
        else
        {
            return nullptr;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
