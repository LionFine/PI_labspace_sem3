#ifndef TEST_H
#define TEST_H

#include <vector>
#include <string>
#include <functional>

void TestAppend();
void TestPrepend();
void TestInsertAt();
void TestGetSubsequence();
void TestConcat();
void TestExceptions();


void TestSmrtPtrBasic();
void TestSmrtPtrCopyAndAssign();
void TestSmrtPtrSubtype();
void runSmrtPtrTests();


double measureExecutionTime(const std::function<void()>& func);
void runPerformanceTests();


void printPerformanceResults(const std::vector<int>& elementCounts,
                             const std::vector<double>& customTimes,
                             const std::vector<double>& standardTimes);
void saveResultsToCSV(const std::string& filename, const std::vector<int>& elementCounts,
                      const std::vector<double>& customTimes, const std::vector<double>& standardTimes);

void runTestsAndDisplayResults();

#endif // TEST_H
