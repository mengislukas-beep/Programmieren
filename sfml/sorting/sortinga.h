#pragma once
#include <SFML/Graphics.hpp>

bool isSorted(const std::vector<int>& data);

void bubbleSort2(std::vector<int>& data, sf::RenderWindow& window);
void bubbleSort2_with_sound(std::vector<int>& data, sf::RenderWindow& window);
void bubbleSort1(std::vector<int>& data, sf::RenderWindow& window);
void bubbleSort1_with_sound(std::vector<int>& data, sf::RenderWindow& window);

//void selectionSort(std::vector<int>& data, sf::RenderWindow& window);

//void insertionSort(std::vector<int>& data, sf::RenderWindow& window);