#include "Object_Parser.h"
#include "../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Object_Writer.h"
#include "Coordinates.h"
#include <assert.h>

Object_Parser::Object_Parser(QTextStream *stream, int numBytesLeft, SMB1_Compliance_Generator_Arguments *args) {
    this->args = args;
    this->objectWriter = new Object_Writer(stream, numBytesLeft, args);
    this->objectWriter->Set_Coordinate_Safety(false);
    this->coordinates = new Coordinates(this->objectWriter);
}

Object_Parser::~Object_Parser() {
    delete this->objectWriter;
    delete this->coordinates;
}

bool Object_Parser::At_End(char coordinates) {
    return coordinates == static_cast<char>(0xFD);
}

bool Object_Parser::Parse_Object(char coordinates, char object) {
    int x = 0, y = 0;
    this->coordinates->Get_Coordinates(coordinates, object, x, y);
    if (y < 0xC) return this->Parse_B_Object(x, y, object);
    else if (y == 0xC) return this->Parse_C_Object(x, object);
    else if (y == 0xD) return this->Parse_D_Object(x, object);
    else if (y == 0xE) return this->Parse_E_Object(x, object);
    else if (y == 0xF) return this->Parse_F_Object(x, object);
    return false;
}

bool Object_Parser::Parse_B_Object(int x, int y, char object) {
    int value = static_cast<int>(object)&0x7F;
    switch (value&0x70) {
    default:    return false;
    case 0x00:
        switch (value) {
        default:    return false;
        case 0x00:  return this->objectWriter->Question_Block_With_Mushroom_Only(x, y);
        case 0x01:  return this->objectWriter->Question_Block_With_Coin(x, y);
        case 0x02:  return this->objectWriter->Hidden_Block_With_Coin(x, y);
        case 0x03:  return this->objectWriter->Hidden_Block_With_1up_Only(x, y);
        case 0x04:  return this->objectWriter->Brick_With_Mushroom_Only(x, y);
        case 0x05:  return this->objectWriter->Brick_With_Vine_Without_Pointer(x, y);
        case 0x06:  return this->objectWriter->Brick_With_Star_Only(x, y);
        case 0x07:  return this->objectWriter->Brick_With_10_Coins(x, y);
        case 0x08:  return this->objectWriter->Brick_With_1up_Only(x, y);
        case 0x09:  return this->objectWriter->Underwater_Sideways_Pipe_Without_Pointer(x, y);
        case 0x0A:  return this->objectWriter->Used_Block(x, y);
        case 0x0B:  return this->objectWriter->Trampoline(x, y);
        }
    case 0x10:
        if (this->args->levelCompliment == Level_Compliment::BULLET_BILL_TURRETS) return this->objectWriter->Bullet_Bill_Turret(x, y, (value&0x0F)+1);
        else return this->objectWriter->Island(x, y, (value&0x0F)+1);
    case 0x20:
        return this->objectWriter->Horizontal_Bricks(x, y, (value&0x0F)+1);
    case 0x30:
        return this->objectWriter->Horizontal_Blocks(x, y, (value&0x0F)+1);
    case 0x40:
        return this->objectWriter->Horizontal_Coins(x, y, (value&0x0F)+1);
    case 0x50:
        if (this->args->levelType == Level_Type::UNDERWATER) return this->objectWriter->Coral(x, y, (value&0x0F)+1);
        else return this->objectWriter->Vertical_Bricks(x, y, (value&0x0F)+1);
    case 0x60:
        return this->objectWriter->Vertical_Blocks(x, y, (value&0x0F)+1);
    case 0x70:
        if (value < 0x78) return this->objectWriter->Pipe(x, y, (value&0x0F)+1);
        else return this->objectWriter->Enterable_Pipe_Without_Pointer(x, y, (value&0x0F)-7);
    }
}

bool Object_Parser::Parse_C_Object(int x, char object) {
    int value = static_cast<int>(object)&0x7F;
    switch (value&0x70) {
    default:    return false;
    case 0x00:  return this->objectWriter->Hole(x, (value&0x0F)+1, false);
    case 0x10:  return this->objectWriter->Balance_Lift_Horizontal_Rope(x, (value&0x0F)+1);
    case 0x20:  return this->objectWriter->Bridge(x, 0x7, (value&0x0F)+1);
    case 0x30:  return this->objectWriter->Bridge(x, 0x8, (value&0x0F)+1);
    case 0x40:  return this->objectWriter->Bridge(x, 0xA, (value&0x0F)+1);
    case 0x50:  return this->objectWriter->Hole(x, (value&0x0F)+1, true);
    case 0x60:  return this->objectWriter->Horizontal_Question_Blocks_With_Coins(x, 0x3, (value&0x0F)+1);
    case 0x70:  return this->objectWriter->Horizontal_Question_Blocks_With_Coins(x, 0x7, (value&0x0F)+1);
    }
}

bool Object_Parser::Parse_D_Object(int x, char object) {
    int value = static_cast<int>(object)&0x7F;
    if (value < 0x40) return this->objectWriter->Page_Change(value);
    switch (value) {
    default:    return false;
    case 0x40:  return this->objectWriter->Reverse_L_Pipe_Without_Pointer(x);
    case 0x41:  return this->objectWriter->Flagpole(x);
    case 0x42:  return this->objectWriter->Axe(x);
    case 0x43:  return this->objectWriter->Axe_Rope(x);
    case 0x44:  return this->objectWriter->Bowser_Bridge(x);
    case 0x45:  return this->objectWriter->Scroll_Stop(x, true);
    case 0x46:  return this->objectWriter->Scroll_Stop(x, false);
    case 0x47:  return this->objectWriter->Scroll_Stop(x, false);
    case 0x48:  return this->objectWriter->Flying_Cheep_Cheep_Spawner(x);
    case 0x49:  return this->objectWriter->Bullet_Bill_Spawner(x);
    case 0x4A:  return this->objectWriter->Cancel_Spawner(x);
    case 0x4B:  return this->objectWriter->Loop_Command(x);
    }
}

bool Object_Parser::Parse_E_Object(int x, char object) {
    int value = static_cast<int>(object)&0x7F;
    if (value < 0x40) {
        Scenery::Scenery scenery = Scenery::NO_SCENERY;
        switch (value&0x30) {
        default:    assert(false); return false;
        case 0x00:  scenery = Scenery::NO_SCENERY; break;
        case 0x10:  scenery = Scenery::ONLY_CLOUDS; break;
        case 0x20:  scenery = Scenery::MOUNTAINS; break;
        case 0x30:  scenery = Scenery::FENCES; break;
        }

        Brick::Brick brick = Brick::NO_BRICKS;
        switch (value&0x0F) {
        default:    assert(false); return false;
        case 0x00:  brick = Brick::NO_BRICKS; break;
        case 0x01:  brick = Brick::SURFACE; break;
        case 0x02:  brick = Brick::SURFACE_AND_CEILING; break;
        case 0x03:  brick = Brick::SURFACE_AND_CEILING_3; break;
        case 0x04:  brick = Brick::SURFACE_AND_CEILING_4; break;
        case 0x05:  brick = Brick::SURFACE_AND_CEILING_8; break;
        case 0x06:  brick = Brick::SURFACE_4_AND_CEILING; break;
        case 0x07:  brick = Brick::SURFACE_4_AND_CEILING_3; break;
        case 0x08:  brick = Brick::SURFACE_4_AND_CEILING_4; break;
        case 0x09:  brick = Brick::SURFACE_5_AND_CEILING; break;
        case 0x0A:  brick = Brick::CEILING; break;
        case 0x0B:  brick = Brick::SURFACE_5_AND_CEILING_4; break;
        case 0x0C:  brick = Brick::SURFACE_8_AND_CEILING; break;
        case 0x0D:  brick = Brick::SURFACE_AND_CEILING_AND_MIDDLE_5; break;
        case 0x0E:  brick = Brick::SURFACE_AND_CEILING_AND_MIDDLE_4; break;
        case 0x0F:  brick = Brick::ALL; break;
        }
        return this->objectWriter->Change_Brick_And_Scenery(x, brick, scenery);
    }

    switch (value) {
    default:    return false;
    case 0x40:  return this->objectWriter->Change_Background(x, Background::BLANK_BACKGROUND);
    case 0x41:  return this->objectWriter->Change_Background(x, Background::IN_WATER);
    case 0x42:  return this->objectWriter->Change_Background(x, Background::CASTLE_WALL);
    case 0x43:  return this->objectWriter->Change_Background(x, Background::OVER_WATER);
    case 0x44:  return this->objectWriter->Change_Background(x, Background::NIGHT);
    case 0x45:  return this->objectWriter->Change_Background(x, Background::SNOW);
    case 0x46:  return this->objectWriter->Change_Background(x, Background::NIGHT_AND_SNOW);
    case 0x47:  return this->objectWriter->Change_Background(x, Background::NIGHT_AND_FREEZE);
    }
}

bool Object_Parser::Parse_F_Object(int x, char object) {
    int value = static_cast<int>(object)&0x7F;
    switch (value) {
    default:    break;
    case 0x26:  return this->objectWriter->Castle(x);
    case 0x38:  return this->objectWriter->End_Steps(x);
    case 0x42:  return this->objectWriter->Tall_Reverse_L_Pipe_Without_Pointer(x, 2);
    case 0x43:  return this->objectWriter->Tall_Reverse_L_Pipe_Without_Pointer(x, 3);
    case 0x44:  return this->objectWriter->Tall_Reverse_L_Pipe_Without_Pointer(x, 4);
    case 0x45:  return this->objectWriter->Tall_Reverse_L_Pipe_Without_Pointer(x, 5);
    case 0x46:  return this->objectWriter->Tall_Reverse_L_Pipe_Without_Pointer(x, 6);
    case 0x47:  return this->objectWriter->Tall_Reverse_L_Pipe_Without_Pointer(x, 7);
    case 0x48:  return this->objectWriter->Tall_Reverse_L_Pipe_Without_Pointer(x, 8);
    case 0x49:  return this->objectWriter->Tall_Reverse_L_Pipe_Without_Pointer(x, 9);
    case 0x4A:  return this->objectWriter->Tall_Reverse_L_Pipe_Without_Pointer(x, 0xA);
    case 0x4F:  return this->objectWriter->Pipe_Wall(x);
    }

    switch (value&0x70) {
    default:    return false;
    case 0x00:  return this->objectWriter->Lift_Rope(x);
    case 0x10:  return this->objectWriter->Balance_Lift_Vertical_Rope(x, (value&0x0F)+1);
    case 0x20:  return this->objectWriter->Big_Castle(x);
    case 0x30:  return this->objectWriter->Steps(x, (value&0x0F)+1);
    case 0x60:  return this->objectWriter->Nothing();
    }
}
