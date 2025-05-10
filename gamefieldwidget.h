#pragma once
#ifndef GAMEFIELDWIDGET_H
#define GAMEFIELDWIDGET_H
#include "ClientNetworkService.h"

#include <QWidget>
#include <QColor>
#include <QPoint>

class GameFieldWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GameFieldWidget(std::shared_ptr<ClientNetworkService> clientService, uint width, uint height, QWidget *parent = nullptr);

public slots:
    void onSelectColor();

protected:
    void paintEvent(QPaintEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void timerEvent(QTimerEvent* event) override;

private:
    void moveCursor(int dx, int dy);
    void colorPixel();

private:
    QVector<QVector<QColor>> _field;

    int _cursorX;
    int _cursorY;
    int _startX;
    int _startY;

    int _visibleWidth;
    int _visibleHeight;

    int _cellSize;

    int _timerId;

    bool _spacePressed;
    QColor _currentColor;

    std::shared_ptr<ClientNetworkService> _clientService;
};


#endif // GAMEFIELDWIDGET_H
