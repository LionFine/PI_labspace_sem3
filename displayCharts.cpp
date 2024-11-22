#include "displayCharts.h"
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtWidgets/QApplication>
#include <QtCharts/QValueAxis>
#include <QtWidgets/QMainWindow>

void displayCharts(
        const std::vector<int>& elementCounts,
        const std::vector<double>& customTimes,
        const std::vector<double>& standardTimes,
        const std::string& chartTitle,
        const std::string& xAxisTitle,
        const std::string& yAxisTitle
) {
    int argc = 0;
    char* argv[] = { nullptr };
    QApplication app(argc, argv);

    // Создаем график
    QChart* chart = new QChart();
    chart->setTitle(QString::fromStdString(chartTitle));

    // Создаем линии для кастомных и стандартных указателей
    QLineSeries* customSeries = new QLineSeries();
    customSeries->setName("Custom Smart Pointers");

    QLineSeries* standardSeries = new QLineSeries();
    standardSeries->setName("Standard Smart Pointers");

    // Заполняем данные для графиков
    for (size_t i = 0; i < elementCounts.size(); ++i) {
        customSeries->append(elementCounts[i], customTimes[i]);
        standardSeries->append(elementCounts[i], standardTimes[i]);
    }

    // Добавляем серии на график
    chart->addSeries(customSeries);
    chart->addSeries(standardSeries);

    // Создаем оси и добавляем их на график
    QValueAxis* axisX = new QValueAxis();
    axisX->setTitleText(QString::fromStdString(xAxisTitle));
    axisX->setLabelFormat("%i");
    chart->addAxis(axisX, Qt::AlignBottom);
    customSeries->attachAxis(axisX);
    standardSeries->attachAxis(axisX);

    QValueAxis* axisY = new QValueAxis();
    axisY->setTitleText(QString::fromStdString(yAxisTitle));
    chart->addAxis(axisY, Qt::AlignLeft);
    customSeries->attachAxis(axisY);
    standardSeries->attachAxis(axisY);

    // Отображение графика
    QChartView* chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QMainWindow window;
    window.setCentralWidget(chartView);
    window.resize(800, 600);
    window.show();

    app.exec();
}
