#pragma once
#include <cmath>
#include "complex.h"
#include <vector>


Complex zeta(const Complex& s, int terms = 1000) {
    Complex eta(0.0, 0.0);

    for (int n = 1; n <= terms; ++n) {
        double ln = std::log(n);
        Complex exponent(-s.real * ln, -s.imag * ln);
        Complex term = exponent.exp();

        if (n % 2 == 1) {
            eta = eta + term;
        } else {
            eta = eta - term;
        }
    }

    double ln2 = std::log(2.0);
    Complex exponent((1.0 - s.real) * ln2, (-s.imag) * ln2);
    Complex two_pow = exponent.exp();

    Complex denominator = Complex(1.0, 0.0) - two_pow;

    return eta / denominator;
}


std::vector<Complex> zeta_partial_sums(const Complex& s, int terms = 100) {
    std::vector<Complex> result;
    result.reserve(terms + 1);

    Complex sum(0.0, 0.0);
    result.push_back(sum); // erstes Element = 0

    for (int n = 1; n <= terms; ++n) {
        double ln = std::log(n);

        // n^{-s} = e^{-s ln(n)}
        Complex exponent(-s.real * ln, -s.imag * ln);
        Complex term = exponent.exp();

        sum = sum + term;
        result.push_back(sum);
    }

    return result;
}







