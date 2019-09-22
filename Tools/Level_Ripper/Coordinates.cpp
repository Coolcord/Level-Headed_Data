#include "Coordinates.h"
#include "../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Item_Writer.h"

Coordinates::Coordinates(Item_Writer *itemWriter) {
    this->itemWriter = itemWriter;
    this->lastX = 0;
}

void Coordinates::Get_Coordinates(char coordinates, char object, int &x, int &y) {
    bool pageFlag = (static_cast<int>(object)&0x80) == 0x80;
    int value = static_cast<int>(coordinates);
    y = value&0x0F;
    int absoluteX = (value&0xF0)/0x10;
    if (pageFlag) {
        x = 0;
        x = ((0x10-this->itemWriter->Get_Absolute_X(0))+absoluteX);
    } else {
        x = absoluteX - this->itemWriter->Get_Absolute_X(0);
    }
    lastX = x;
}
