#ifndef GENERATOR_H
#define GENERATOR_H

#include <vector>
#include "Person.h"

class Generator {
public:
    static std::vector<Person> GenerateRandomPersons(int count);
};

#endif // GENERATOR_H
