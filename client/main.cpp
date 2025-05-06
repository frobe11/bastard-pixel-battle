#include "mainwindow.h"

#include <QApplication>

#include "mainwindow.h"
#include "ClientNetworkService.h"

const QString DOMAIN = "127.0.0.1";
const QString PORT = "9808";

int main(int argc, char *argv[])
{
    std::shared_ptr<asio::io_context> io = std::make_shared<asio::io_context>();
    QApplication a(argc, argv);
    std::shared_ptr<ClientNetworkService> cns = std::make_shared<ClientNetworkService>(io);
    io->run();
    cns->connectToServer(DOMAIN, PORT);
    MainWindow w(cns);
    w.show();
    return a.exec();
}
