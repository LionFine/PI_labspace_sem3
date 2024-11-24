#include "test.h"
#include "LinkedList.h"
#include "SmrtPtr.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <memory>
#include <fstream>
#include <iomanip>

void TestAppend() {
    LinkedList<int> list;
    list.Append(10);
    list.Append(20);
    if (list.GetLength() == 2 && list.Get(0) == 10 && list.Get(1) == 20) {
        std::cout << "TestAppend passed.\n";
    } else {
        std::cout << "TestAppend failed.\n";
    }
}

void TestPrepend() {
    LinkedList<int> list;
    list.Prepend(10);
    list.Prepend(20);
    if (list.GetLength() == 2 && list.Get(0) == 20 && list.Get(1) == 10) {
        std::cout << "TestPrepend passed.\n";
    } else {
        std::cout << "TestPrepend failed.\n";
    }
}

void TestInsertAt() {
    LinkedList<int> list;
    list.Append(10);
    list.Append(30);
    list.InsertAt(20, 1);
    if (list.GetLength() == 3 && list.Get(1) == 20) {
        std::cout << "TestInsertAt passed.\n";
    } else {
        std::cout << "TestInsertAt failed.\n";
    }
}

void TestGetSubsequence() {
    LinkedList<int> list;
    list.Append(10);
    list.Append(20);
    list.Append(30);
    SmrtPtr<Sequence<int>> subseq = list.GetSubsequence(1, 2);
    LinkedList<int>* sublist = dynamic_cast<LinkedList<int>*>(subseq.get());
    if (sublist && sublist->GetLength() == 2 && sublist->Get(0) == 20 && sublist->Get(1) == 30) {
        std::cout << "TestGetSubsequence passed.\n";
    } else {
        std::cout << "TestGetSubsequence failed.\n";
    }
}


void TestConcat() {
    SmrtPtr<LinkedList<int>> list1(new LinkedList<int>());
    list1->Append(10);
    list1->Append(20);
    SmrtPtr<LinkedList<int>> list2(new LinkedList<int>());
    list2->Append(30);
    list2->Append(40);
    SmrtPtr<Sequence<int>> concatResult = list1->Concat(list2);

    if (concatResult->GetLength() == 4 &&
        concatResult->Get(0) == 10 &&
        concatResult->Get(1) == 20 &&
        concatResult->Get(2) == 30 &&
        concatResult->Get(3) == 40) {
        std::cout << "TestConcat passed.\n";
    } else {
        std::cout << "TestConcat failed.\n";
    }
}

void TestExceptions() {
    LinkedList<int> list;
    try {
        list.Get(0);
        std::cout << "TestExceptions failed (no exception on Get from empty list).\n";
    } catch (const std::out_of_range&) {
        std::cout << "TestExceptions passed (Get from empty list throws exception).\n";
    }

    list.Append(10);
    try {
        list.Get(5);
        std::cout << "TestExceptions failed (no exception on invalid index).\n";
    } catch (const std::out_of_range&) {
        std::cout << "TestExceptions passed (invalid index throws exception).\n";
    }
}

void TestSmrtPtrBasic() {
    SmrtPtr<int> ptr1(new int(10));
    std::cout << "Value in SmrtPtr: " << *ptr1 << "\n";
}

void TestSmrtPtrCopyAndAssign() {
    SmrtPtr<int> ptr1(new int(10));
    SmrtPtr<int> ptr2 = ptr1;
    SmrtPtr<int> ptr3;
    ptr3 = ptr1;
    std::cout << "Copy and Assign Test: " << *ptr1 << ", " << *ptr2 << ", " << *ptr3 << "\n";
}

void runSmrtPtrTests() {
    std::cout << "Running SmrtPtr basic tests...\n";
    TestSmrtPtrBasic();
    TestSmrtPtrCopyAndAssign();
    std::cout << "SmrtPtr tests completed.\n";
}

// время
double measureExecutionTime(const std::function<void()>& func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;
    return elapsed.count();
}

void printPerformanceResults(
        const std::vector<int>& elementCounts,
        const std::vector<double>& customTimes,
        const std::vector<double>& standardTimes
) {
    std::cout << "\nPerformance Test Results:\n";
    std::cout << std::left << std::setw(15) << "Element Count"
              << std::setw(20) << "SmrtPtr Time (ms)"
              << std::setw(20) << "std::shared_ptr Time (ms)"
              << std::setw(15) << "Difference (%)\n";
    std::cout << std::string(70, '-') << "\n";

    for (size_t i = 0; i < elementCounts.size(); i++) {
        double difference = 100.0 * (customTimes[i] - standardTimes[i]) / standardTimes[i];
        std::cout << std::left << std::setw(15) << elementCounts[i]
                  << std::setw(20) << std::fixed << std::setprecision(2) << customTimes[i]
                  << std::setw(20) << standardTimes[i]
                  << std::setw(15) << difference << "%\n";
    }
}

void saveResultsToCSV(const std::string& filename, const std::vector<int>& elementCounts,
                      const std::vector<double>& customTimes, const std::vector<double>& standardTimes) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << "Element Count,SmrtPtr Time (ms),std::shared_ptr Time (ms),Difference (%)\n";
        for (size_t i = 0; i < elementCounts.size(); i++) {
            double difference = 100.0 * (customTimes[i] - standardTimes[i]) / standardTimes[i];
            file << elementCounts[i] << "," << std::fixed << std::setprecision(2)
                 << customTimes[i] << "," << standardTimes[i] << "," << difference << "\n";
        }
        file.close();
        std::cout << "Results saved to " << filename << "\n";
    } else {
        std::cerr << "Failed to open file for writing: " << filename << "\n";
    }
}

// Нагрузочный тест
void runPerformanceTests() {
    const std::vector<int> testSizes = {10, 1000, 10000, 100000, 1000000}; // Массив тестовых размеров
    std::vector<double> smrtPtrTimes, sharedPtrTimes;
    for (int n : testSizes) {
        std::cout << "Testing with " << n << " elements...\n";

        double smrtPtrTime = measureExecutionTime([&]() {
            std::vector<SmrtPtr<int>> smrtPtrs;
            for (int i = 0; i < n; ++i) {
                smrtPtrs.push_back(SmrtPtr<int>(new int(i)));
            }
        });
        smrtPtrTimes.push_back(smrtPtrTime);

        double sharedPtrTime = measureExecutionTime([&]() {
            std::vector<std::shared_ptr<int>> sharedPtrs;
            for (int i = 0; i < n; ++i) {
                sharedPtrs.push_back(std::shared_ptr<int>(new int(i)));
            }
        });
        sharedPtrTimes.push_back(sharedPtrTime);
    }


    printPerformanceResults(testSizes, smrtPtrTimes, sharedPtrTimes);
    saveResultsToCSV("performance_results.csv", testSizes, smrtPtrTimes, sharedPtrTimes);
}

void runTestsAndDisplayResults() {
    std::cout << "Running LinkedList functional tests...\n";
    TestAppend();
    TestPrepend();
    TestInsertAt();
    TestGetSubsequence();
    TestConcat();
    TestExceptions();

    std::cout << "Running SmrtPtr tests...\n";
    runSmrtPtrTests();

    std::cout << "Running performance tests...\n";
    runPerformanceTests();

    std::cout << "All tests completed.\n";
}
