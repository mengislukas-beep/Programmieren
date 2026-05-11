#pragma once
#include <vector>


class Board {
private:
    std::vector<std::vector<int>> board;

public:
    Board();
    void print() const;
    bool isValidMove(int row, int col, int num) const;
    bool solve();
    void setBoard(const std::vector<std::vector<int>>& newBoard);
};