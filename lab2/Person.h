#ifndef PERSON_H
#define PERSON_H

#include <string>

struct Person {
    std::string firstName;
    std::string lastName;
    int birthYear;
    double height;
    double weight;

    Person(std::string fn, std::string ln, int by, double h, double w)
            : firstName(std::move(fn)), lastName(std::move(ln)), birthYear(by), height(h), weight(w) {}
};

#endif // PERSON_H
