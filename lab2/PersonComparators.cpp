#include "PersonComparators.h"

// Сравнение по имени (firstName) в алфавитном порядке
int CompareByFirstName(const Person& a, const Person& b) {
    if (a.firstName < b.firstName) return -1;
    if (a.firstName > b.firstName) return 1;
    return 0;
}

// Сравнение по фамилии (lastName) в алфавитном порядке
int CompareByLastName(const Person& a, const Person& b) {
    if (a.lastName < b.lastName) return -1;
    if (a.lastName > b.lastName) return 1;
    return 0;
}

// Сравнение по году рождения (birthYear) - по возрастанию
int CompareByBirthYear(const Person& a, const Person& b) {
    if (a.birthYear < b.birthYear) return -1;
    if (a.birthYear > b.birthYear) return 1;
    return 0;
}

// Сравнение по росту (height) - по возрастанию
int CompareByHeight(const Person& a, const Person& b) {
    if (a.height < b.height) return -1;
    if (a.height > b.height) return 1;
    return 0;
}

// Сравнение по весу (weight) - по возрастанию
int CompareByWeight(const Person& a, const Person& b) {
    if (a.weight < b.weight) return -1;
    if (a.weight > b.weight) return 1;
    return 0;
}

// Сравнение по email в алфавитном порядке
int CompareByEmail(const Person& a, const Person& b) {
    if (a.email < b.email) return -1;
    if (a.email > b.email) return 1;
    return 0;
}

// Сравнение по номеру телефона (phoneNumber) в алфавитном порядке
int CompareByPhoneNumber(const Person& a, const Person& b) {
    if (a.phoneNumber < b.phoneNumber) return -1;
    if (a.phoneNumber > b.phoneNumber) return 1;
    return 0;
}
