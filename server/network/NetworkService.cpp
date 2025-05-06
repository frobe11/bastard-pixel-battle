#include "NetworkService.h"

void NetworkService::readMessage(std::shared_ptr<websocket::stream<tcp::socket>> ws)
{
    try
    {
        beast::flat_buffer buffer;

        // Выполняем синхронное чтение данных
        ws->read(buffer);
        std::cout << "New message received" << std::endl;

        // Преобразуем данные в строку
        std::string message = beast::buffers_to_string(buffer.data());
        std::string response;
        std::istringstream iss(message);
        std::string command;
        iss >> command;
        std::cout << command << std::endl;

        if (command == "GETGRID")
        {
            // Обработка команды GETGRID
            std::string session_id;
            iss >> session_id;
            std::cout << session_id << std::endl;
            CommandgetGrid cmd(session_id);
            std::cout << "CMD created" << std::endl;

            asio::post(*(_domainThreadPoolPtr), [&cmd]()
                       { cmd.execute(); });
            std::cout << "CMD posted" << std::endl;

            cmd.waitForExecution();
            std::cout << "CMD executed" << std::endl;

            auto result = cmd.getResult();
            if (result == nullptr)
            {
                response = "ERROR WRONG_SESSION_ID";
            }
            else
            {
                nlohmann::json jsonData = result->getGrid();
                std::string serializedData = jsonData.dump();
                response = "GRID " + serializedData;
            }
        }
        else if (command == "NEWGAME")
        {
            // Обработка команды NEWGAME
            size_t height, width;
            iss >> height >> width;
            std::cout << height << " " << width << std::endl;
            CommandNewGame cmd(width, height);
            std::cout << "CMD created" << std::endl;

            asio::post(*(_domainThreadPoolPtr), [&cmd]()
                       { cmd.execute(); });
            std::cout << "CMD posted" << std::endl;

            cmd.waitForExecution();
            std::cout << "CMD executed" << std::endl;

            auto result = cmd.getResult();
            if (result == "")
            {
                response = "ERROR SMTH_WENT_WRONG";
            }
            else
            {
                response = "SESSION_ID " + result;
            }
        }
        else if (command == "SETPIXEL")
        {
            // Обработка команды SETPIXEL
            std::string session_id;
            size_t x, y;
            size_t r, g, b;
            iss >> session_id >> x >> y >> r >> g >> b;

            CommandsetPixel cmd(session_id, x, y, {r, g, b});
            std::cout << "CMD created" << std::endl;

            asio::post(*(_domainThreadPoolPtr), [&cmd]()
                       { cmd.execute(); });
            std::cout << "CMD posted" << std::endl;

            cmd.waitForExecution();
            std::cout << "CMD executed" << std::endl;

            auto result = cmd.getResult();
            if (!result)
            {
                response = "ERROR SMTH_WENT_WRONG";
            }
            else
            {
                response = "OK";
            }
        }
        else
        {
            // Неизвестная команда
            response = "ERROR UNKNOWN_COMMAND";
        }
        std::cout << response << std::endl;

        // Отправляем ответ обратно клиенту
        ws->text(true); // Устанавливаем тип сообщения (текст)
        ws->write(asio::buffer(response));

        // Продолжаем чтение следующего сообщения
        readMessage(ws);
    }
    catch (beast::system_error const &e)
    {
        // Обработка ошибок чтения или записи
        std::cerr << "Error: " << e.code().message() << std::endl;
    }
    catch (std::exception const &e)
    {
        // Обработка других исключений
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void NetworkService::handleNewConnection(std::shared_ptr<websocket::stream<tcp::socket>> ws)
{

    std::cout << "new Handshake handeled" << std::endl;

    try
    {
        // Выполняем синхронный accept
        ws->accept();
        std::cout << "new Handshake accepted" << std::endl;

        // Начинаем чтение сообщений
        this->readMessage(ws);
    }
    catch (beast::system_error const &e)
    {
        // Обработка ошибок handshake
        std::cerr << "Handshake failed: " << e.code().message() << std::endl;
    }
    catch (std::exception const &e)
    {
        // Обработка других исключений
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void NetworkService::startServer(uint16_t port)
{
    try
    {
        // Создаем acceptor для прослушивания входящих соединений
        tcp::acceptor acceptor(*_ioPtr, {tcp::v4(), port});
        std::cout << "Webserver is running on port " << port << std::endl;

        while (true)
        {
            
            // Принимаем входящее TCP-соединение
            tcp::socket socket(*_ioPtr);
            std::cout << "socket initialized" << std::endl;
            acceptor.accept(socket);
            std::cout << "socket accepted" << std::endl;
            // Создаем WebSocket-стрим поверх TCP-сокета
            auto ws = std::make_shared<websocket::stream<tcp::socket>>(std::move(socket));
            std::cout << "websocket created" << std::endl;
            // этo threadpool закидывать нельзя(все потоки заблокируем и конец)
            // Обрабатываем новое соединение в новом потоке
            boost::thread newThread([ws, networkService = this]()
                                    { networkService->handleNewConnection(ws); });
        }
    }
    catch (std::exception const &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
