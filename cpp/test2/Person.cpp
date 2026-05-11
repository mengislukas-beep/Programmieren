#include "Person.h"
#include <iostream>

Person::Person(std::string name, int alter) {
    this->name = name;
    this->alter = alter;
}

void Person::vorstellen() const {
    std::cout << "Ich bin " << name
              << " und " << alter << " Jahre alt.\n";
}