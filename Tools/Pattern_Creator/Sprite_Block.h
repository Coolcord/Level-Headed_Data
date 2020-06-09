#ifndef SPRITE_BLOCK_H
#define SPRITE_BLOCK_H

#include <QGraphicsItem>
#include <QPainter>

class Tile;

class Sprite_Block : public QGraphicsItem {
public:
    Sprite_Block(char topLeftTile, char topRightTile, char middleLeftTile, char middleRightTile, char bottomLeftTile, char bottomRightTile);
    ~Sprite_Block();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:

private:
    Tile *topLeft;
    Tile *topRight;
    Tile *middleLeft;
    Tile *middleRight;
    Tile *bottomLeft;
    Tile *bottomRight;
};

#endif // SPRITE_BLOCK_H
