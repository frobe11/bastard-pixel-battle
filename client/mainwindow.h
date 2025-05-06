#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma once

#include <QMainWindow>
#include "ClientNetworkService.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(std::shared_ptr<ClientNetworkService> clientService, QWidget *parent = nullptr);
    ~MainWindow();

private:
    void showError(const QString& message);
    void goToGameScreen();

private slots:
    void onConnectClicked();
    void onCreateSessionClicked();

private:
    Ui::MainWindow *ui;
    std::shared_ptr<ClientNetworkService> _clientService;
};

#endif // MAINWINDOW_H
