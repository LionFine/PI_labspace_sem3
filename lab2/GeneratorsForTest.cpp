#include "GeneratorsForTest.h"
#include <random>

SmrtPtr<LinkedList<Person>> GeneratorForTest::GenerateRandom(int size, const std::vector<std::string>& firstNames,
                                                      const std::vector<std::string>& lastNames) {
    SmrtPtr<LinkedList<Person>> people(new LinkedList<Person>());
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> nameDist(0, firstNames.size() - 1);
    std::uniform_int_distribution<> lastNameDist(0, lastNames.size() - 1);
    std::uniform_int_distribution<> yearDist(1950, 2000);
    std::uniform_real_distribution<> heightDist(150.0, 200.0);
    std::uniform_real_distribution<> weightDist(50.0, 100.0);

    for (int i = 0; i < size; ++i) {
        people->Append(Person(
                firstNames[nameDist(gen)],
                lastNames[lastNameDist(gen)],
                yearDist(gen),
                heightDist(gen),
                weightDist(gen)
        ));
    }
    return people;
}

SmrtPtr<LinkedList<Person>> GeneratorForTest::GenerateDescending(int size, const std::vector<std::string>& firstNames,
                                                          const std::vector<std::string>& lastNames) {
    SmrtPtr<LinkedList<Person>> people(new LinkedList<Person>());
    for (int i = size; i > 0; --i) {
        people->Append(Person(
                firstNames[i % firstNames.size()],
                lastNames[i % lastNames.size()],
                1950 + i % 51,
                150.0 + i % 50,
                50.0 + i % 50
        ));
    }
    return people;
}

SmrtPtr<LinkedList<Person>> GeneratorForTest::GenerateIdentical(int size, const Person& templatePerson) {
    SmrtPtr<LinkedList<Person>> people(new LinkedList<Person>());
    for (int i = 0; i < size; ++i) {
        people->Append(templatePerson);
    }
    return people;
}
