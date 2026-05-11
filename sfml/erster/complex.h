#pragma once

#include <cmath>
#include <iostream>

struct Complex {
    double real; 
    double imag;

    Complex() = default;
    Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}

    Complex operator-() const;
    Complex zeta(double g) const;
    double abs() const;
    Complex conjugate() const;
    Complex exp() const; 
    Complex ln() const;
};


std::istream& operator>>(std::istream& is, Complex& c);
std::ostream& operator<<(std::ostream& os, const Complex& c);


Complex operator+(const Complex& c1, const Complex& c2);
Complex operator-(const Complex& c1, const Complex& c2);
Complex operator*(const Complex& c1, const Complex& c2);
Complex operator/(const Complex& c1, const Complex& c2);

Complex operator^(const Complex& c, const Complex& exponent);
Complex operator^(const Complex& c, double exponent);


bool operator==(const Complex& c1, const Complex& c2);
bool operator!=(const Complex& c1, const Complex& c2);

inline constexpr double EPSILON = 1e-10;

