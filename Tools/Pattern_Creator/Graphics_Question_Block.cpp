#include "Graphics_Question_Block.h"
#include "Object_Block.h"

Graphics_Question_Block::Graphics_Question_Block(ROM_Reader *romReader) {
    assert(romReader);
    this->romReader = romReader;
    this->objectBlock = new Object_Block(romReader, 0, 1, 2, 3);
    setFlag(ItemIsMovable);
}

Graphics_Question_Block::~Graphics_Question_Block() {
    delete this->objectBlock;
}

QRectF Graphics_Question_Block::boundingRect() const {
    return QRectF(0, 0, 16, 16);
}

void Graphics_Question_Block::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    this->objectBlock->paint(painter, option, widget);
}
