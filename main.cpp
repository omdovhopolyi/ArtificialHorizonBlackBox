#include "mainwindow.h"

#include <QApplication>

#include "maincontroller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainController mainController;
    MainWindow mainWindow;

    mainController.Init();

    QObject::connect(&mainController, &MainController::DataReceived, &mainWindow, &MainWindow::OnDataUpdated);

    mainWindow.show();
    return a.exec();
}
