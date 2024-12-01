#include <iostream>
#include <vector>
#include <string>
#include "MergeSorter.h"
#include "QuickSorter.h"
#include "Person.h"
#include "PersonComparators.h"
#include "PersonHelper.h"
#include "Generator.h"
#include "Tests.h"
#include <fstream>

std::vector<std::string> readFileToVector(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filePath);
    }

    std::vector<std::string> data;
    std::string line;
    while (std::getline(file, line)) {
        data.push_back(line);
    }

    return data;
}

void ManualSorting() {
    try {
        SmrtPtr<LinkedList<Person>> sourceData = readPersonData("person_data.txt");

        int count;
        std::cout << "Enter the number of structures to generate: ";
        std::cin >> count;

        if (count > sourceData->GetLength()) {
            std::cerr << "The requested number exceeds the available data\n";
            return;
        }

        SmrtPtr<LinkedList<Person>> randomPeople(new LinkedList<Person>());
        for (int i = 0; i < count; ++i) {
            randomPeople->Append(sourceData->Get(i % sourceData->GetLength()));
        }

        writePersonData("unsorted_people.csv", randomPeople);

        int sortType;
        std::cout << "Choose the sorting method:\n1. MergeSort\n2. QuickSort\nYour choice: ";
        std::cin >> sortType;

        int fieldChoice;
        std::cout << "Choose the field to sort by:\n1. FirstName\n2. LastName\n3. BirthYear\n4. Height\n5. Weight\nYour choice: ";
        std::cin >> fieldChoice;

        SmrtPtr<ISorter<Person>> sorter;

        if (sortType == 1) {
            sorter = SmrtPtr<ISorter<Person>>(new MergeSorter<Person>());
        } else if (sortType == 2) {
            sorter = SmrtPtr<ISorter<Person>>(new QuickSorter<Person>());
        } else {
            std::cerr << "Invalid sorting method choice\n";
            return;
        }

        int (*cmp)(const Person&, const Person&) = nullptr;
        switch (fieldChoice) {
            case 1: cmp = CompareByFirstName; break;
            case 2: cmp = CompareByLastName; break;
            case 3: cmp = CompareByBirthYear; break;
            case 4: cmp = CompareByHeight; break;
            case 5: cmp = CompareByWeight; break;
            default:
                std::cerr << "Invalid field choice\n";
                return;
        }

        sorter->Sort(randomPeople, cmp);

        writePersonData("sorted_people.csv", randomPeople);

        std::cout << "Sorting completed. Results have been saved to sorted_people.csv\n";

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}


int main() {
    try {
        std::cout << "Main Menu:\n";
        std::cout << "1. Manual Sorting\n";
        std::cout << "2. Run Tests\n";
        std::cout << "Your choice: ";
        int choice;
        std::cin >> choice;

        if (choice == 1) {
            ManualSorting();
        } else if (choice == 2) {
            auto firstNames = readFileToVector("first_names.txt");
            auto lastNames = readFileToVector("last_names.txt");
            RunTests(firstNames, lastNames);
        } else {
            std::cerr << "Invalid menu choice\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
