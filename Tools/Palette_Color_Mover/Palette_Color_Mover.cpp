#include "Palette_Color_Mover.h"
#include <assert.h>
#include <QStack>
#include <QMap>

Palette_Color_Mover::Palette_Color_Mover(QFile *f, Level_Offset *lo) : Byte_Writer(f, lo) {
    this->colorMap = new QMap<Sprites::Sprites, int>();
    this->tileMap = new QMap<Sprites::Sprites, QByteArray>();
    this->swappedTiles = new QSet<char>();
}

Palette_Color_Mover::~Palette_Color_Mover() {
    delete this->colorMap;
    delete this->tileMap;
    delete this->swappedTiles;
}

bool Palette_Color_Mover::Get_Hex_From_Char_Arg(char *inArg, char &outArg) {
    QByteArray bytes = QByteArray::fromHex(QString(inArg).toLatin1());
    if (bytes.size() != 1) return false;
    outArg = bytes.at(0);
    return true;
}

bool Palette_Color_Mover::Swap_Colors_In_RGB_Groups(int color1, int color2) {
    if (!this->Swap_Colors_In_Red_Group(color1, color2)) return false;
    if (!this->Swap_Colors_In_Green_Group(color1, color2)) return false;
    return this->Swap_Colors_In_Blue_Group(color1, color2);
}

bool Palette_Color_Mover::Swap_Colors_In_Red_Group(int color1, int color2) {
    if (!this->Are_Colors_Valid(color1, color2)) return false;
    if (!this->Swap_Color_In_Palette(color1, color2, 0x0CD0)) return false;
    if (!this->Swap_Color_In_Palette(color1, color2, 0x0CF4)) return false;
    if (!this->Swap_Color_In_Palette(color1, color2, 0x0D18)) return false;
    if (!this->Swap_Color_In_Palette(color1, color2, 0x0D3C)) return false;
    return this->Swap_Colors_In_Sprite_Group(color1, color2, 0x02);
}

bool Palette_Color_Mover::Swap_Colors_In_Green_Group(int color1, int color2) {
    if (!this->Are_Colors_Valid(color1, color2)) return false;
    if (!this->Swap_Color_In_Palette(color1, color2, 0x0CF0)) return false;
    if (!this->Swap_Color_In_Palette(color1, color2, 0x0D14)) return false;
    if (!this->Swap_Color_In_Palette(color1, color2, 0x0CCC)) return false;
    if (!this->Swap_Color_In_Palette(color1, color2, 0x0D38)) return false;
    return this->Swap_Colors_In_Sprite_Group(color1, color2, 0x01);
}

bool Palette_Color_Mover::Swap_Colors_In_Blue_Group(int color1, int color2) {
    if (!this->Are_Colors_Valid(color1, color2)) return false;
    if (!this->Swap_Color_In_Palette(color1, color2, 0x0CD4)) return false;
    if (!this->Swap_Color_In_Palette(color1, color2, 0x0CF8)) return false;
    if (!this->Swap_Color_In_Palette(color1, color2, 0x0D1C)) return false;
    if (!this->Swap_Color_In_Palette(color1, color2, 0x0D40)) return false;
    return this->Swap_Colors_In_Sprite_Group(color1, color2, 0x03);
}

bool Palette_Color_Mover::Swap_Colors_In_Mario_Group(int color1, int color2) {
    if (!this->Are_Colors_Valid(color1, color2)) return false;
    if (!this->Swap_Color_In_Palette(color1, color2, 0x05E8)) return false; //Swap the Palette Colors for Mario
    if (!this->Swap_Color_In_Palette(color1, color2, 0x05EC)) return false; //Swap the Palette Colors for Luigi
    if (!this->Swap_Color_In_Palette(color1, color2, 0x05F0)) return false; //Swap the Palette Colors for Fire Mario

    //Swap the Palette in the Graphics Data
    QByteArray marioTiles;
    for (int i = 0; i < 0x50; ++i) {
        if (!this->Swap_Color_In_Sprite_Tile(static_cast<char>(i), color1, color2)) return false;
    }
    for (int i = 0x58; i < 0x5B; ++i) {
        if (!this->Swap_Color_In_Sprite_Tile(static_cast<char>(i), color1, color2)) return false;
    }
    for (int i = 0x5C; i < 0x60; ++i) {
        if (!this->Swap_Color_In_Sprite_Tile(static_cast<char>(i), color1, color2)) return false;
    }
    for (int i = 0x90; i < 0x94; ++i) {
        if (!this->Swap_Color_In_Sprite_Tile(static_cast<char>(i), color1, color2)) return false;
    }
    for (int i = 0x9E; i < 0xA0; ++i) {
        if (!this->Swap_Color_In_Sprite_Tile(static_cast<char>(i), color1, color2)) return false;
    }
    return true;
}

bool Palette_Color_Mover::Swap_Colors_In_Bowser_Group(int color1, int color2) {
    //Swap the Palette Colors
    if (!this->Are_Colors_Valid(color1, color2)) return false;
    if (!this->Swap_Color_In_Palette(color1, color2, 0x0D60)) return false;

    //Swap the Palette in the Graphics Data
    QByteArray bowserTiles;
    if (!this->Read_Bytes_From_Offset(0x6820, 24, bowserTiles)) return false;
    for (int i = 0; i < bowserTiles.size(); ++i) {
        if (!this->Swap_Color_In_Sprite_Tile(bowserTiles.at(i), color1, color2)) return false;
    }
    return true;
}

bool Palette_Color_Mover::Swap_Colors_In_Background_Tile_Without_Touching_Palette(int color1, int color2, char tileID) {
    if (!this->Are_Colors_Valid(color1, color2)) return false;
    return this->Swap_Color_In_Background_Tile(tileID, color1, color2);
}

bool Palette_Color_Mover::Swap_Colors_In_Sprite_Tile_Without_Touching_Palette(int color1, int color2, char tileID) {
    if (!this->Are_Colors_Valid(color1, color2)) return false;
    return this->Swap_Color_In_Sprite_Tile(tileID, color1, color2);
}

bool Palette_Color_Mover::Are_Colors_Valid(int color1, int color2) {
    if (color1 < 1 || color1 > 3) return false;
    if (color2 < 1 || color2 > 3) return false;
    return true;
}

bool Palette_Color_Mover::Read_Maps() {
    //Read the Color Map
    this->colorMap->clear();
    if (!this->Read_Color_Map_Value(Sprites::KOOPA_TROOPA_GREEN)) return false;
    if (!this->Read_Color_Map_Value(Sprites::KOOPA_TROOPA_GREEN_STOPPED)) return false;
    if (!this->Read_Color_Map_Value(Sprites::KOOPA_TROOPA_RED)) return false;
    if (!this->Read_Color_Map_Value(Sprites::KOOPA_TROOPA_LOOP)) return false;
    if (!this->Read_Color_Map_Value(Sprites::BUZZY_BEETLE)) return false;
    if (!this->Read_Color_Map_Value(Sprites::PARATROOPA_LEFT_RIGHT)) return false;
    if (!this->Read_Color_Map_Value(Sprites::PARATROOPA_JUMP)) return false;
    if (!this->Read_Color_Map_Value(Sprites::PARATROOPA_STOPPED)) return false;
    if (!this->Read_Color_Map_Value(Sprites::PARATROOPA_UP_DOWN)) return false;
    if (!this->Read_Color_Map_Value(Sprites::GOOMBA)) return false;
    if (!this->Read_Color_Map_Value(Sprites::SPINY)) return false;
    if (!this->Read_Color_Map_Value(Sprites::PIRANHA_PLANT)) return false;
    if (!this->Read_Color_Map_Value(Sprites::CHEEP_CHEEP_MULTI_GREEN)) return false;
    if (!this->Read_Color_Map_Value(Sprites::CHEEP_CHEEP_MULTI_RED)) return false;
    if (!this->Read_Color_Map_Value(Sprites::FLYING_CHEEP_CHEEP)) return false;
    if (!this->Read_Color_Map_Value(Sprites::BLOOPER)) return false;
    if (!this->Read_Color_Map_Value(Sprites::PODOBOO)) return false;
    if (!this->Read_Color_Map_Value(Sprites::BULLET_BILL_MULTI)) return false;
    if (!this->Read_Color_Map_Value(Sprites::HAMMER_BROS)) return false;
    if (!this->Read_Color_Map_Value(Sprites::BOWSER_FLAME_1)) return false;
    if (!this->Read_Color_Map_Value(Sprites::BOWSER_FLAME_2)) return false;
    if (!this->Read_Color_Map_Value(Sprites::HAMMER_1)) return false;
    if (!this->Read_Color_Map_Value(Sprites::HAMMER_2)) return false;
    if (!this->Read_Color_Map_Value(Sprites::HAMMER_3)) return false;
    if (!this->Read_Color_Map_Value(Sprites::HAMMER_4)) return false;
    if (!this->Read_Color_Map_Value(Sprites::MUSHROOM)) return false;
    if (!this->Read_Color_Map_Value(Sprites::FIRE_FLOWER)) return false;
    if (!this->Read_Color_Map_Value(Sprites::STARMAN)) return false;
    if (!this->Read_Color_Map_Value(Sprites::ONE_UP_MUSHROOM)) return false;
    if (!this->Read_Color_Map_Value(Sprites::LIFT)) return false;
    if (!this->Read_Color_Map_Value(Sprites::SMALL_LIFT)) return false;
    if (!this->Read_Color_Map_Value(Sprites::FIREWORKS_UL)) return false;
    if (!this->Read_Color_Map_Value(Sprites::FIREWORKS_LL)) return false;
    if (!this->Read_Color_Map_Value(Sprites::FIREBAR)) return false;
    if (!this->Read_Color_Map_Value(Sprites::SPRINGBOARD_1)) return false;
    if (!this->Read_Color_Map_Value(Sprites::SPRINGBOARD_2)) return false;
    if (!this->Read_Color_Map_Value(Sprites::SPRINGBOARD_3)) return false;
    if (!this->Read_Color_Map_Value(Sprites::BRICK_BLOCK)) return false;
    if (!this->Read_Color_Map_Value(Sprites::BRICK_BLOCK_PIECE)) return false;
    if (!this->Read_Color_Map_Value(Sprites::FIREWORKS_UR)) return false;
    if (!this->Read_Color_Map_Value(Sprites::FIREWORKDS_LR)) return false;
    if (!this->Read_Color_Map_Value(Sprites::VINE)) return false;
    if (!this->Read_Color_Map_Value(Sprites::CASTLE_FLAG)) return false;
    if (!this->Read_Color_Map_Value(Sprites::TOAD)) return false;
    if (!this->Read_Color_Map_Value(Sprites::PEACH)) return false;
    if (!this->Read_Color_Map_Value(Sprites::BUBBLE)) return false;
    if (!this->Read_Color_Map_Value(Sprites::LAKITU)) return false;
    if (!this->Read_Color_Map_Value(Sprites::FLAGPOLE)) return false;
    if (!this->Read_Color_Map_Value(Sprites::EMPTY_BLOCK)) return false;
    if (!this->Read_Color_Map_Value(Sprites::POINTS)) return false;
    if (!this->Read_Color_Map_Value(Sprites::ONE_UP_TEXT)) return false;
    if (!this->Read_Color_Map_Value(Sprites::COIN_TEXT)) return false;
    if (!this->Read_Color_Map_Value(Sprites::BRICK_PIECE)) return false;
    if (!this->Read_Color_Map_Value(Sprites::COIN_ANIMATION)) return false;

    //Read the Tile Map
    this->tileMap->clear();
    if (!this->Read_Tile_Map_Value(Sprites::KOOPA_TROOPA_GREEN)) return false;
    if (!this->Read_Tile_Map_Value(Sprites::KOOPA_TROOPA_GREEN_STOPPED)) return false;
    if (!this->Read_Tile_Map_Value(Sprites::KOOPA_TROOPA_RED)) return false;
    if (!this->Read_Tile_Map_Value(Sprites::KOOPA_TROOPA_LOOP)) return false;
    if (!this->Read_Tile_Map_Value(Sprites::BUZZY_BEETLE)) return false;
    if (!this->Read_Tile_Map_Value(Sprites::PARATROOPA_LEFT_RIGHT)) return false;
    if (!this->Read_Tile_Map_Value(Sprites::PARATROOPA_JUMP)) return false;
    if (!this->Read_Tile_Map_Value(Sprites::PARATROOPA_STOPPED)) return false;
    if (!this->Read_Tile_Map_Value(Sprites::PARATROOPA_UP_DOWN)) return false;
    if (!this->Read_Tile_Map_Value(Sprites::GOOMBA)) return false;
    if (!this->Read_Tile_Map_Value(Sprites::SPINY)) return false;
    if (!this->Read_Tile_Map_Value(Sprites::PIRANHA_PLANT)) return false;
    if (!this->Read_Tile_Map_Value(Sprites::CHEEP_CHEEP_MULTI_GREEN)) return false;
    if (!this->Read_Tile_Map_Value(Sprites::CHEEP_CHEEP_MULTI_RED)) return false;
    if (!this->Read_Tile_Map_Value(Sprites::FLYING_CHEEP_CHEEP)) return false;
    if (!this->Read_Tile_Map_Value(Sprites::BLOOPER)) return false;
    if (!this->Read_Tile_Map_Value(Sprites::PODOBOO)) return false;
    if (!this->Read_Tile_Map_Value(Sprites::BULLET_BILL_MULTI)) return false;
    if (!this->Read_Tile_Map_Value(Sprites::HAMMER_BROS)) return false;
    if (!this->Read_Tile_Map_Value(Sprites::BOWSER_FLAME_1)) return false;
    if (!this->Read_Tile_Map_Value(Sprites::BOWSER_FLAME_2)) return false;
    if (!this->Read_Tile_Map_Value(Sprites::HAMMER_1)) return false;
    if (!this->Read_Tile_Map_Value(Sprites::HAMMER_2)) return false;
    if (!this->Read_Tile_Map_Value(Sprites::HAMMER_3)) return false;
    if (!this->Read_Tile_Map_Value(Sprites::HAMMER_4)) return false;
    if (!this->Read_Tile_Map_Value(Sprites::MUSHROOM)) return false;
    if (!this->Read_Tile_Map_Value(Sprites::FIRE_FLOWER)) return false;
    if (!this->Read_Tile_Map_Value(Sprites::STARMAN)) return false;
    if (!this->Read_Tile_Map_Value(Sprites::ONE_UP_MUSHROOM)) return false;
    if (!this->Read_Tile_Map_Value(Sprites::LIFT)) return false;
    if (!this->Read_Tile_Map_Value(Sprites::SMALL_LIFT)) return false;
    if (!this->Read_Tile_Map_Value(Sprites::FIREWORKS_UL)) return false;
    if (!this->Read_Tile_Map_Value(Sprites::FIREWORKS_LL)) return false;
    if (!this->Read_Tile_Map_Value(Sprites::FIREBAR)) return false;
    if (!this->Read_Tile_Map_Value(Sprites::SPRINGBOARD_1)) return false;
    if (!this->Read_Tile_Map_Value(Sprites::SPRINGBOARD_2)) return false;
    if (!this->Read_Tile_Map_Value(Sprites::SPRINGBOARD_3)) return false;
    if (!this->Read_Tile_Map_Value(Sprites::BRICK_BLOCK)) return false;
    if (!this->Read_Tile_Map_Value(Sprites::BRICK_BLOCK_PIECE)) return false;
    if (!this->Read_Tile_Map_Value(Sprites::FIREWORKS_UR)) return false;
    if (!this->Read_Tile_Map_Value(Sprites::FIREWORKDS_LR)) return false;
    if (!this->Read_Tile_Map_Value(Sprites::VINE)) return false;
    if (!this->Read_Tile_Map_Value(Sprites::CASTLE_FLAG)) return false;
    if (!this->Read_Tile_Map_Value(Sprites::TOAD)) return false;
    if (!this->Read_Tile_Map_Value(Sprites::PEACH)) return false;
    if (!this->Read_Tile_Map_Value(Sprites::BUBBLE)) return false;
    if (!this->Read_Tile_Map_Value(Sprites::LAKITU)) return false;
    if (!this->Read_Tile_Map_Value(Sprites::FLAGPOLE)) return false;
    if (!this->Read_Tile_Map_Value(Sprites::EMPTY_BLOCK)) return false;
    if (!this->Read_Tile_Map_Value(Sprites::POINTS)) return false;
    if (!this->Read_Tile_Map_Value(Sprites::ONE_UP_TEXT)) return false;
    if (!this->Read_Tile_Map_Value(Sprites::COIN_TEXT)) return false;
    if (!this->Read_Tile_Map_Value(Sprites::BRICK_PIECE)) return false;
    if (!this->Read_Tile_Map_Value(Sprites::COIN_ANIMATION)) return false;
    return true;
}

bool Palette_Color_Mover::Read_Color_Map_Value(Sprites::Sprites value) {
    QByteArray bytes;
    qint64 offset = static_cast<qint64>(value);
    if (offset < 0) { //unknown ROM location
        switch (value) {
        default:                    assert(false); return false;
        case Sprites::POINTS:       this->colorMap->insert(value, 0x02); break;
        case Sprites::ONE_UP_TEXT:  this->colorMap->insert(value, 0x02); break;
        case Sprites::COIN_TEXT:    this->colorMap->insert(value, 0x03); break;
        case Sprites::BRICK_PIECE:  this->colorMap->insert(value, 0x03); break;
        case Sprites::COIN_ANIMATION:  this->colorMap->insert(value, 0x02); break;
        }
        return true;
    } else {
        if (!this->Read_Bytes_From_Offset(offset, 1, bytes)) return false;
        char byte = bytes.at(0);
        int colorValue = -1;
        if ((byte&0x03) == 0x00) colorValue = 0x00;
        else if ((byte&0x03) == 0x01) colorValue = 0x01;
        else if ((byte&0x03) == 0x02) colorValue = 0x02;
        else if ((byte&0x03) == 0x03) colorValue = 0x03;
        assert(colorValue != -1);
        this->colorMap->insert(value, colorValue);
        return true;
    }
}

bool Palette_Color_Mover::Read_Tile_Map_Value(Sprites::Sprites value) {
    //Get the Tiles or the Offsets of the Tiles
    QStack<qint64> offsets;
    QByteArray tiles;
    switch (value) {
    case Sprites::KOOPA_TROOPA_GREEN:               offsets.push(0x675A); offsets.push(0x6760); offsets.push(0x67A8); offsets.push(0x67AE); offsets.push(0x67B4); offsets.push(0x67BA); break;
    case Sprites::KOOPA_TROOPA_GREEN_STOPPED:       offsets.push(0x675A); offsets.push(0x6760); offsets.push(0x67A8); offsets.push(0x67AE); offsets.push(0x67B4); offsets.push(0x67BA); break;
    case Sprites::KOOPA_TROOPA_RED:                 offsets.push(0x675A); offsets.push(0x6760); offsets.push(0x67A8); offsets.push(0x67AE); offsets.push(0x67B4); offsets.push(0x67BA); break;
    case Sprites::KOOPA_TROOPA_LOOP:                offsets.push(0x675A); offsets.push(0x6760); offsets.push(0x67A8); offsets.push(0x67AE); offsets.push(0x67B4); offsets.push(0x67BA); break;
    case Sprites::BUZZY_BEETLE:                     offsets.push(0x674E); offsets.push(0x6754); offsets.push(0x67C0); offsets.push(0x67C6); offsets.push(0x67CC); offsets.push(0x67D2); break;
    case Sprites::PARATROOPA_LEFT_RIGHT:            offsets.push(0x6766); offsets.push(0x676C); offsets.push(0x67A8); offsets.push(0x67AE); offsets.push(0x67B4); offsets.push(0x67BA); break;
    case Sprites::PARATROOPA_JUMP:                  offsets.push(0x6766); offsets.push(0x676C); offsets.push(0x67A8); offsets.push(0x67AE); offsets.push(0x67B4); offsets.push(0x67BA); break;
    case Sprites::PARATROOPA_STOPPED:               offsets.push(0x6766); offsets.push(0x676C); offsets.push(0x67A8); offsets.push(0x67AE); offsets.push(0x67B4); offsets.push(0x67BA); break;
    case Sprites::PARATROOPA_UP_DOWN:               offsets.push(0x6766); offsets.push(0x676C); offsets.push(0x67A8); offsets.push(0x67AE); offsets.push(0x67B4); offsets.push(0x67BA); break;
    case Sprites::GOOMBA:                           offsets.push(0x67A2); offsets.push(0x67D8); break;
    case Sprites::SPINY:                            offsets.push(0x6772); offsets.push(0x6778); offsets.push(0x677E); offsets.push(0x6784); break;
    case Sprites::PIRANHA_PLANT:                    offsets.push(0x680E); offsets.push(0x6814); break;
    case Sprites::CHEEP_CHEEP_MULTI_GREEN:          offsets.push(0x6796); offsets.push(0x679C); break;
    case Sprites::CHEEP_CHEEP_MULTI_RED:            offsets.push(0x6796); offsets.push(0x679C); break;
    case Sprites::FLYING_CHEEP_CHEEP:               offsets.push(0x6796); offsets.push(0x679C); break;
    case Sprites::BLOOPER:                          offsets.push(0x678A); offsets.push(0x6790); break;
    case Sprites::PODOBOO:                          offsets.push(0x681A); break;
    case Sprites::BULLET_BILL_MULTI:                offsets.push(0x6838); break;
    case Sprites::HAMMER_BROS:                      offsets.push(0x67F6); offsets.push(0x67FC); offsets.push(0x6802); offsets.push(0x6808); break;
    case Sprites::BOWSER_FLAME_1:                   tiles = QByteArray::fromHex(QString("515253").toLatin1()); break;
    case Sprites::BOWSER_FLAME_2:                   tiles = QByteArray::fromHex(QString("515253").toLatin1()); break;
    case Sprites::HAMMER_1:                         tiles = QByteArray::fromHex(QString("80818283").toLatin1()); break;
    case Sprites::HAMMER_2:                         tiles = QByteArray::fromHex(QString("80818283").toLatin1()); break;
    case Sprites::HAMMER_3:                         tiles = QByteArray::fromHex(QString("80818283").toLatin1()); break;
    case Sprites::HAMMER_4:                         tiles = QByteArray::fromHex(QString("80818283").toLatin1()); break;
    case Sprites::MUSHROOM:                         tiles = QByteArray::fromHex(QString("76777879").toLatin1()); break;
    case Sprites::FIRE_FLOWER:                      tiles = QByteArray::fromHex(QString("D6D9").toLatin1()); break;
    case Sprites::STARMAN:                          tiles = QByteArray::fromHex(QString("8DE4").toLatin1()); break;
    case Sprites::ONE_UP_MUSHROOM:                  tiles = QByteArray::fromHex(QString("76777879").toLatin1()); break;
    case Sprites::LIFT:                             tiles = QByteArray(1, static_cast<char>(0x5B)); break;
    case Sprites::SMALL_LIFT:                       tiles = QByteArray(1, static_cast<char>(0x5B)); break;
    case Sprites::FIREWORKS_UL:                     tiles = QByteArray::fromHex(QString("666768").toLatin1()); break;
    case Sprites::FIREWORKS_LL:                     tiles = QByteArray::fromHex(QString("666768").toLatin1()); break;
    case Sprites::FIREBAR:                          tiles = QByteArray::fromHex(QString("6465").toLatin1()); break;
    case Sprites::SPRINGBOARD_1:                    offsets.push(0x683E); break;
    case Sprites::SPRINGBOARD_2:                    offsets.push(0x6844); break;
    case Sprites::SPRINGBOARD_3:                    offsets.push(0x684A); break;
    case Sprites::BRICK_BLOCK:                      tiles = QByteArray::fromHex(QString("8687").toLatin1()); break;
    case Sprites::BRICK_BLOCK_PIECE:                tiles = QByteArray(1, static_cast<char>(0x85)); break;
    case Sprites::FIREWORKS_UR:                     tiles = QByteArray::fromHex(QString("666768").toLatin1()); break;
    case Sprites::FIREWORKDS_LR:                    tiles = QByteArray::fromHex(QString("666768").toLatin1()); break;
    case Sprites::VINE:                             tiles = QByteArray::fromHex(QString("E0E1E2").toLatin1()); break;
    case Sprites::CASTLE_FLAG:                      tiles = QByteArray::fromHex(QString("54555657").toLatin1()); break;
    case Sprites::TOAD:                             offsets.push(0x67F0); break;
    case Sprites::PEACH:                            offsets.push(0x67EA); break;
    case Sprites::BUBBLE:                           tiles = QByteArray(1, static_cast<char>(0x74)); break;
    case Sprites::LAKITU:                           offsets.push(0x67DE); offsets.push(0x67E4); break;
    case Sprites::FLAGPOLE:                         tiles = QByteArray::fromHex(QString("7E7F").toLatin1()); break;
    case Sprites::EMPTY_BLOCK:                      tiles = QByteArray(1, static_cast<char>(0x88)); break;
    case Sprites::POINTS:                           tiles = QByteArray::fromHex(QString("50F6F7F8F9FAFB").toLatin1()); break;
    case Sprites::ONE_UP_TEXT:                      tiles = QByteArray::fromHex(QString("FDFE").toLatin1()); break;
    case Sprites::COIN_TEXT:                        tiles = QByteArray(1, static_cast<char>(0xFF)); break;
    case Sprites::BRICK_PIECE:                      tiles = QByteArray(1, static_cast<char>(0x84)); break;
    case Sprites::COIN_ANIMATION:                   tiles = QByteArray::fromHex(QString("60616263").toLatin1()); break;
    }
    assert(!offsets.isEmpty() || !tiles.isEmpty());

    //Insert the Data into the Tile Map
    QByteArray bytes;
    if (!tiles.isEmpty()) {
        this->tileMap->insert(value, tiles);
        return true;
    } else {
        while (!offsets.isEmpty()) {
            QByteArray tmpBytes;
            if (!this->Read_Bytes_From_Offset(offsets.pop(), 6, tmpBytes)) return false;
            bytes += tmpBytes;
        }
        assert(!bytes.isEmpty());
        this->tileMap->insert(value, bytes);
        return true;
    }
}

bool Palette_Color_Mover::Swap_Colors_In_Sprite_Group(int color1, int color2, int group) {
    assert(group > 0x00 && group < 0x05);
    if (!this->Read_Maps()) return false;

    for (QMap<Sprites::Sprites, int>::iterator iter = this->colorMap->begin(); iter != this->colorMap->end(); ++iter) {
        int colorGroup = iter.value();
        if (colorGroup == group) {
            Sprites::Sprites enemy = iter.key();
            QMap<Sprites::Sprites, QByteArray>::iterator tileEntry = this->tileMap->find(enemy);
            assert(tileEntry != this->tileMap->end());
            QByteArray tiles = tileEntry.value();
            for (char byte : tiles) {
                if (!this->Swap_Color_In_Sprite_Tile(byte, color1, color2)) return false;
            }
        }
    }
    return true;
}

bool Palette_Color_Mover::Swap_Color_In_Palette(int color1, int color2, qint64 offset) {
    QByteArray paletteBytes;
    if (!this->Read_Bytes_From_Offset(offset, 3, paletteBytes)) return false;
    char color1Palette = paletteBytes.data()[color1-1];
    char color2Palette = paletteBytes.data()[color2-1];
    paletteBytes.data()[color1-1] = color2Palette;
    paletteBytes.data()[color2-1] = color1Palette;
    return this->Write_Bytes_To_Offset(offset, paletteBytes);
}

bool Palette_Color_Mover::Swap_Color_In_Background_Tile(char tileID, int color1, int color2) {
    if (this->swappedTiles->constFind(tileID) != this->swappedTiles->constEnd()) return true; //tile already swapped
    this->swappedTiles->insert(tileID);
    QByteArray graphicsBytes;
    if (!this->Read_Graphics_Bytes_From_Background_Tile_ID(tileID, graphicsBytes)) return false;
    if (!this->Swap_Color_In_Graphics_Bytes(graphicsBytes, color1, color2)) return false;
    return this->Write_Graphics_Bytes_To_Background_Tile_ID(tileID, graphicsBytes);
}

bool Palette_Color_Mover::Swap_Color_In_Sprite_Tile(char tileID, int color1, int color2) {
    if (this->swappedTiles->constFind(tileID) != this->swappedTiles->constEnd()) return true; //tile already swapped
    this->swappedTiles->insert(tileID);
    QByteArray graphicsBytes;
    if (!this->Read_Graphics_Bytes_From_Sprite_Tile_ID(tileID, graphicsBytes)) return false;
    if (!this->Swap_Color_In_Graphics_Bytes(graphicsBytes, color1, color2)) return false;
    return this->Write_Graphics_Bytes_To_Sprite_Tile_ID(tileID, graphicsBytes);
}

bool Palette_Color_Mover::Swap_Color_In_Graphics_Bytes(QByteArray &graphicsBytes, int color1, int color2) {
    if (color1 == color2) return true; //nothing to do
    if (!this->Are_Colors_Valid(color1, color2)) return false;
    if (graphicsBytes.size() != 16) return false;

    //Split the Two Channels
    QByteArray channel1(8, static_cast<char>(0x00));
    for (int i = 0; i < 8; ++i) channel1.data()[i] = graphicsBytes.at(i);
    QByteArray channel2(8, static_cast<char>(0x00));
    for (int i = 0; i < 8; ++i) channel2.data()[i] = graphicsBytes.at(i+8);
    int color[64];
    for (int i = 0; i < 64; ++i) color[i] = 0;

    //Read the Colors
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            int andValue = 0x00;
            switch (j) {
            default:    assert(false); return false;
            case 0:     andValue = 0x80; break;
            case 1:     andValue = 0x40; break;
            case 2:     andValue = 0x20; break;
            case 3:     andValue = 0x10; break;
            case 4:     andValue = 0x08; break;
            case 5:     andValue = 0x04; break;
            case 6:     andValue = 0x02; break;
            case 7:     andValue = 0x01; break;
            }
            bool channel1BitSet = false, channel2BitSet = false;
            if ((channel1.at(i)&andValue) == andValue) channel1BitSet = true;
            if ((channel2.at(i)&andValue) == andValue) channel2BitSet = true;
            int colorValue = -1;
            if (!channel1BitSet && !channel2BitSet) colorValue = 0;
            if (channel1BitSet && !channel2BitSet) colorValue = 1;
            if (!channel1BitSet && channel2BitSet) colorValue = 2;
            if (channel1BitSet && channel2BitSet) colorValue = 3;
            assert(colorValue != -1);
            color[(i*8)+j] = colorValue;
        }
    }

    //Swap the Colors
    for (int i = 0; i < 64; ++i) {
        if (color[i] == color1) color[i] = color2;
        else if (color[i] == color2) color[i] = color1;
    }

    //Write the Colors
    channel1 = QByteArray(8, static_cast<char>(0x00)); //start with clean values
    channel2 = QByteArray(8, static_cast<char>(0x00));
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            int addValue = 0x00;
            switch (j) {
            default:    assert(false); return false;
            case 0:     addValue = 0x80; break;
            case 1:     addValue = 0x40; break;
            case 2:     addValue = 0x20; break;
            case 3:     addValue = 0x10; break;
            case 4:     addValue = 0x08; break;
            case 5:     addValue = 0x04; break;
            case 6:     addValue = 0x02; break;
            case 7:     addValue = 0x01; break;
            }
            int colorValue = color[(i*8)+j];
            switch (colorValue) {
            default:    assert(false); return false;
            case 0:     break; //nothing to do
            case 1:     channel1.data()[i] += addValue; break;
            case 2:     channel2.data()[i] += addValue; break;
            case 3:     channel1.data()[i] += addValue; channel2.data()[i] += addValue; break;
            }
        }
    }
    graphicsBytes = channel1+channel2;
    return true;
}

bool Palette_Color_Mover::Read_Graphics_Bytes_From_Background_Tile_ID(char tileID, QByteArray &graphicsBytes) {
    unsigned char c = static_cast<unsigned char>(tileID);
    qint64 spriteGraphicsOffset = 0x9010+(c*0x10); //get the graphics offset for the tile
    return this->Read_Bytes_From_Offset(spriteGraphicsOffset, 16, graphicsBytes);
}

bool Palette_Color_Mover::Read_Graphics_Bytes_From_Sprite_Tile_ID(char tileID, QByteArray &graphicsBytes) {
    unsigned char c = static_cast<unsigned char>(tileID);
    qint64 spriteGraphicsOffset = 0x8010+(c*0x10); //get the graphics offset for the tile
    return this->Read_Bytes_From_Offset(spriteGraphicsOffset, 16, graphicsBytes);
}

bool Palette_Color_Mover::Write_Graphics_Bytes_To_Background_Tile_ID(char tileID, const QByteArray &graphicsBytes) {
    if (graphicsBytes.size() != 16) return false;
    unsigned char c = static_cast<unsigned char>(tileID);
    qint64 spriteGraphicsOffset = 0x9010+(c*0x10); //get the graphics offset for the tile
    return this->Write_Bytes_To_Offset(spriteGraphicsOffset, graphicsBytes);
}

bool Palette_Color_Mover::Write_Graphics_Bytes_To_Sprite_Tile_ID(char tileID, const QByteArray &graphicsBytes) {
    if (graphicsBytes.size() != 16) return false;
    unsigned char c = static_cast<unsigned char>(tileID);
    qint64 spriteGraphicsOffset = 0x8010+(c*0x10); //get the graphics offset for the tile
    return this->Write_Bytes_To_Offset(spriteGraphicsOffset, graphicsBytes);
}
