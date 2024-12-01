#include <iostream>
#include <fstream>
#include <chrono>
#include "GeneratorsForTest.h"
#include "MergeSorter.h"
#include "QuickSorter.h"
#include "HeapSort.h"
#include "ShellSorter.h"
#include "PersonComparators.h"

void RunTests(const std::vector<std::string>& firstNames, const std::vector<std::string>& lastNames) {
    const std::vector<int> sizes = {14, 50, 150};
    const Person templatePerson("John", "Doe", 1990, 180.0, 75.0);

    std::ofstream resultsFile("results.txt");
    resultsFile << "Sort type,Field,List type,Size,Time (seconds)\n";

    for (int size : sizes) {
        std::cout << "Testing with size: " << size << "\n";

        auto randomList = GeneratorForTest::GenerateRandom(size, firstNames, lastNames);
        auto descendingList = GeneratorForTest::GenerateDescending(size, firstNames, lastNames);
        auto identicalList = GeneratorForTest::GenerateIdentical(size, templatePerson);

        std::cout << "Gen is ok " << "\n";

        SmrtPtr<ISorter<Person>> mergeSorter(new MergeSorter<Person>());
        SmrtPtr<ISorter<Person>> quickSorter(new QuickSorter<Person>());
        SmrtPtr<ISorter<Person>> heapSorter(new HeapSorter<Person>());
        SmrtPtr<ISorter<Person>> shellSorter(new ShellSorter<Person>());

        for (int field = 1; field <= 5; ++field) {
            int (*cmp)(const Person&, const Person&) = nullptr;
            std::string fieldName;
            switch (field) {
                case 1: cmp = CompareByFirstName; fieldName = "FirstName"; break;
                case 2: cmp = CompareByLastName; fieldName = "LastName"; break;
                case 3: cmp = CompareByBirthYear; fieldName = "BirthYear"; break;
                case 4: cmp = CompareByHeight; fieldName = "Height"; break;
                case 5: cmp = CompareByWeight; fieldName = "Weight"; break;
            }

            // Test MergeSort
            auto start = std::chrono::high_resolution_clock::now();
            mergeSorter->Sort(randomList, cmp);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = end - start;
            resultsFile << "MergeSort," << fieldName << ",Random," << size << "," << elapsed.count() << "\n";

            start = std::chrono::high_resolution_clock::now();
            mergeSorter->Sort(descendingList, cmp);
            end = std::chrono::high_resolution_clock::now();
            elapsed = end - start;
            resultsFile << "MergeSort," << fieldName << ",Descending," << size << "," << elapsed.count() << "\n";

            start = std::chrono::high_resolution_clock::now();
            mergeSorter->Sort(identicalList, cmp);
            end = std::chrono::high_resolution_clock::now();
            elapsed = end - start;
            resultsFile << "MergeSort," << fieldName << ",Identical," << size << "," << elapsed.count() << "\n";

            // Test QuickSort
            start = std::chrono::high_resolution_clock::now();
            quickSorter->Sort(randomList, cmp);
            end = std::chrono::high_resolution_clock::now();
            elapsed = end - start;
            resultsFile << "QuickSort," << fieldName << ",Random," << size << "," << elapsed.count() << "\n";

            start = std::chrono::high_resolution_clock::now();
            quickSorter->Sort(descendingList, cmp);
            end = std::chrono::high_resolution_clock::now();
            elapsed = end - start;
            resultsFile << "QuickSort," << fieldName << ",Descending," << size << "," << elapsed.count() << "\n";

            start = std::chrono::high_resolution_clock::now();
            quickSorter->Sort(identicalList, cmp);
            end = std::chrono::high_resolution_clock::now();
            elapsed = end - start;
            resultsFile << "QuickSort," << fieldName << ",Identical," << size << "," << elapsed.count() << "\n";

            //тест heap
            start = std::chrono::high_resolution_clock::now();
            heapSorter->Sort(randomList, cmp);
            end = std::chrono::high_resolution_clock::now();
            elapsed = end - start;
            resultsFile << "HeapSort," << fieldName << ",Random," << size << "," << elapsed.count() << "\n";

            start = std::chrono::high_resolution_clock::now();
            heapSorter->Sort(descendingList, cmp);
            end = std::chrono::high_resolution_clock::now();
            elapsed = end - start;
            resultsFile << "HeapSort," << fieldName << ",Descending," << size << "," << elapsed.count() << "\n";

            start = std::chrono::high_resolution_clock::now();
            heapSorter->Sort(identicalList, cmp);
            end = std::chrono::high_resolution_clock::now();
            elapsed = end - start;
            resultsFile << "HeapSort," << fieldName << ",Identical," << size << "," << elapsed.count() << "\n";

            //тест ShellSort
            start = std::chrono::high_resolution_clock::now();
            shellSorter->Sort(randomList, cmp);
            end = std::chrono::high_resolution_clock::now();
            elapsed = end - start;
            resultsFile << "ShellSort," << fieldName << ",Random," << size << "," << elapsed.count() << "\n";

            start = std::chrono::high_resolution_clock::now();
            shellSorter->Sort(descendingList, cmp);
            end = std::chrono::high_resolution_clock::now();
            elapsed = end - start;
            resultsFile << "ShellSort," << fieldName << ",Descending," << size << "," << elapsed.count() << "\n";

            start = std::chrono::high_resolution_clock::now();
            shellSorter->Sort(identicalList, cmp);
            end = std::chrono::high_resolution_clock::now();
            elapsed = end - start;
            resultsFile << "ShellSort," << fieldName << ",Identical," << size << "," << elapsed.count() << "\n";

            resultsFile << "\n";
        }
    }

    resultsFile.close();
    std::cout << "Tests completed. Results written to results.txt.\n";
}
