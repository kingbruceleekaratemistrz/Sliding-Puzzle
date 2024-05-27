#include "tile.h"

Tile::Tile(int row, int col) : kRow_(row), kCol_(col) {}

const int& Tile::getValue() const { return value_; }

const int& Tile::getRow() const { return kRow_; }

const int& Tile::getCol() const { return kCol_; }

void Tile::setValue(int value) { value_ = value; }
