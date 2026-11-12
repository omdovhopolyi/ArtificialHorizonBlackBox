#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QSharedPointer>

#include <QTimer>

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
    MainWindow(AppConfig* config, QWidget *parent = nullptr);
    ~MainWindow();

    void SetDataProvider(const IDataProvider* dataProvider);

signals:
    void StartSession();
    void StopSession();
    void RunSession(QString filename);

public slots:
    void OnDataUpdated();
    void OnDebugTimer();

private:
    void InitSeries();
    void InitGraphicsView();

    void UpdateChart(const DataPoint& point);
    void UpdateGraphicsView(const DataPoint& point);

    void OnStartSessionClicked();
    void OnStopSessionClicked();
    void OnRunSessionClicked();
    void OnSessionSelectorClicked();

private:
    Ui::MainWindow *ui;
    AppConfig* _config = nullptr;

    QLineSeries* _pitchSeries = nullptr;
    QLineSeries* _rollSeries = nullptr;
    QChart* _chart = nullptr;
    QValueAxis* _axisX = nullptr;
    QValueAxis* _axisY = nullptr;
    QChartView* _chartView = nullptr;

    QGraphicsPixmapItem* _artificialHorizonPixmap = nullptr;

    const IDataProvider* _dataProvider = nullptr;

    QTimer _debugTimer;
};
#endif // MAINWINDOW_H
