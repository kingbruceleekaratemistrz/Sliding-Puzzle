#include "tile.h"

Tile::Tile(int row, int col) : kRow_(row), kCol_(col) {}

Tile::Tile(int row, int col, int value) : kRow_(row), kCol_(col), value_(value) {}

const int& Tile::getValue() const { return value_; }

const int& Tile::getRow() const { return kRow_; }

const int& Tile::getCol() const { return kCol_; }

void Tile::setValue(int value) { value_ = value; }
