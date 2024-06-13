#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "tile.h"

class Board
{
private:
    int size_;
    int empty_tile_value_;
    std::vector<Tile> tiles_;
public:
    Board();

    const int& getSize() const;
    void setSize(int size);
    std::vector<int> getTilesValues() const;
    void initializeNewGame();
    void initializeNewGame(std::vector<int> tiles_values);
    void playMove(int tile_num);
    bool isSolved() const;
private:
    void shuffle();
    void swapTilesValues(Tile &t1, Tile &t2);
    bool areNeighbors(Tile &t1, Tile &t2) const;
    bool isSolvable() const;
    int countInversions() const;
    Tile& getTileByValue(int value);
};

#endif // BOARD_H
