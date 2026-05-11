#pragma once
#include "complex.h"
#include <vector>
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <utility>

struct Matrix {
    std::vector<std::vector<Complex>> data;
    size_t rows;
    size_t cols;

    Matrix(size_t r, size_t c) : rows(r), cols(c), data(r, std::vector<Complex>(c, Complex(0, 0))) {}

private:
    static bool isClose(const Complex& a, const Complex& b, double eps = 1e-9) {
        return std::abs(a.real - b.real) < eps && std::abs(a.imag - b.imag) < eps;
    }

    static bool isZero(const Complex& z, double eps = 1e-9) {
        return std::abs(z.real) < eps && std::abs(z.imag) < eps;
    }

public:
    Matrix operator+(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw std::invalid_argument("Matrix dimensions must match for addition.");
        }

        Matrix result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    Matrix operator-(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw std::invalid_argument("Matrix dimensions must match for subtraction.");
        }

        Matrix result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] - other.data[i][j];
            }
        }
        return result;
    }

    Matrix operator*(const Matrix& other) const {
        if (cols != other.rows) {
            throw std::invalid_argument("Invalid dimensions for matrix multiplication.");
        }

        Matrix result(rows, other.cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < other.cols; ++j) {
                Complex sum(0, 0);
                for (size_t k = 0; k < cols; ++k) {
                    sum = sum + data[i][k] * other.data[k][j];
                }
                result.data[i][j] = sum;
            }
        }
        return result;
    }

    bool operator==(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            return false;
        }

        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                if (!isClose(data[i][j], other.data[i][j])) {
                    return false;
                }
            }
        }
        return true;
    }

    bool operator!=(const Matrix& other) const {
        return !(*this == other);
    }

    void print() const {
        for (const auto& row : data) {
            for (const auto& elem : row) {
                std::cout << "(" << elem.real;
                if (elem.imag >= 0) {
                    std::cout << " + " << elem.imag << "i)";
                } else {
                    std::cout << " - " << -elem.imag << "i)";
                }
                std::cout << " ";
            }
            std::cout << '\n';
        }
    }

    Matrix transpose() const {
        Matrix result(cols, rows);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result.data[j][i] = data[i][j];
            }
        }
        return result;
    }

    Matrix conjugate() const {
        Matrix result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j].conjugate();
            }
        }
        return result;
    }

    Matrix adjoint() const {
        return conjugate().transpose();
    }

    Matrix rref() const {
        Matrix result = *this;
        size_t lead = 0;

        for (size_t r = 0; r < result.rows; ++r) {
            if (lead >= result.cols) {
                break;
            }

            size_t pivotRow = r;
            while (pivotRow < result.rows && isZero(result.data[pivotRow][lead])) {
                ++pivotRow;
            }

            while (pivotRow == result.rows) {
                ++lead;
                if (lead >= result.cols) {
                    return result;
                }
                pivotRow = r;
                while (pivotRow < result.rows && isZero(result.data[pivotRow][lead])) {
                    ++pivotRow;
                }
            }

            if (pivotRow != r) {
                std::swap(result.data[pivotRow], result.data[r]);
            }

            Complex pivot = result.data[r][lead];
            for (size_t j = 0; j < result.cols; ++j) {
                result.data[r][j] = result.data[r][j] / pivot;
            }

            for (size_t i = 0; i < result.rows; ++i) {
                if (i != r) {
                    Complex factor = result.data[i][lead];
                    if (!isZero(factor)) {
                        for (size_t j = 0; j < result.cols; ++j) {
                            result.data[i][j] = result.data[i][j] - factor * result.data[r][j];
                        }
                    }
                }
            }

            ++lead;
        }

        return result;
    }

    Complex determinant() const {
        if (rows != cols) {
            throw std::invalid_argument("Matrix must be square to compute determinant.");
        }

        if (rows == 0) {
            return Complex(1, 0);
        }

        if (rows == 1) {
            return data[0][0];
        }

        if (rows == 2) {
            return data[0][0] * data[1][1] - data[0][1] * data[1][0];
        }

        Complex det(0, 0);

        for (size_t j = 0; j < cols; ++j) {
            Matrix subMatrix(rows - 1, cols - 1);

            for (size_t i = 1; i < rows; ++i) {
                size_t subCol = 0;
                for (size_t k = 0; k < cols; ++k) {
                    if (k == j) {
                        continue;
                    }
                    subMatrix.data[i - 1][subCol] = data[i][k];
                    ++subCol;
                }
            }

            Complex term = data[0][j] * subMatrix.determinant();
            if (j % 2 == 0) {
                det = det + term;
            } else {
                det = det - term;
            }
        }

        return det;
    }

    Matrix inverse() const {
        if (rows != cols) {
            throw std::invalid_argument("Matrix must be square to compute inverse.");
        }

        Matrix augmented(rows, cols * 2);

        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                augmented.data[i][j] = data[i][j];
                augmented.data[i][j + cols] = (i == j) ? Complex(1, 0) : Complex(0, 0);
            }
        }

        augmented = augmented.rref();

        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                Complex expected = (i == j) ? Complex(1, 0) : Complex(0, 0);
                if (!isClose(augmented.data[i][j], expected)) {
                    throw std::runtime_error("Matrix is not invertible.");
                }
            }
        }

        Matrix inv(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                inv.data[i][j] = augmented.data[i][j + cols];
            }
        }

        return inv;
    }

    Matrix pow(int exponent) const {
        if (rows != cols) {
            throw std::invalid_argument("Matrix must be square to compute power.");
        }

        if (exponent < 0) {
            return inverse().pow(-exponent);
        }

        Matrix result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            result.data[i][i] = Complex(1, 0);
        }

        if (exponent == 0) {
            return result;
        }

        Matrix base = *this;
        while (exponent > 0) {
            if (exponent % 2 == 1) {
                result = result * base;
            }
            base = base * base;
            exponent /= 2;
        }

        return result;
    }

    


};