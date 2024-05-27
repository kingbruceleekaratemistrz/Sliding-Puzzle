#include "board.h"

#include <random>
#include <cstdlib>
#include <stdexcept>

Board::Board(int size) : kSize_(size), kEmptyTileValue_(size*size)
{
}

void Board::initializeNewGame()
{
    for (int r = 0; r < kSize_; r++)
        for (int c = 0; c < kSize_; c++)
            tiles_.push_back(Tile(r, c));

    do {
        shuffle();
    } while (!isSolvable() || isSolved());
}

const int& Board::getSize() const { return kSize_; }

std::vector<int> Board::getTilesValues() const
{
    std::vector<int> tiles_values;
    for (auto &t : tiles_)
        tiles_values.push_back(t.getValue());
    return tiles_values;
}

void Board::playMove(int tile_num)
{
    Tile &tile_to_move = getTileByValue(tile_num);
    Tile &empty_tile = getTileByValue(kEmptyTileValue_);

    if (areNeighbors(tile_to_move, empty_tile))
        swapTilesValues(tile_to_move, empty_tile);
}

bool Board::isSolved() const
{
    int next_expected_value = 1;
    for (auto &tile : tiles_)
        if (tile.getValue() != next_expected_value++)
            return false;

    return true;
}

void Board::shuffle()
{
    std::vector<bool> value_used(kSize_*kSize_, false);

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1, kSize_*kSize_ - 1);

    for (int i = 0; i < kSize_*kSize_ - 1; i++)
    {
        int value;
        do {
            value = dist(rng);
        } while (value_used[value] == true);

        value_used[value] = true;
        tiles_[i].setValue(value);
    }
    tiles_[kSize_*kSize_ - 1].setValue(kEmptyTileValue_);
}

void Board::swapTilesValues(Tile& t1, Tile&t2)
{
    if (&t1 == &t2) return;
    int tmpValue = t1.getValue();
    t1.setValue(t2.getValue());
    t2.setValue(tmpValue);
}

bool Board::areNeighbors(Tile &t1, Tile &t2) const
{
    if (t1.getRow() == t2.getRow() &&
        abs(t1.getCol() - t2.getCol()) == 1)
        return true;
    else if (t1.getCol() == t2.getCol() &&
             abs(t1.getRow() - t2.getRow()) == 1)
        return true;
    else
        return false;
}

bool Board::isSolvable() const
{
    int inversions = countInversions();

    if ((kSize_ % 2 == 1) && (inversions % 2 == 0))
        return true;
    else if ((kSize_ % 2 == 0) && ((inversions + kSize_ - 1) % 2 == 1))
        return true;
    else
        return false;
}

int Board::countInversions() const
{
    int inversions = 0;
    std::vector<int> tiles_values = this->getTilesValues();
    tiles_values.pop_back();

    for (int l = 0; l < kSize_*kSize_; l++)
        for (int r = l + 1; r < kSize_*kSize_; r++)
            if (tiles_values[l] > tiles_values[r])
                inversions++;

    return inversions;
}

Tile& Board::getTileByValue(int value)
{
    for (auto &tile : tiles_)
        if (tile.getValue() == value)
            return tile;

    throw std::invalid_argument("Niepoprawny numer kafelka");
}
