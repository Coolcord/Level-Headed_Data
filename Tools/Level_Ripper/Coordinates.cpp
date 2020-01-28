#include "Coordinates.h"
#include "../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Item_Buffer.h"

Coordinates::Coordinates(Item_Buffer *itemWriter) {
    this->itemWriter = itemWriter;
}

void Coordinates::Set_Last_Was_Group(bool lastWasGroup) {
    this->lastWasGroup = lastWasGroup;
}

void Coordinates::Get_Coordinates(char coordinates, char object, int &x, int &y, bool peek) {
    bool pageFlag = (static_cast<int>(object)&0x80) == 0x80;
    int value = static_cast<int>(coordinates);
    y = value&0x0F;
    int absoluteX = (value&0xF0)/0x10;
    int lastAbsoluteX = this->itemWriter->Get_Page_Relative_Absolute_X(0);
    if (this->lastWasGroup) {
        if (!peek) this->lastWasGroup = false;
        if (lastAbsoluteX > 0xC) {
            assert(lastAbsoluteX <= 0xF);
            lastAbsoluteX = 0xC-lastAbsoluteX;
        }
    }
    if (pageFlag) {
        x = ((0x10-lastAbsoluteX)+absoluteX);
    } else {
        x = absoluteX - lastAbsoluteX;
    }
}
