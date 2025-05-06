#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "gamewindow.h"

#include <QMessageBox>

MainWindow::MainWindow(std::shared_ptr<ClientNetworkService> clientService, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), _clientService(clientService)
{
    ui->setupUi(this);

    connect(ui->connectButton, &QPushButton::clicked, this, &MainWindow::onConnectClicked);
    connect(ui->createSessionButton, &QPushButton::clicked, this, &MainWindow::onCreateSessionClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onConnectClicked()
{
    QString sessionId = ui->sessionIdEdit->text();

    bool success = _clientService->tryConnectToSession(sessionId);

    if (success)
    {
        goToGameScreen();
    }
    else
    {
        showError("Ошибка подключения к сессии");
    }
}

void MainWindow::onCreateSessionClicked()
{
    std::cout << "onCreateSessionClicked" << std::endl;
    uint width = ui->widthEdit->text().toUInt();
    uint height = ui->heightEdit->text().toUInt();
    std::cout << width << " " << height << std::endl;
    std::cout << (_clientService == nullptr) << std::endl;
    QString newSessionId = _clientService->createNewGame(height, width);

    bool success = true;

    if (success)
    {
        ui->sessionIdEdit->setText(newSessionId);
    }
    else
    {
        showError("Ошибка создания сессии");
    }
}

void MainWindow::showError(const QString &message)
{
    QMessageBox::critical(this, "Ошибка", message);
}

void MainWindow::goToGameScreen()
{
    // это уберем когда подключим уже сервер, оттуда сетку брать будем
    uint width = ui->widthEdit->text().toUInt();
    uint height = ui->heightEdit->text().toUInt();

    GameWindow *gameWindow = new GameWindow(_clientService, width, height);
    gameWindow->show();
    this->close();
}
