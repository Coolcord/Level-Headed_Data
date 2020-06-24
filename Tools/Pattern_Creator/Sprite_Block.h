#ifndef SPRITE_BLOCK_H
#define SPRITE_BLOCK_H

#include <QGraphicsItem>
#include <QPainter>

class ROM_Reader;
class Tile;

class Sprite_Block : public QGraphicsItem {
public:
    Sprite_Block(ROM_Reader *romReader, char topLeftTile, char topRightTile, char middleLeftTile, char middleRightTile, char bottomLeftTile, char bottomRightTile);
    ~Sprite_Block();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:

private:
    ROM_Reader *romReader;
    Tile *topLeft;
    Tile *topRight;
    Tile *middleLeft;
    Tile *middleRight;
    Tile *bottomLeft;
    Tile *bottomRight;
};

#endif // SPRITE_BLOCK_H
