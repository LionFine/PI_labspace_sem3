#ifndef DISPLAYCHARTS_H
#define DISPLAYCHARTS_H

#include <vector>
#include <string>

void displayCharts(
        const std::vector<int>& elementCounts,
        const std::vector<double>& customTimes,
        const std::vector<double>& standardTimes,
        const std::string& chartTitle,
        const std::string& xAxisTitle,
        const std::string& yAxisTitle

);

#endif // DISPLAYCHARTS_H
