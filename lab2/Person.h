#ifndef PERSON_H
#define PERSON_H

#include <string>

struct Person {
    std::string firstName;
    std::string lastName;
    int birthYear;
    double height;
    double weight;
    std::string email;
    std::string phoneNumber;

    Person(std::string fn, std::string ln, int by, double h, double w, std::string em = "", std::string phone = "")
            : firstName(std::move(fn)), lastName(std::move(ln)),
              birthYear(by), height(h), weight(w),
              email(std::move(em)), phoneNumber(std::move(phone)) {}

    void swap(Person& other) {
        using std::swap;
        swap(firstName, other.firstName);
        swap(lastName, other.lastName);
        swap(birthYear, other.birthYear);
        swap(height, other.height);
        swap(weight, other.weight);
        swap(email, other.email);
        swap(phoneNumber, other.phoneNumber);
    }
};


#endif // PERSON_H
