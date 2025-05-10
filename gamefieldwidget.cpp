#include "gamefieldwidget.h"

#include <QPainter>
#include <QKeyEvent>
#include <QDebug>
#include <QColorDialog>

GameFieldWidget::GameFieldWidget(std::shared_ptr<ClientNetworkService> clientService, uint width, uint height, QWidget *parent)
    : QWidget(parent),
      _cursorX(0),
      _cursorY(0),
      _startX(0),
      _startY(0),
      _visibleWidth(0),
      _visibleHeight(0),
      _cellSize(0),
      _currentColor(QColor(Qt::black)),
      _clientService(clientService),
      _spacePressed(0)
{
   _field = *_clientService->getGrid();
    // _field = QVector<QVector<QColor>> (width, QVector<QColor>(height, QColor(Qt::white)));
    _timerId = startTimer(1000);

    setMinimumSize(500,500);
}

void GameFieldWidget::onSelectColor() {
    QColor newColor = QColorDialog::getColor(Qt::white, this, "select color");

    if (newColor.isValid()) {
        _currentColor = newColor;
    }
}

void GameFieldWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    int w = width();
    int h = height();

    _visibleWidth = std::min(_field.size(), w / 50);
    _visibleHeight = std::min(_field[0].size(), h / 50);

    _cellSize = std::max(50, std::min(w / _visibleWidth, h / _visibleHeight));

    for (int y = 0; y < _visibleHeight; ++y) {
        for (int x = 0; x < _visibleWidth; ++x) {
            int fx = _startX + x;
            int fy = _startY + y;

            QColor color = (fx == _cursorX && fy == _cursorY) ? Qt::red : _field[fx][fy];

            p.fillRect(x * _cellSize, y * _cellSize, _cellSize, _cellSize, color);
            p.setPen(Qt::black);
            p.drawRect(x * _cellSize, y * _cellSize, _cellSize, _cellSize);
        }
    }
}


void GameFieldWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Left:
        moveCursor(-1, 0);
        if(_spacePressed)
           colorPixel();
        break;
    case Qt::Key_Right:
        moveCursor(1, 0);
        if(_spacePressed)
           colorPixel();
        break;
    case Qt::Key_Up:
        moveCursor(0, -1);
        if(_spacePressed)
           colorPixel();
        break;
    case Qt::Key_Down:
        moveCursor(0, 1);
        if(_spacePressed)
           colorPixel();
        break;
    case Qt::Key_Space:
        _spacePressed = true;
        colorPixel();
    }
}

void GameFieldWidget::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Space)
        _spacePressed = false;
}

void GameFieldWidget::timerEvent(QTimerEvent *event)
{
    if( _timerId == event->timerId()) {
       _field = *_clientService->getGrid();
        qDebug() << "Обновили поле";
        update();
    }
}

void GameFieldWidget::colorPixel() {
    _clientService->setPixel(_cursorX, _cursorY, _currentColor);
    _field[_cursorX][_cursorY] = _currentColor;
}

void GameFieldWidget::moveCursor(int dx, int dy)
{
    qDebug() << _cursorX << ' ' << _cursorY ;
    _cursorX = std::max(0, std::min(_cursorX + dx, _field.size() - 1));
    _cursorY = std::max(0, std::min(_cursorY + dy, _field[0].size() - 1));

    if (_cursorX < _startX)
        _startX = _cursorX;
    if (_cursorX >= _startX + _visibleWidth)
        _startX = _cursorX - _visibleWidth + 1;
    if (_cursorY < _startY)
        _startY = _cursorY;
    if (_cursorY >= _startY + _visibleHeight)
        _startY = _cursorY - _visibleHeight + 1;

    _startX = std::max(0, std::min(_startX, _field.size() - _visibleWidth));
    _startY = std::max(0, std::min(_startY, _field[0].size() - _visibleHeight));

    update();
}
