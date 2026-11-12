#include "mainwindow.h"

#include <QApplication>

#include "maincontroller.h"
#include "appconfig.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    AppConfig config;
    MainController mainController;
    MainWindow mainWindow{ &config };

    mainController.Init(&config);
    mainWindow.SetDataProvider(&mainController);

    QObject::connect(&app, &QApplication::aboutToQuit, &mainController, &MainController::BeforeAppClosed);

    QObject::connect(&mainController, &MainController::DataReceived, &mainWindow, &MainWindow::OnNewPoint);
    QObject::connect(&mainWindow, &MainWindow::StartSession, &mainController, &MainController::StartSession);
    QObject::connect(&mainWindow, &MainWindow::StopSession, &mainController, &MainController::StopSession);

    mainWindow.show();
    return app.exec();
}
