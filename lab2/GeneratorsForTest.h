#ifndef GENERATOR_H
#define GENERATOR_H

#include <vector>
#include "Person.h"
#include "../lab1/SmrtPtr.h"
#include "../lab1/LinkedList.h"

class GeneratorForTest {
public:
    static SmrtPtr<LinkedList<Person>> GenerateRandom(int size, const std::vector<std::string>& firstNames,
                                                      const std::vector<std::string>& lastNames);
    static SmrtPtr<LinkedList<Person>> GenerateDescending(int size, const std::vector<std::string>& firstNames,
                                                          const std::vector<std::string>& lastNames);
    static SmrtPtr<LinkedList<Person>> GenerateIdentical(int size, const Person& templatePerson);
};

#endif // GENERATOR_H
