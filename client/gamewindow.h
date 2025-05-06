#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include "gamefieldwidget.h"
#include "ClientNetworkService.h"

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(std::shared_ptr<ClientNetworkService> clientService, uint width, uint height, QWidget *parent = nullptr);

private:
    GameFieldWidget* _fieldWidget;
};

#endif // GAMEWINDOW_H
