#include <iostream>
#include "complex.h"




void Print(const Complex& c) {
    std::cout << c.real << " + " << c.imag << "i";
    return;
}