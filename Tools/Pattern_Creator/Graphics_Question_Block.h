#ifndef GRAPHICS_QUESTION_BLOCK_H
#define GRAPHICS_QUESTION_BLOCK_H

#include <QGraphicsItem>
#include <QPainter>

class Object_Block;
class ROM_Reader;

class Graphics_Question_Block : public QGraphicsItem {
public:
    Graphics_Question_Block(ROM_Reader *romReader);
    ~Graphics_Question_Block();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:

private:
    Object_Block *objectBlock;
    ROM_Reader *romReader;
};

#endif // GRAPHICS_QUESTION_BLOCK_H
