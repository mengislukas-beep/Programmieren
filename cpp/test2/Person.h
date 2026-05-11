#pragma once
#include <string>

class Person {
private:
    std::string name;
    int alter;

public:
    Person(std::string name, int alter);
    void vorstellen() const;
};