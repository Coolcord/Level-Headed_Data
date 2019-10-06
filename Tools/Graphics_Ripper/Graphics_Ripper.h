#ifndef GRAPHICS_RIPPER_H
#define GRAPHICS_RIPPER_H

#include "../../../Hexagon/Hexagon/Hexagon_Interface.h"
#include <QByteArray>
#include <QSet>
#include <QStack>

class Graphics_Ripper {
public:
    Graphics_Ripper(const QString &applicationLocation, const QString &originalFileLocation, const QString &patchFileLocation, Hexagon_Interface *hexagon);
    ~Graphics_Ripper();
    bool Rip_All();

    //Sprites
    bool Rip_Air_Bubble();
    bool Rip_Blooper();
    bool Rip_Bowser();
    bool Rip_Bullet_Bill();
    bool Rip_Buzzy_Beetle();
    bool Rip_Castle_Flag();
    bool Rip_Cheep_Cheep();
    bool Rip_Coin_Animation();
    bool Rip_Explosion();
    bool Rip_Fireball();
    bool Rip_Flagpole_Flag();
    bool Rip_Goomba();
    bool Rip_Hammer_Bro();
    bool Rip_Jump_Spring();
    bool Rip_Koopa();
    bool Rip_Lakitu();
    bool Rip_Lift();
    bool Rip_Mario();
    bool Rip_One_Up_Font();
    bool Rip_Peach();
    bool Rip_Piranha_Plant();
    bool Rip_Podoboo();
    bool Rip_Score_Font();
    bool Rip_Sky_Lift();
    bool Rip_Spiny();
    bool Rip_Spiny_Egg();
    bool Rip_Toad();

    //Background
    bool Rip_Axe();
    bool Rip_Brick_Block();
    bool Rip_Bridge();
    bool Rip_Bowser_Bridge();
    bool Rip_Bullet_Bill_Cannon();
    bool Rip_Castle_Block();
    bool Rip_Chain();
    bool Rip_Cloud_Block();
    bool Rip_Coin();
    bool Rip_Coral();
    bool Rip_Fire_Flower();
    bool Rip_Flagpole();
    bool Rip_Font();
    bool Rip_Mushroom_Powerup();
    bool Rip_Mushroom_Platform();
    bool Rip_Overworld_Block();
    bool Rip_Pipe();
    bool Rip_Question_Block();
    bool Rip_Rope();
    bool Rip_Solid_Block();
    bool Rip_Tree_Platform();
    bool Rip_Underwater_Block();
    bool Rip_Water();

private:
    bool Apply_Patch();
    bool Create_Patch(const QString &sprite);
    void Close_Files();
    void Close_Working_Files();
    bool Does_Patch_Use_New_Tiles(const QByteArray &oldTiles, qint64 offset, bool sprite);
    bool Does_Patch_Use_New_Tiles(const QByteArray &oldTiles, QStack<qint64> offsets, bool sprite);
    QString Get_Base_Name_From_Path(const QString &path);
    bool Is_Tile_Blank(char tileID, bool sprite);
    bool Read_Graphics_Bytes_From_Sprite_Tile_ID(char tileID, QByteArray &graphicsBytes);
    bool Read_Graphics_Bytes_From_Background_Tile_ID(char tileID, QByteArray &graphicsBytes);
    bool Recreate_Working_File();
    bool Scan_For_Palette_Allowed();
    bool Write_Background_Tiles_To_Working_File(const QByteArray &tiles);
    bool Write_Sprite_Tiles_To_Working_File(const QByteArray &tiles);
    bool Write_Tiles_And_Order_To_Working_File(qint64 offset, bool sprite);
    bool Write_Tiles_And_Order_To_Working_File(QStack<qint64> offsets, bool sprite);
    bool Write_Tiles_To_Working_File(const QByteArray &tiles, bool sprite);

    QString applicationLocation;
    QString originalFileLocation;
    QString workingFileLocation; //0x52
    QString baseFileLocation;
    QString patchFileLocation;
    QFile *originalFile;
    QFile *workingFile;
    QFile *baseFile;
    QFile *outputFile;
    Hexagon_Interface *hexagon;
    QSet<char> writtenBackgroundTiles;
    QSet<char> writtenSpriteTiles;
    bool palettesDisabled;
};

#endif // GRAPHICS_RIPPER_H