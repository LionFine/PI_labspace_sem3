#include "Generator.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Person.h"

std::vector<Person> Generator::GenerateRandomPersons(int count) {
    std::vector<Person> persons;
    srand(static_cast<unsigned>(time(0)));

    for (int i = 0; i < count; ++i) {
        std::string firstName = "FirstName" + std::to_string(i);
        std::string lastName = "LastName" + std::to_string(i);
        int birthYear = 1970 + rand() % 54; // Генерация года рождения между 1970 и 2024
        double height = 150.0 + static_cast<double>(rand() % 50); // Рост от 150 до 200
        double weight = 50.0 + static_cast<double>(rand() % 50);  // Вес от 50 до 100

        persons.emplace_back(firstName, lastName, birthYear, height, weight);
    }

    return persons;
}
