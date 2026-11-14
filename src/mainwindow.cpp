#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QVBoxLayout>
#include <QFileDialog>

#include "appconfig.h"
#include "datapoint.h"

MainWindow::MainWindow(const ah::AppConfig* config, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _config(config)
{
    Q_ASSERT(_config);

    ui->setupUi(this);

    InitSeries();
    InitGraphicsView();

    connect(ui->StartSessonButton, &QPushButton::released, this, &MainWindow::OnStartSessionClicked);
    connect(ui->StopSessionButton, &QPushButton::released, this, &MainWindow::OnStopSessionClicked);
    connect(ui->RunSessionButton, &QPushButton::released, this, &MainWindow::OnRunSessionClicked);
    connect(ui->ChooseFileButton, &QPushButton::released, this, &MainWindow::OnSessionSelectorClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::OnNewPoint(ah::DataPoint point)
{
    UpdateChart(point);
    UpdateGraphicsView(point);
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

    auto backgroundImage = _artificialHorizonPixmap = scene->addPixmap(
        QPixmap(":/images/assets/" + _config->GetHorizonBackgroundStatic()));
    backgroundImage->setTransformOriginPoint(backgroundImage->boundingRect().center());

    _artificialHorizonPixmap = scene->addPixmap(QPixmap(":/images/assets/" + _config->GetHorizonBackgroundDynamic()));
    _artificialHorizonPixmap->setTransformOriginPoint(_artificialHorizonPixmap->boundingRect().center());

    scene->addPixmap(QPixmap(":/images/assets/" + _config->GetHorizonTarget()));

    ui->ArtificialHorizonView->setScene(scene);
}

void MainWindow::UpdateChart(const ah::DataPoint &point)
{
    const auto rangeMax =_axisX->max();
    const bool needMoveTimeRange = (_pitchSeries->count() > 0 && point.timestamp >= rangeMax);

    if (needMoveTimeRange) {
        _axisX->setRange(rangeMax, rangeMax + _config->GetTimeRange());
        _pitchSeries->clear();
        _rollSeries->clear();
    }

    _pitchSeries->append(point.timestamp, point.pitch);
    _rollSeries->append(point.timestamp, point.roll);
}

void MainWindow::UpdateGraphicsView(const ah::DataPoint &point)
{
    const float pitchCorrected = std::min(point.pitch, _config->GetMaxPitch());
    const float pitch = (_config->PixelsPer10Degrees() * (pitchCorrected / 10.f));

    auto origin =_artificialHorizonPixmap->transformOriginPoint();
    origin.setY(origin.x() - pitch);

    _artificialHorizonPixmap->setTransformOriginPoint(origin);

    _artificialHorizonPixmap->setPos({ 0.f, pitch });
    _artificialHorizonPixmap->setRotation(point.roll);
}

void MainWindow::OnStartSessionClicked()
{
    ClearChart();
    emit StartSession();
}

void MainWindow::OnStopSessionClicked()
{
    emit StopSession();
}

void MainWindow::OnRunSessionClicked()
{
    ClearChart();
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

void MainWindow::ClearChart()
{
    _pitchSeries->clear();
    _rollSeries->clear();

    _axisX->setRange(0.f, _config->GetTimeRange());
}
