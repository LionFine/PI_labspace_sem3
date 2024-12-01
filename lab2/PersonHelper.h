#ifndef PERSONHELPER_H
#define PERSONHELPER_H

#include "../lab1/SmrtPtr.h"
#include "../lab1/LinkedList.h"
#include "Person.h"
#include <string>

SmrtPtr<LinkedList<Person>> readPersonData(const std::string& filePath);
void writePersonData(const std::string& filePath, const SmrtPtr<LinkedList<Person>>& people);

#endif // PERSONHELPER_H
