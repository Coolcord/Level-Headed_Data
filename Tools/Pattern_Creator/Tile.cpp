#include "Tile.h"

Tile::Tile(char tileNumber, bool sprite) {
    this->tileNumber = tileNumber;
    this->sprite = sprite;
    this->image = nullptr;
}

Tile::~Tile() {
    delete this->image;
}

bool Tile::Read_Tile_From_ROM() {
    if (this->image) return true; //already read
    this->image = new QImage(8, 8, QImage::Format_ARGB32);
    switch (this->tileNumber) {
    default:
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) this->image->setPixel(i, j, 0xFF00FF00); //green
        }
        break;
    case 1:
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) this->image->setPixel(i, j, 0xFFFF0000); //red
        }
        break;
    case 2:
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) this->image->setPixel(i, j, 0xFF0000FF); //blue
        }
        break;
    case 3:
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) this->image->setPixel(i, j, 0xFFFFFF00); //yellow
        }
        break;
    }
    return true;
}

QImage *Tile::Get_Image() {
    if (!this->Read_Tile_From_ROM()) return nullptr;
    return this->image;
}
