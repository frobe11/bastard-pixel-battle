#include "mainwindow.h"
#include <dotenv.h>
#include <QApplication>

#include "mainwindow.h"
#include "ClientNetworkService.h"


int main(int argc, char *argv[])
{
    dotenv::init(".env");
    const QString DOMAIN = QString::fromUtf8(dotenv::getenv("DOMAIN", "127.0.0.1").c_str());
    const QString PORT = QString::fromUtf8(dotenv::getenv("PORT", "8080").c_str());
    
    std::shared_ptr<asio::io_context> io = std::make_shared<asio::io_context>();
    QApplication a(argc, argv);
    std::shared_ptr<ClientNetworkService> cns = std::make_shared<ClientNetworkService>(io);
    io->run();
    cns->connectToServer(DOMAIN, PORT);
    MainWindow w(cns);
    w.show();
    return a.exec();
}
