#include "mainwindow.h"

#include <QApplication>

#include "maincontroller.h"
#include "appconfig.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    ah::AppConfig config;
    ah::MainController mainController;
    MainWindow mainWindow{ &config };

    mainController.Init(&config);

    QObject::connect(&app, &QApplication::aboutToQuit, &mainController, &ah::MainController::BeforeAppClosed);

    QObject::connect(&mainController, &ah::MainController::DataReceived, &mainWindow, &MainWindow::OnNewPoint);
    QObject::connect(&mainWindow, &MainWindow::StartSession, &mainController, &ah::MainController::StartSession);
    QObject::connect(&mainWindow, &MainWindow::StopSession, &mainController, &ah::MainController::StopSession);
    QObject::connect(&mainWindow, &MainWindow::RunSession, &mainController, &ah::MainController::RunSession);

    mainWindow.show();
    return app.exec();
}
