#include "Sprite_Block.h"
#include "Tile.h"

Sprite_Block::Sprite_Block(char topLeftTile, char topRightTile, char middleLeftTile, char middleRightTile, char bottomLeftTile, char bottomRightTile) {
    this->topLeft = new Tile(topLeftTile, true);
    this->topRight = new Tile(topRightTile, true);
    this->middleLeft = new Tile(middleLeftTile, true);
    this->middleRight = new Tile(middleRightTile, true);
    this->bottomLeft = new Tile(bottomLeftTile, true);
    this->bottomRight = new Tile(bottomRightTile, true);
}

Sprite_Block::~Sprite_Block() {
    delete this->topLeft;
    delete this->topRight;
    delete this->middleLeft;
    delete this->middleRight;
    delete this->bottomLeft;
    delete this->bottomRight;
}

QRectF Sprite_Block::boundingRect() const {
    return QRectF(0, 0, 16, 24);
}

void Sprite_Block::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawImage(QRectF(0, 0, 16, 24), *this->topLeft->Get_Image());
    painter->drawImage(QRectF(8, 0, 16, 24), *this->topRight->Get_Image());
    painter->drawImage(QRectF(0, 8, 16, 24), *this->middleLeft->Get_Image());
    painter->drawImage(QRectF(8, 8, 16, 24), *this->middleRight->Get_Image());
    painter->drawImage(QRectF(0, 16, 16, 24), *this->bottomLeft->Get_Image());
    painter->drawImage(QRectF(8, 16, 16, 24), *this->bottomRight->Get_Image());
}
