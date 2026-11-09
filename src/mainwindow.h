#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class IDataProvider;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void SetDataProvider(const IDataProvider* dataProvider);

public slots:
    void OnDataUpdated();

private:
    Ui::MainWindow *ui;

    const IDataProvider* _dataProvider = nullptr;
};
#endif // MAINWINDOW_H
