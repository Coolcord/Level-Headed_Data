#include "Coordinates.h"
#include "../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Object_Writer.h"

Coordinates::Coordinates(Object_Writer *objectWriter) {
    this->objectWriter = objectWriter;
    this->lastX = 0;
}

void Coordinates::Get_Coordinates(char coordinates, char object, int &x, int &y) {
    bool pageFlag = (static_cast<int>(object)&0x80) == 0x80;
    int value = static_cast<int>(coordinates);
    y = value&0x0F;
    int absoluteX = (value&0xF0)/0x10;
    if (pageFlag) {
        x = 0;
        x = (0x10-this->objectWriter->Get_Absolute_X(0)+absoluteX);
    } else {
        x = absoluteX - this->objectWriter->Get_Absolute_X(0);
    }
    lastX = x;
}
