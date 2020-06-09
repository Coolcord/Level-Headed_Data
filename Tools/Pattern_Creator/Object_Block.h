#ifndef OBJECT_BLOCK_H
#define OBJECT_BLOCK_H

#include <QGraphicsItem>
#include <QPainter>

class Tile;

class Object_Block : public QGraphicsItem {
public:
    Object_Block(char topLeftTile, char topRightTile, char bottomLeftTile, char bottomRightTile);
    ~Object_Block();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:

private:
    Tile *topLeft;
    Tile *topRight;
    Tile *bottomLeft;
    Tile *bottomRight;
};

#endif // OBJECT_BLOCK_H
