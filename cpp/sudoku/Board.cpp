#include "Board.h"
#include <iostream>

Board::Board() {
    board = std::vector<std::vector<int>>(9, std::vector<int>(9, 0));
}

void Board::print() const {
    for (const auto& row : board) {
        for (const auto& num : row) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }
}
bool Board::isValidMove(int row, int col, int num) const {
    for (int i = 0; i < 9; ++i) {
        if (board[row][i] == num || board[i][col] == num ||
            board[row - row % 3 + i / 3][col - col % 3 + i % 3] == num) {
            return false;
        }
    }
    return true;
}
bool Board::solve() {
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (board[row][col] == 0) {
                for (int num = 1; num <= 9; ++num) {
                    if (isValidMove(row, col, num)) {
                        board[row][col] = num;
                        if (solve()) {
                            return true;
                        }
                        board[row][col] = 0;
                    }
                }
                return false;
            }
        }
    }
    return true;
}
void Board::setBoard(const std::vector<std::vector<int>>& newBoard) {
    board = newBoard;
}