#include "Object_Block.h"
#include "Tile.h"

Object_Block::Object_Block(char topLeftTile, char topRightTile, char bottomLeftTile, char bottomRightTile) {
    this->topLeft = new Tile(topLeftTile, false);
    this->topRight = new Tile(topRightTile, false);
    this->bottomLeft = new Tile(bottomLeftTile, false);
    this->bottomRight = new Tile(bottomRightTile, false);
}

Object_Block::~Object_Block() {
    delete this->topLeft;
    delete this->topRight;
    delete this->bottomLeft;
    delete this->bottomRight;
}

QRectF Object_Block::boundingRect() const {
    return QRectF(0, 0, 16, 16);
}

void Object_Block::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawImage(QRectF(0, 0, 8, 8), *this->topLeft->Get_Image());
    painter->drawImage(QRectF(8, 0, 8, 8), *this->topRight->Get_Image());
    painter->drawImage(QRectF(0, 8, 8, 8), *this->bottomLeft->Get_Image());
    painter->drawImage(QRectF(8, 8, 8, 8), *this->bottomRight->Get_Image());
}
