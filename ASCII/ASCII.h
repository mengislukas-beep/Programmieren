#pragma once
#include <fstream>
#include <iostream>
#include <vector>




void print(const std::vector<std::vector<int>>& liste, int x = 0, int y = 0) {
    system("clear");
    int m = liste.size();
    int n = liste[0].size();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cout << liste[i][j];
        }
        std::cout << std::endl;
    }
}

std::vector<std::vector<int>> rechteck(int a, int b) {
    std::vector<std::vector<int>> liste; 
}


