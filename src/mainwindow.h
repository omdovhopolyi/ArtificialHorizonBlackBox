#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include "datapoint.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class AppConfig;
class IDataProvider;
struct DataPoint;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(const AppConfig* config, QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void StartSession();
    void StopSession();
    void RunSession(QString filename);

public slots:
    void OnNewPoint(DataPoint point);

private:
    void InitSeries();
    void InitGraphicsView();

    void UpdateChart(const DataPoint& point);
    void UpdateGraphicsView(const DataPoint& point);

    void OnStartSessionClicked();
    void OnStopSessionClicked();
    void OnRunSessionClicked();
    void OnSessionSelectorClicked();

    void ClearChart();

private:
    Ui::MainWindow *ui;
    const AppConfig* _config = nullptr;

    QLineSeries* _pitchSeries = nullptr;
    QLineSeries* _rollSeries = nullptr;
    QChart* _chart = nullptr;
    QValueAxis* _axisX = nullptr;
    QValueAxis* _axisY = nullptr;
    QChartView* _chartView = nullptr;

    QPointF _currentChartRange;

    QGraphicsPixmapItem* _artificialHorizonPixmap = nullptr;
};
#endif // MAINWINDOW_H
