#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace ah {
    class AppConfig;
    struct DataPoint;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(const ah::AppConfig* config, QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void StartSession(QString port);
    void StopSession();
    void RunSession(QString filename);

public slots:
    void OnNewPoint(ah::DataPoint point);

private:
    void InitSeries();
    void InitGraphicsView();
    void InitPortsCombobox();

    void UpdateChart(const ah::DataPoint& point);
    void UpdateGraphicsView(const ah::DataPoint& point);

    void OnStartSessionClicked();
    void OnStopSessionClicked();
    void OnRunSessionClicked();
    void OnSessionSelectorClicked();
    void OnRefreshPorts();

    void ClearChart();

private:
    Ui::MainWindow *ui;
    const ah::AppConfig* _config = nullptr;

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
