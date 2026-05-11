#include <SFML/Graphics.hpp>
#include "print.h"
#include "sortinga.h"
#include <vector>
#include <random>
#include <numeric>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    if (argc < 2) {
        printf("Bitte eine Zahl angeben!\n");
        return 1;
    }

    int n = atoi(argv[1]);

    sf::RenderWindow window(sf::VideoMode(1800, 800), "Sorting!");
    
    
    std::random_device rd;
    std::mt19937 gen(rd());
    

    std::vector<int> liste(n);
    std::iota(liste.begin(), liste.end(), 1); // Fill with
    std::shuffle(liste.begin(), liste.end(), gen); // Shuffle the vector

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        

         
        
        if (!isSorted(liste)) {
            bubbleSort2_with_sound(liste, window);
            print(window, liste, 0, window.getSize().x, sf::Color::Green);
        }
        else {
            print(window, liste, 0, window.getSize().x, sf::Color::Green);
        }


        window.display();


        
        
    }

    return 0;
}