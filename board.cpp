#include "board.h"

#include <random>
#include <cstdlib>
#include <stdexcept>
#include <QSettings>

Board::Board()
{
    QSettings settings("config.ini", QSettings::IniFormat);
    size_ = settings.value("boardsize").toInt();    
}

const int& Board::getSize() const { return size_; }

void Board::setSize(int size) { size_ = size; };

std::vector<int> Board::getTilesValues() const
{
    std::vector<int> tiles_values;
    for (auto &t : tiles_)
        tiles_values.push_back(t.getValue());
    return tiles_values;
}

void Board::initializeNewGame()
{
    tiles_.clear();

    empty_tile_value_= size_*size_;
    for (int r = 0; r < size_; r++)
        for (int c = 0; c < size_; c++)
            tiles_.push_back(Tile(r, c));

    do {
        shuffle();
    } while (!isSolvable() || isSolved());
}

void Board::initializeNewGame(std::vector<int> tiles_values)
{
    tiles_.clear();

    empty_tile_value_ = size_*size_;
    for (int r = 0; r < size_; r++)
        for (int c = 0; c < size_; c++)
            tiles_.push_back(Tile(r, c, tiles_values.at(r*size_+c)));

}

void Board::playMove(int tile_num)
{
    Tile &tile_to_move = getTileByValue(tile_num);
    Tile &empty_tile = getTileByValue(empty_tile_value_);

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
    std::vector<bool> value_used(size_*size_, false);

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1, size_*size_ - 1);

    for (int i = 0; i < size_*size_ - 1; i++)
    {
        int value;
        do {
            value = dist(rng);
        } while (value_used[value] == true);

        value_used[value] = true;
        tiles_[i].setValue(value);
    }
    tiles_[size_*size_ - 1].setValue(empty_tile_value_);
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

    if ((size_ % 2 == 1) && (inversions % 2 == 0))
        return true;
    else if ((size_ % 2 == 0) && ((inversions + size_ - 1) % 2 == 1))
        return true;
    else
        return false;
}

int Board::countInversions() const
{
    int inversions = 0;
    std::vector<int> tiles_values = this->getTilesValues();
    tiles_values.pop_back();

    for (int l = 0; l < size_*size_; l++)
        for (int r = l + 1; r < size_*size_; r++)
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
