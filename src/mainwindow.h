#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QSharedPointer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class AppConfig;
class IDataProvider;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(AppConfig* config, QWidget *parent = nullptr);
    ~MainWindow();

    void SetDataProvider(const IDataProvider* dataProvider);

public slots:
    void OnDataUpdated();

private:
    void InitSeries();

private:
    Ui::MainWindow *ui;
    AppConfig* _config = nullptr;

    QLineSeries* _pitchSeries = nullptr;
    QLineSeries* _rollSeries = nullptr;
    QChart* _chart = nullptr;
    QValueAxis* _axisX = nullptr;
    QValueAxis* _axisY = nullptr;
    QChartView* _chartView = nullptr;

    const IDataProvider* _dataProvider = nullptr;
};
#endif // MAINWINDOW_H
