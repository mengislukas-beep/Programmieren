#include "complex.h"
#include <cmath>
#include <iostream>



std::istream& operator>>(std::istream& is, Complex& c) {
    std::cout << "Geben Sie den Realteil ein: ";
    is >> c.real; 
    std::cout << "Geben Sie den Imaginärteil ein: ";
    is >> c.imag;
    return is;
}

Complex operator+(const Complex& c1, const Complex& c2) {
    return Complex(c1.real + c2.real, c1.imag + c2.imag);
}

Complex operator-(const Complex& c1, const Complex& c2) {
    return Complex(c1.real - c2.real, c1.imag - c2.imag);
}

Complex operator*(const Complex& c1, const Complex& c2) {
    return Complex(c1.real * c2.real - c1.imag * c2.imag,
                   c1.real * c2.imag + c1.imag * c2.real);
}

Complex operator/(const Complex& c1, const Complex& c2) {
    double denominator = c2.real * c2.real + c2.imag * c2.imag;
    return Complex((c1.real * c2.real + c1.imag * c2.imag) / denominator,
                   (c1.imag * c2.real - c1.real * c2.imag) / denominator);
}

Complex Complex::operator-() const {
    return Complex(-real, -imag);
}   

bool operator==(const Complex& c1, const Complex& c2) {
    return std::abs(c1.real - c2.real) < EPSILON && std::abs(c1.imag - c2.imag) < EPSILON;
}

bool operator!=(const Complex& c1, const Complex& c2) {
    return !(c1 == c2);
}

Complex operator^(const Complex& c, const Complex& exponent) {
    double r = std::sqrt(c.real * c.real + c.imag * c.imag);
    double theta = std::atan2(c.imag, c.real);
    double new_r = std::pow(r, exponent.real) * std::exp(-exponent.imag * theta);
    double new_theta = exponent.real * theta + exponent.imag * std::log(r);
    return Complex(new_r * std::cos(new_theta), new_r * std::sin(new_theta));
}

Complex operator^(const Complex& c, double exponent) {
    return c ^ Complex(exponent, 0);
}

double Complex::abs() const {
    return std::sqrt(real * real + imag * imag);
}   

Complex Complex::conjugate() const {
    return Complex(real, -imag);
}   

Complex Complex::exp() const {
    double exp_real = std::exp(real);
    return Complex(exp_real * std::cos(imag), exp_real * std::sin(imag));
}

Complex Complex::zeta(double g) const {
    const Complex s = *this;
    const double eps = std::pow(10.0, -g);
    const int maxN = 1000000;

    Complex eta(0, 0);
    for (int n = 1; n <= maxN; ++n) {
        Complex ln_n(std::log((double)n), 0.0);
        Complex term = (-(s * ln_n)).exp(); 

        eta = (n % 2 == 0) ? (eta - term) : (eta + term);

        if (term.abs() < eps) break;
    }

    Complex one(1, 0);
    Complex ln2(std::log(2.0), 0.0);
    Complex denom = one - ((one - s) * ln2).exp();

    return eta / denom;
}

Complex Complex::ln() const {
    double r = this->abs();
    double theta = std::atan2(imag, real);
    return Complex(std::log(r), theta);
}


std::ostream& operator<<(std::ostream& os, const Complex& c) {
    os << c.real;
    if (c.imag > 0) {
        os << " + " << c.imag << "i";
    } else if (c.imag < 0) {
        os << " - " << -c.imag << "i";
    }

    
    return os;
}