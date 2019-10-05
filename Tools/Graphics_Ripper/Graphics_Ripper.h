#ifndef GRAPHICS_RIPPER_H
#define GRAPHICS_RIPPER_H

#include "../../../Hexagon/Hexagon/Hexagon_Interface.h"
#include <QByteArray>

class Graphics_Ripper {
public:
    Graphics_Ripper(const QString &originalFileLocation, const QString &patchFileLocation, Hexagon_Interface *hexagon);
    ~Graphics_Ripper();
    bool Rip_All();

    //Sprites
    bool Rip_Blooper();
    bool Rip_Bowser();
    bool Rip_Bullet_Bill();
    bool Rip_Buzzy_Beetle();
    bool Rip_Cheep_Cheep();
    bool Rip_Goomba();
    bool Rip_Hammer_Bro();
    bool Rip_Koopa();
    bool Rip_Lakitu();
    bool Rip_Jump_Spring();
    bool Rip_Mario();
    bool Rip_Peach();
    bool Rip_Piranha_Plant();
    bool Rip_Podoboo();
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
    bool Rip_Mushroom_Powerup();
    bool Rip_Mushroom_Platform();
    bool Rip_Overworld_Block();
    bool Rip_Pipe();
    bool Rip_Question_Block();
    bool Rip_Rope();
    bool Rip_Solid_Block();
    bool Rip_Text();
    bool Rip_Tree_Platform();
    bool Rip_Underwater_Block();
    bool Rip_Water();

private:
    bool Apply_Patch();
    bool Read_Graphics_Bytes_From_Sprite_Tile_ID(char tileID, QByteArray &graphicsBytes);
    bool Read_Graphics_Bytes_From_Background_Tile_ID(char tileID, QByteArray &graphicsBytes);

    QString originalFileLocation;
    QString patchFileLocation;
    QFile *outputFile;
    Hexagon_Interface *hexagon;
};

#endif // GRAPHICS_RIPPER_H
