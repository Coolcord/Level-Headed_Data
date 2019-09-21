#include "Coordinates.h"

void Coordinates::Get_Coordinates(char coordinates, char object, int &x, int &y) {
    bool pageFlag = (static_cast<int>(object)&0x80) == 0x80;
    int value = static_cast<int>(coordinates);
    x = (value&0xF0)>4;
    if (pageFlag) x += 0x10;
    y = value&0x0F;
}
