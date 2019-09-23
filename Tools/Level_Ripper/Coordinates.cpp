#include "Coordinates.h"
#include "../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Item_Writer.h"

Coordinates::Coordinates(Item_Writer *itemWriter) {
    this->itemWriter = itemWriter;
}

void Coordinates::Set_Last_Was_Group(bool lastWasGroup) {
    this->lastWasGroup = lastWasGroup;
}

void Coordinates::Get_Coordinates(char coordinates, char object, int &x, int &y) {
    bool pageFlag = (static_cast<int>(object)&0x80) == 0x80;
    int value = static_cast<int>(coordinates);
    y = value&0x0F;
    int absoluteX = (value&0xF0)/0x10;
    if (pageFlag) {
        x = ((0x10-this->itemWriter->Get_Absolute_X(0))+absoluteX);
    } else {
        if (this->lastWasGroup) {
            int lastAbsoluteX = this->itemWriter->Get_Absolute_X(0);
            if (lastAbsoluteX > 0xC) {
                assert(lastAbsoluteX <= 0xF);
                lastAbsoluteX = 0xC-lastAbsoluteX;
            }
            x = absoluteX - lastAbsoluteX;
        } else {
            x = absoluteX - this->itemWriter->Get_Absolute_X(0);
        }
    }
}
