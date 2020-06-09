#ifndef TILE_H
#define TILE_H

#include <QImage>

class Tile {
public:
    Tile(char tileNumber, bool sprite);
    ~Tile();
    QImage *Get_Image();

private:
    bool Read_Tile_From_ROM();

    QImage *image;
    char tileNumber;
    bool sprite;
};

#endif // TILE_H
