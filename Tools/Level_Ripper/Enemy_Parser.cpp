#include "Enemy_Parser.h"
#include "../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Enemy_Buffer.h"
#include "../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Object_Buffer.h"
#include "../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Pipe_Pointer_Buffer.h"
#include "Coordinates.h"
#include <QDebug>
#include <assert.h>

Enemy_Parser::Enemy_Parser(int numBytesLeft, SMB1_Compliance_Generator_Arguments *args) {
    this->enemies = new Enemy_Buffer(numBytesLeft);
    this->objects = new Object_Buffer(numBytesLeft, args);
    this->objects->Set_Coordinate_Safety(false);
    this->enemies->Set_Coordinate_Safety(false);
    this->pipePointerWriter = new Pipe_Pointer_Buffer(this->objects, this->enemies);
    this->coordinates = new Coordinates(this->enemies);
    this->lastWasPageChange = false;
}

Enemy_Parser::~Enemy_Parser() {
    delete this->pipePointerWriter;
    delete this->enemies;
    delete this->objects;
    delete this->coordinates;
}

bool Enemy_Parser::At_End(char coordinates) {
    return coordinates == static_cast<char>(0xFF);
}

bool Enemy_Parser::Is_Pipe_Pointer(char coordinates, char enemy) {
    int x = 0, y = 0;
    this->coordinates->Get_Coordinates(coordinates, enemy, x, y, true);
    return y == 0xE;
}

bool Enemy_Parser::Parse_Enemy(char coordinates, char enemy) {
    int value = static_cast<int>(enemy)&0x3F;
    bool hardMode = (static_cast<int>(enemy)&0x40) == 0x40;
    int x = 0, y = 0;
    this->coordinates->Get_Coordinates(coordinates, enemy, x, y, false);
    if (y == 0xF) {
        this->lastWasPageChange = true;
        return this->enemies->Page_Change(value);
    }
    --y;
    if (value >= 0x1B && value <= 0x1F) --y;
    if (value > 0x36) x -= 3; //group enemy x value is off by 3
    if (this->lastWasPageChange) {
        this->lastWasPageChange = false;
        if (x > 0x10) x -= 0x10;
    }
    bool success = false;
    switch (value) {
    default:    return false;
    case 0x00:  return this->enemies->Green_Koopa(x, y, true, hardMode);
    case 0x02:  return this->enemies->Buzzy_Beetle(x, y, hardMode);
    case 0x03:  return this->enemies->Red_Koopa(x, y, hardMode);
    case 0x04:  return this->enemies->Green_Koopa(x, y, false, hardMode);
    case 0x05:  return this->enemies->Hammer_Bro(x, y, hardMode);
    case 0x06:  return this->enemies->Goomba(x, y, hardMode);
    case 0x07:  return this->enemies->Blooper(x, y, hardMode);
    case 0x08:  return this->enemies->Bullet_Bill(x, y, hardMode);
    case 0x09:  return this->enemies->Green_Paratroopa(x, y, false, false, hardMode);
    case 0x0A:  return this->enemies->Green_Cheep_Cheep(x, y, hardMode);
    case 0x0B:  return this->enemies->Red_Cheep_Cheep(x, y, hardMode);
    case 0x0C:  return this->enemies->Podoboo(x, hardMode);
    case 0x0D:  return this->enemies->Piranha_Plant(x, y, hardMode);
    case 0x0E:  return this->enemies->Green_Paratroopa(x, y, true, true, hardMode);
    case 0x0F:  return this->enemies->Red_Paratroopa(x, y, hardMode);
    case 0x10:  return this->enemies->Green_Paratroopa(x, y, true, false, hardMode);
    case 0x11:  return this->enemies->Lakitu(x, y, hardMode);
    case 0x12:  return this->enemies->Spiny(x, y, hardMode);
    case 0x14:  return this->enemies->Swimming_Cheep_Cheep_Spawner(x, true, hardMode);
    case 0x15:  return this->enemies->Bowser_Fire_Spawner(x, hardMode);
    case 0x17:  return this->enemies->Bullet_Bill_Spawner(x, hardMode);
    case 0x1B:  return this->enemies->Fire_Bar(x, y, true, false, hardMode);
    case 0x1C:  return this->enemies->Fire_Bar(x, y, true, true, hardMode);
    case 0x1D:  return this->enemies->Fire_Bar(x, y, false, false, hardMode);
    case 0x1E:  return this->enemies->Fire_Bar(x, y, false, true, hardMode);
    case 0x1F:  return this->enemies->Large_Fire_Bar(x, y, hardMode);
    case 0x24:  return this->enemies->Balance_Lift(x, y, hardMode);
    case 0x25:  return this->enemies->Lift(x, y, true, hardMode);
    case 0x26:  return this->enemies->Lift_Spawner(x, y, true, false, hardMode);
    case 0x27:  return this->enemies->Lift_Spawner(x, y, false, false, hardMode);
    case 0x28:  return this->enemies->Lift(x, y, false, hardMode);
    case 0x29:  return this->enemies->Falling_Lift(x, y, hardMode);
    case 0x2A:  return this->enemies->Surfing_Lift(x, y, hardMode);
    case 0x2B:  return this->enemies->Lift_Spawner(x, y, true, true, hardMode);
    case 0x2C:  return this->enemies->Lift_Spawner(x, y, false, true, hardMode);
    case 0x2D:  return this->enemies->Bowser(x, hardMode);
    case 0x34:  return this->enemies->Warp_Zone(x);
    case 0x35:  return this->enemies->Toad(x, hardMode);
    case 0x37:  success = this->enemies->Goomba_Group(x, 0xA, 2, hardMode); break;
    case 0x38:  success = this->enemies->Goomba_Group(x, 0xA, 3, hardMode); break;
    case 0x39:  success = this->enemies->Goomba_Group(x, 0x6, 2, hardMode); break;
    case 0x3A:  success = this->enemies->Goomba_Group(x, 0x6, 3, hardMode); break;
    case 0x3B:  success = this->enemies->Koopa_Group(x, 0xA, 2, hardMode); break;
    case 0x3C:  success = this->enemies->Koopa_Group(x, 0xA, 3, hardMode); break;
    case 0x3D:  success = this->enemies->Koopa_Group(x, 0x6, 2, hardMode); break;
    case 0x3E:  success = this->enemies->Koopa_Group(x, 0x6, 3, hardMode); break;
    }
    this->coordinates->Set_Last_Was_Group(true);
    return success;
}

bool Enemy_Parser::Parse_Pipe_Pointer(char coordinates, char levelSlot, char page) {
    int x = 0, y = 0;
    this->coordinates->Get_Coordinates(coordinates, levelSlot, x, y, false);
    qDebug() << "Warning: Pipe pointer detected!";
    qDebug().noquote() << "x:" << x << "y:" << y << "levelSlot:" << levelSlot << "page:" << page;
    return this->pipePointerWriter->Pipe_Pointer(x, Level::WORLD_1_LEVEL_1, 1, page); //this is just a place holder
}
