#include "cube.h"



int main() {
    

    Surface filled = make_cube("*%&*$£",100,50,0,20);

    auto screen = to_string(filled);
    clearScreen();

    print(screen);
}