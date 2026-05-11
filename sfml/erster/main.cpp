#include <SFML/Graphics.hpp>
#include "complex.h"
#include "helper.h"



int main()
{


    Complex c1(34534, 92);
    Complex c2(1, -2);

    Print(c1);
    std::cout << std::endl;
    Print(c2);
    std::cout << std::endl;
    Print(c1 + c2);
    std::cout << std::endl;
    Print(c1 - c2);
    std::cout << std::endl;
    Print(c1 * c2);
    std::cout << std::endl;
    Print(c1 / c2);
    std::cout << std::endl;
    Print(c1 ^ Complex {0,0});
    std::cout << std::endl;
    Print(c1.zeta(10));
    std::cout << " und " << c2.zeta(10) << std::endl;
    Print(c1.exp());
    std::cout << " und " << c2.exp() << std::endl;
    Print(c1.ln());
    std::cout << " und " << c2.ln() << std::endl;



    return 0;
}