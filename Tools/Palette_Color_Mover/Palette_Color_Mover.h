#ifndef PALETTE_COLOR_MOVER_H
#define PALETTE_COLOR_MOVER_H

#include "../../../Level-Headed/SMB1/SMB1_Writer/Byte_Writer.h"
#include <QSet>
#include "Sprites.h"

class Palette_Color_Mover : public Byte_Writer {
public:
    Palette_Color_Mover(QFile *file, Level_Offset *levelOffset);
    ~Palette_Color_Mover();

    bool Swap_Colors_In_RGB_Groups(int color1, int color2);
    bool Swap_Colors_In_Red_Group(int color1, int color2);
    bool Swap_Colors_In_Green_Group(int color1, int color2);
    bool Swap_Colors_In_Blue_Group(int color1, int color2);

    bool Swap_Colors_In_Mario_Group(int color1, int color2); //also updates Luigi and Fire Mario
    bool Swap_Colors_In_Bowser_Group(int color1, int color2);

private:
    bool Are_Colors_Valid(int color1, int color2);
    bool Read_Maps();
    bool Read_Color_Map_Value(Sprites::Sprites value);
    bool Read_Tile_Map_Value(Sprites::Sprites value);

    bool Swap_Colors_In_Sprite_Group(int color1, int color2, int group);
    bool Swap_Color_In_Palette(int color1, int color2, qint64 offset);

    bool Swap_Color_In_Background_Tile(char tileID, int color1, int color2);
    bool Swap_Color_In_Sprite_Tile(char tileID, int color1, int color2);
    bool Swap_Color_In_Graphics_Bytes(QByteArray &graphicsBytes, int color1, int color2);

    bool Read_Graphics_Bytes_From_Background_Tile_ID(char tileID, QByteArray &graphicsBytes);
    bool Read_Graphics_Bytes_From_Sprite_Tile_ID(char tileID, QByteArray &graphicsBytes);
    bool Write_Graphics_Bytes_To_Background_Tile_ID(char tileID, const QByteArray &graphicsBytes);
    bool Write_Graphics_Bytes_To_Sprite_Tile_ID(char tileID, const QByteArray &graphicsBytes);

    QMap<Sprites::Sprites, int> *colorMap;
    QMap<Sprites::Sprites, QByteArray> *tileMap;
    QSet<char> *swappedTiles;
};

#endif // PALETTE_COLOR_MOVER_H
