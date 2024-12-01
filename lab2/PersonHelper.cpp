#include "PersonHelper.h"
#include <fstream>
#include <sstream>

SmrtPtr<LinkedList<Person>> readPersonData(const std::string& filePath) {
    SmrtPtr<LinkedList<Person>> people(new LinkedList<Person>());
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filePath);
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream stream(line);
        std::string firstName, lastName, email, phoneNumber;
        int birthYear;
        double height, weight;

        std::getline(stream, firstName, ',');
        std::getline(stream, lastName, ',');
        stream >> birthYear;
        stream.ignore(1);
        stream >> height;
        stream.ignore(1);
        stream >> weight;
        stream.ignore(1);
        std::getline(stream, email, ',');
        std::getline(stream, phoneNumber, ',');

        people->Append(Person(firstName, lastName, birthYear, height, weight, email, phoneNumber));
    }
    return people;
}

void writePersonData(const std::string& filePath, const SmrtPtr<LinkedList<Person>>& people) {
    std::ofstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filePath);
    }

    for (int i = 0; i < people->GetLength(); ++i) {
        const Person& person = people->Get(i);
        file << person.firstName << ","
             << person.lastName << ","
             << person.birthYear << ","
             << person.height << ","
             << person.weight << ","
             << person.email << ","
             << person.phoneNumber << "\n";
    }
}

