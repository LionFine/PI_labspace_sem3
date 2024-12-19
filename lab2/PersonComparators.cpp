#include "PersonComparators.h"

int CompareByFirstName(const Person& a, const Person& b) {
    if (a.firstName < b.firstName) return -1;
    if (a.firstName > b.firstName) return 1;
    return 0;
}

int CompareByLastName(const Person& a, const Person& b) {
    if (a.lastName < b.lastName) return -1;
    if (a.lastName > b.lastName) return 1;
    return 0;
}

int CompareByBirthYear(const Person& a, const Person& b) {
    if (a.birthYear < b.birthYear) return -1;
    if (a.birthYear > b.birthYear) return 1;
    return 0;
}

int CompareByHeight(const Person& a, const Person& b) {
    if (a.height < b.height) return -1;
    if (a.height > b.height) return 1;
    return 0;
}

int CompareByWeight(const Person& a, const Person& b) {
    if (a.weight < b.weight) return -1;
    if (a.weight > b.weight) return 1;
    return 0;
}
