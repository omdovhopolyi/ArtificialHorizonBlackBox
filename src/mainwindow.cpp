#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Create a series
    auto* series = new QLineSeries();
    series->setName("First");

    series->append(0, 10);
    series->append(1, 20);
    series->append(2, 15);
    series->append(3, 30);

    auto* series2 = new QLineSeries();
    series2->setName("Second");

    series2->append(0, 15);
    series2->append(1, 25);
    series2->append(2, 20);
    series2->append(3, 30);

    auto* chart = new QChart();
    chart->addSeries(series);
    chart->addSeries(series2);

    auto* axisX = new QValueAxis();
    axisX->setRange(0, 5);
    axisX->setTitleText("X");

    auto* axisY = new QValueAxis();
    axisY->setRange(0, 30);
    axisY->setTitleText("Y");

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    series->attachAxis(axisX);
    series->attachAxis(axisY);

    series2->attachAxis(axisX);
    series2->attachAxis(axisY);

    auto* chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    ui->chartLayout->addWidget(chartView);
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

}
