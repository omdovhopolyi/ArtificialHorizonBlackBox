#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QVBoxLayout>

#include "dataprovider.h"
#include "appconfig.h"

MainWindow::MainWindow(AppConfig* config, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _config(config)
{
    Q_ASSERT(_config);

    ui->setupUi(this);

    InitSeries();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SetDataProvider(const IDataProvider *dataProvider)
{
    _dataProvider = dataProvider;
}

void MainWindow::OnDataUpdated()
{
    if (_dataProvider) {
        const auto& dataPoints = _dataProvider->GetData();
        if (!dataPoints.empty()) {

            if (_pitchSeries->count() > _config->GetTimeRange()) {
                _pitchSeries->remove(0);
                _rollSeries->remove(0);
            }

            const auto& lastPoint = dataPoints.back();
            _pitchSeries->append(lastPoint.timestamp, lastPoint.pitch);
            _rollSeries->append(lastPoint.timestamp, lastPoint.roll);

            const auto& firstPoint = _pitchSeries->points().front();
            const auto xValueStart = static_cast<int>(firstPoint.x());
            const auto xValueEnd = xValueStart + _config->GetTimeRange();

            _axisX->setRange(xValueStart, xValueEnd);
        }
    }
}

void MainWindow::InitSeries()
{
    _pitchSeries = new QLineSeries();
    _pitchSeries->setName(_config->GetPitchSeriesName());

    _rollSeries = new QLineSeries();
    _rollSeries->setName(_config->GetRollSeriesName());

    _chart = new QChart();
    _chart->addSeries(_pitchSeries);
    _chart->addSeries(_rollSeries);

    _axisX = new QValueAxis();
    _axisX->setRange(0, _config->GetTimeRange());
    _axisX->setTitleText(_config->GetTimeAxisName());

    _axisY = new QValueAxis();
    _axisY->setRange(0, _config->GetValueRange());
    _axisY->setTitleText(_config->GetValueAxisName());

    _chart->addAxis(_axisX, Qt::AlignBottom);
    _chart->addAxis(_axisY, Qt::AlignLeft);

    _pitchSeries->attachAxis(_axisX);
    _pitchSeries->attachAxis(_axisY);

    _rollSeries->attachAxis(_axisX);
    _rollSeries->attachAxis(_axisY);

    _chartView = new QChartView(_chart);
    _chartView->setRenderHint(QPainter::Antialiasing);

    ui->ChartLayout->addWidget(_chartView);
}
