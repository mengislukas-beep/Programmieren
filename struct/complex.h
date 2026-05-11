#pragma once
#include <cmath>
#include <iostream>
#include <stdexcept>

struct Complex {
    double real;
    double imag;

    static constexpr double EPS = 1e-9;

    Complex(double r = 0.0, double i = 0.0) : real(clean(r)), imag(clean(i)) {}

private:
    static double clean(double x) {
        return (std::abs(x) < EPS) ? 0.0 : x;
    }

public:
    bool isZero() const {
        return std::abs(real) < EPS && std::abs(imag) < EPS;
    }

    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }

    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imag - other.imag);
    }

    Complex operator*(const Complex& other) const {
        return Complex(
            real * other.real - imag * other.imag,
            real * other.imag + imag * other.real
        );
    }

    Complex operator/(const Complex& other) const {
        double denominator = other.real * other.real + other.imag * other.imag;
        if (std::abs(denominator) < EPS) {
            throw std::runtime_error("Division by zero complex number.");
        }

        return Complex(
            (real * other.real + imag * other.imag) / denominator,
            (imag * other.real - real * other.imag) / denominator
        );
    }

    double magnitude() const {
        return std::hypot(real, imag);
    }

    Complex conjugate() const {
        return Complex(real, -imag);
    }

    Complex exp() const {
        double expReal = std::exp(real);
        return Complex(
            expReal * std::cos(imag),
            expReal * std::sin(imag)
        );
    }

    Complex pow(const Complex& exponent) const {
        if (isZero()) {
            if (exponent.isZero()) {
                throw std::runtime_error("0^0 is undefined.");
            }
            return Complex(0, 0);
        }

        double r = magnitude();
        double theta = std::atan2(imag, real);

        double newR = std::pow(r, exponent.real) * std::exp(-exponent.imag * theta);
        double newTheta = exponent.real * theta + exponent.imag * std::log(r);

        return Complex(
            newR * std::cos(newTheta),
            newR * std::sin(newTheta)
        );
    }

    void print() const {
        std::cout << real;
        if (imag >= 0) {
            std::cout << " + " << imag << "i";
        } else {
            std::cout << " - " << -imag << "i";
        }
    }

    bool operator==(const Complex& other) const {
        return std::abs(real - other.real) < EPS &&
               std::abs(imag - other.imag) < EPS;
    }

    bool operator!=(const Complex& other) const {
        return !(*this == other);
    }

    bool operator<(const Complex& other) const {
        return magnitude() < other.magnitude() - EPS;
    }

    bool operator>(const Complex& other) const {
        return magnitude() > other.magnitude() + EPS;
    }
};