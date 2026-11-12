#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QVBoxLayout>
#include <QFileDialog>

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
    InitGraphicsView();

    //_debugTimer.start(100);

    //connect(&_debugTimer, &QTimer::timeout, this, &MainWindow::OnDebugTimer);

    connect(ui->StartSessonButton, &QPushButton::released, this, &MainWindow::OnStartSessionClicked);
    connect(ui->StopSessionButton, &QPushButton::released, this, &MainWindow::OnStopSessionClicked);
    connect(ui->RunSessionButton, &QPushButton::released, this, &MainWindow::OnRunSessionClicked);
    connect(ui->ChooseFileButton, &QPushButton::released, this, &MainWindow::OnSessionSelectorClicked);
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
            const auto& lastPoint = dataPoints.back();

            UpdateChart(lastPoint);
            UpdateGraphicsView(lastPoint);
        }
    }
}

void MainWindow::OnDebugTimer()
{
    auto rotation = _artificialHorizonPixmap->rotation();
    rotation += 1.f;
    _artificialHorizonPixmap->setRotation(rotation);
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

void MainWindow::InitGraphicsView()
{
    auto* scene = new QGraphicsScene(this);

    _artificialHorizonPixmap = scene->addPixmap(
        QPixmap(":/images/assets/ah_back_20.png")
    );

    auto pixmapTarget = scene->addPixmap(QPixmap(":/images/assets/ah_target.png"));

    ui->ArtificialHorizonView->setScene(scene);

    _artificialHorizonPixmap->setTransformOriginPoint(
        _artificialHorizonPixmap->boundingRect().center()
    );

    pixmapTarget->setTransformOriginPoint(
        pixmapTarget->boundingRect().center()
    );

    //_artificialHorizonPixmap->setRotation(45);
    //_artificialHorizonPixmap->setScale(2.0);
}

void MainWindow::UpdateChart(const DataPoint &point)
{
    if (_pitchSeries->count() > _config->GetTimeRange()) {
        _pitchSeries->remove(0);
        _rollSeries->remove(0);
    }

    _pitchSeries->append(point.timestamp, point.pitch);
    _rollSeries->append(point.timestamp, point.roll);

    const auto& firstPoint = _pitchSeries->points().front();
    const auto xValueStart = static_cast<int>(firstPoint.x());
    const auto xValueEnd = xValueStart + _config->GetTimeRange();

    _axisX->setRange(xValueStart, xValueEnd);
}

void MainWindow::UpdateGraphicsView(const DataPoint &point)
{
    _artificialHorizonPixmap->setRotation(point.roll);
}

void MainWindow::OnStartSessionClicked()
{
    emit StartSession();
}

void MainWindow::OnStopSessionClicked()
{
    emit StopSession();
}

void MainWindow::OnRunSessionClicked()
{
    QString filename = ui->FileNameView->text();
    emit RunSession(filename);
}

void MainWindow::OnSessionSelectorClicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Select session");
    if (!filePath.isEmpty()) {
        QString filename = QFileInfo(filePath).fileName();
        ui->FileNameView->setText(filename);
    }
}
