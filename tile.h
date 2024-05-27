#ifndef TILE_H
#define TILE_H

class Tile
{
private:
    int value_;
    const int kRow_;
    const int kCol_;
public:
    Tile(int row, int col);

    const int& getValue() const;
    const int& getRow() const;
    const int& getCol() const;

    void setValue(int value);
};

#endif // TILE_H
