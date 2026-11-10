#include "mainwindow.h"

#include <QApplication>

#include "maincontroller.h"
#include "appconfig.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    AppConfig config;
    MainController mainController;
    MainWindow mainWindow{ &config };

    mainController.Init(&config);
    mainWindow.SetDataProvider(&mainController);

    QObject::connect(&mainController, &MainController::DataReceived, &mainWindow, &MainWindow::OnDataUpdated);

    mainController.StartReceiver();

    mainWindow.show();
    return a.exec();
}
