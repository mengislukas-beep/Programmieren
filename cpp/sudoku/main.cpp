#include "Board.h"
#include <iostream>


int main() {
    Board board;
    std::cout << "Initiales Sudoku-Board:\n";

    board.setBoard({
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},

        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},

        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    });


    board.print();
    std::cout << std::endl;

    if (board.solve()) {
        std::cout << "Gelöstes Sudoku-Board:\n";
        board.print();
    } else {
        std::cout << "Keine Lösung gefunden.\n";
    }

    return 0;
}