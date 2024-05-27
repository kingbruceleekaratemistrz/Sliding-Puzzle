#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "tile.h"

class Board
{
private:
    const int kSize_;
    const int kEmptyTileValue_;
    std::vector<Tile> tiles_;
public:
    Board(int size);

    const int& getSize() const;
    std::vector<int> getTilesValues() const;
    void initializeNewGame();
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
