#ifndef TILE_H
#define TILE_H

#include <QImage>

class ROM_Reader;

class Tile {
public:
    Tile(ROM_Reader *romReader, char tileNumber, bool sprite);
    ~Tile();
    QImage *Get_Image();

private:
    bool Read_Tile_From_ROM();

    ROM_Reader *romReader;
    QImage *image;
    char tileNumber;
    bool sprite;
};

#endif // TILE_H
