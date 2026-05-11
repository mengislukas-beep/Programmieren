#include "sortinga.h"
#include <SFML/Audio.hpp>
#include <vector>
#include "print.h"
#include <thread>
#include <chrono>
#include "sound.h"

#include <SFML/Graphics.hpp>


bool isSorted(const std::vector<int>& data)
{
    for (size_t i = 1; i < data.size(); ++i)
    {
        if (data[i - 1] > data[i])
            return false;
    }
    return true;
}


void bubbleSort2(std::vector<int>& data, sf::RenderWindow& window)
{
    int n = data.size();
    bool swapped;

    for (int i = 0; i < n - 1; i++)
    {
        swapped = false;

        for (int j = 0; j < n - i - 1; j++)
        {
            if (data[j] > data[j + 1])
            {
                std::swap(data[j], data[j + 1]);
                swapped = true;
            }
        }

        // Nur einmal pro äußerem Durchlauf neu zeichnen
        window.clear();
        print(window, data, 0, window.getSize().x, sf::Color::White);
         // Kurze Pause, damit der Ton hörbar ist

        window.display();

        // Wenn nichts mehr getauscht wurde, ist schon sortiert
        if (!swapped)
            break;
    }
}

void bubbleSort1(std::vector<int>& data, sf::RenderWindow& window)
{
    int n = data.size();

    for (int i = 0; i < n - 1; i++)
    {

        for (int j = 0; j < n - i - 1; j++)
        {
            if (data[j] > data[j + 1])
            {
                window.clear();
                print(window, data, 0, window.getSize().x, sf::Color::White);
                window.display();
                std::swap(data[j], data[j + 1]);
                
            }
        }
    }
}

void bubbleSort2_with_sound(std::vector<int>& data, sf::RenderWindow& window)
{
    int n = data.size();
    bool swapped;
    Sound sound;

    for (int i = 0; i < n - 1; i++)
    {
        swapped = false;

        for (int j = 0; j < n - i - 1; j++)
        {
            if (data[j] > data[j + 1])
            {
                std::swap(data[j], data[j + 1]);
                swapped = true;
            }
        }

        // Nur einmal pro äußerem Durchlauf neu zeichnen
        window.clear();
        print(window, data, 0, window.getSize().x, sf::Color::White);
        
        float frequency = sound.getFrequency(n - data[n - i - 1], n);
        sound.play(frequency); 
        std::this_thread::sleep_for(std::chrono::milliseconds(20));

        window.display();

        // Wenn nichts mehr getauscht wurde, ist schon sortiert
        if (!swapped)
            break;
    }
}

void bubbleSort1_with_sound(std::vector<int>& data, sf::RenderWindow& window)
{
    int n = data.size();

    for (int i = 0; i < n - 1; i++)
    {

        for (int j = 0; j < n - i - 1; j++)
        {
            if (data[j] > data[j + 1])
            {
                window.clear();
                print(window, data, 0, window.getSize().x, sf::Color::White);
                window.display();
                Sound sound;
                float frequency = sound.getFrequency(data[j], n);
                sound.play(frequency);
                std::this_thread::sleep_for(std::chrono::milliseconds(20));
                std::swap(data[j], data[j + 1]);
                
            }
        }
    }
}