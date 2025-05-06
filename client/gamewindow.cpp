#include "gamewindow.h"
#include <QVBoxLayout>
#include <QAction>
#include <QToolBar>

GameWindow::GameWindow(std::shared_ptr<ClientNetworkService> clientService, uint width, uint height, QWidget *parent)
    : QMainWindow(parent)
{
    _fieldWidget = new GameFieldWidget(clientService, width, height, this);
    _fieldWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    _fieldWidget->setFocusPolicy(Qt::StrongFocus);
    setCentralWidget(_fieldWidget);

    QToolBar* toolBar = addToolBar("toolBar");

    QAction* colorAction = new QAction("select color", this);
    toolBar->addAction(colorAction);

    connect(colorAction, &QAction::triggered, _fieldWidget, &GameFieldWidget::onSelectColor);
}
