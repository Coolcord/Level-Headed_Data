#include "Enemy_Parser.h"
#include "../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Enemy_Writer.h"
#include "../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Object_Writer.h"
#include "../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Pipe_Pointer_Writer.h"
#include "Coordinates.h"
#include <assert.h>

Enemy_Parser::Enemy_Parser(int numBytesLeft, SMB1_Compliance_Generator_Arguments *args) {
    this->enemyWriter = new Enemy_Writer(numBytesLeft);
    this->objectWriter = new Object_Writer(numBytesLeft, args);
    this->objectWriter->Set_Coordinate_Safety(false);
    this->enemyWriter->Set_Coordinate_Safety(false);
    this->pipePointerWriter = new Pipe_Pointer_Writer(this->objectWriter, this->enemyWriter);
    this->coordinates = new Coordinates(this->enemyWriter);
    this->lastWasPageChange = false;
}

Enemy_Parser::~Enemy_Parser() {
    delete this->pipePointerWriter;
    delete this->enemyWriter;
    delete this->objectWriter;
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
        return this->enemyWriter->Page_Change(value);
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
    case 0x00:  return this->enemyWriter->Green_Koopa(x, y, true, hardMode);
    case 0x02:  return this->enemyWriter->Buzzy_Beetle(x, y, hardMode);
    case 0x03:  return this->enemyWriter->Red_Koopa(x, y, hardMode);
    case 0x04:  return this->enemyWriter->Green_Koopa(x, y, false, hardMode);
    case 0x05:  return this->enemyWriter->Hammer_Bro(x, y, hardMode);
    case 0x06:  return this->enemyWriter->Goomba(x, y, hardMode);
    case 0x07:  return this->enemyWriter->Blooper(x, y, hardMode);
    case 0x08:  return this->enemyWriter->Bullet_Bill(x, y, hardMode);
    case 0x09:  return this->enemyWriter->Green_Paratroopa(x, y, false, false, hardMode);
    case 0x0A:  return this->enemyWriter->Green_Cheep_Cheep(x, y, hardMode);
    case 0x0B:  return this->enemyWriter->Red_Cheep_Cheep(x, y, hardMode);
    case 0x0C:  return this->enemyWriter->Podoboo(x, hardMode);
    case 0x0D:  return this->enemyWriter->Piranha_Plant(x, y, hardMode);
    case 0x0E:  return this->enemyWriter->Green_Paratroopa(x, y, true, true, hardMode);
    case 0x0F:  return this->enemyWriter->Red_Paratroopa(x, y, hardMode);
    case 0x10:  return this->enemyWriter->Green_Paratroopa(x, y, true, false, hardMode);
    case 0x11:  return this->enemyWriter->Lakitu(x, y, hardMode);
    case 0x12:  return this->enemyWriter->Spiny(x, y, hardMode);
    case 0x14:  return this->enemyWriter->Swimming_Cheep_Cheep_Spawner(x, true, hardMode);
    case 0x15:  return this->enemyWriter->Bowser_Fire_Spawner(x, hardMode);
    case 0x17:  return this->enemyWriter->Bullet_Bill_Spawner(x, hardMode);
    case 0x1B:  return this->enemyWriter->Fire_Bar(x, y, true, false, hardMode);
    case 0x1C:  return this->enemyWriter->Fire_Bar(x, y, true, true, hardMode);
    case 0x1D:  return this->enemyWriter->Fire_Bar(x, y, false, false, hardMode);
    case 0x1E:  return this->enemyWriter->Fire_Bar(x, y, false, true, hardMode);
    case 0x1F:  return this->enemyWriter->Large_Fire_Bar(x, y, hardMode);
    case 0x24:  return this->enemyWriter->Balance_Lift(x, y, hardMode);
    case 0x25:  return this->enemyWriter->Lift(x, y, true, hardMode);
    case 0x26:  return this->enemyWriter->Lift_Spawner(x, y, true, false, hardMode);
    case 0x27:  return this->enemyWriter->Lift_Spawner(x, y, false, false, hardMode);
    case 0x28:  return this->enemyWriter->Lift(x, y, false, hardMode);
    case 0x29:  return this->enemyWriter->Falling_Lift(x, y, hardMode);
    case 0x2A:  return this->enemyWriter->Surfing_Lift(x, y, hardMode);
    case 0x2B:  return this->enemyWriter->Lift_Spawner(x, y, true, true, hardMode);
    case 0x2C:  return this->enemyWriter->Lift_Spawner(x, y, false, true, hardMode);
    case 0x2D:  return this->enemyWriter->Bowser(x, hardMode);
    case 0x34:  return this->enemyWriter->Warp_Zone(x);
    case 0x35:  return this->enemyWriter->Toad(x, hardMode);
    case 0x37:  success = this->enemyWriter->Goomba_Group(x, 0xA, 2, hardMode); break;
    case 0x38:  success = this->enemyWriter->Goomba_Group(x, 0xA, 3, hardMode); break;
    case 0x39:  success = this->enemyWriter->Goomba_Group(x, 0x6, 2, hardMode); break;
    case 0x3A:  success = this->enemyWriter->Goomba_Group(x, 0x6, 3, hardMode); break;
    case 0x3B:  success = this->enemyWriter->Koopa_Group(x, 0xA, 2, hardMode); break;
    case 0x3C:  success = this->enemyWriter->Koopa_Group(x, 0xA, 3, hardMode); break;
    case 0x3D:  success = this->enemyWriter->Koopa_Group(x, 0x6, 2, hardMode); break;
    case 0x3E:  success = this->enemyWriter->Koopa_Group(x, 0x6, 3, hardMode); break;
    }
    this->coordinates->Set_Last_Was_Group(true);
    return success;
}

bool Enemy_Parser::Parse_Pipe_Pointer(char coordinates, char levelSlot, char page) {
    int x = 0, y = 0;
    this->coordinates->Get_Coordinates(coordinates, levelSlot, x, y, false);
    return this->pipePointerWriter->Pipe_Pointer(x, static_cast<int>(QString::number(levelSlot).toUInt()), static_cast<int>(QString::number(page).toUInt()));
    //*this->stream << "Pipe_Pointer " << x << " [[[" << QString::number(static_cast<int>(levelSlot)) << "]]] " << QString::number(static_cast<int>(page)) << endl;
    //this->enemyWriter->Set_First_Enemy(false);
    //return true;
}
