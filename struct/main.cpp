#include "complex.h"
#include "matrix.h"
#include <iostream>
#include <vector>


int main() {
    Complex c1(1.0, 0.0);
    Complex c2(3.0, 4.0);

    Complex c3 = c1 + c2;
    Complex c4 = c1 * c2;
    Complex c5 = c1 / c2;
    Complex c6 = c1.exp();
    Complex c7 = c1.pow(0);

    c1.print();
    std::cout << std::endl;  
    c2.print();
    std::cout << std::endl;
    c3.print();
    std::cout << std::endl;
    c4.print();
    std::cout << std::endl;
    c5.print();
    std::cout << std::endl;
    c6.print();
    std::cout << std::endl;
    c7.print();
    std::cout << std::endl << std::endl;


    std::vector<Matrix> matrices;
    Matrix m1 = Matrix(2, 2);
    
    std::vector<std::vector<Complex>> data1 = {
        {Complex(3, -1), Complex(6, -2)},
        {Complex(-3, 1),  Complex(-5, 2)}
    };

    for (size_t i = 0; i < m1.rows; ++i) {
        for (size_t j = 0; j < m1.cols; ++j) {
            m1.data[i][j] = data1[i][j];
        }
    }

    Matrix m2 = m1.transpose();
    Matrix m3 = m1 * m2;
    Matrix m4 = m1.adjoint();
    Matrix m5 = m1.rref();


    matrices.push_back(m1);
    matrices.push_back(m2);
    matrices.push_back(m3);
    matrices.push_back(m4);
    matrices.push_back(m5);


    for (const auto& matrix : matrices) {
        matrix.print();
        std::cout << std::endl;
    }

    m1.determinant().print();
    std::cout << std::endl;

    Matrix m6 = m1.inverse();
    m6.print();

    std::cout << std::endl;


    



    return 0;
}