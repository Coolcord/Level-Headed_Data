#include "Graphics_Ripper.h"
#include "../../../Hexagon/Hexagon/Value_Manipulator.h"
#include "../../../Level-Headed/SMB1/Common_SMB1_Files/Fix_Strings.h"
#include "../../../Level-Headed/SMB1/SMB1_Writer/Graphics_Offsets.h"
#include "Blacklist.h"
#include <assert.h>
#include <QDebug>
#include <QDir>
#include <QFileInfo>

Graphics_Ripper::Graphics_Ripper(const QString &applicationLocation, const QString &originalFileLocation, const QString &patchFileLocation, Hexagon_Interface *hexagon) {
    assert(hexagon);
    this->applicationLocation = applicationLocation;
    this->originalFileLocation = originalFileLocation;
    this->patchFileLocation = patchFileLocation;
    this->hexagon = hexagon;
    this->usedOffsets = new QMap<qint64, QByteArray*>();
    this->palettesDisabled = false;
    this->outputFile = nullptr;
    this->originalFile = nullptr;
    this->marioSpriteBlacklist = nullptr;
    this->graphicsOffsets = new Graphics_Offsets();
}

Graphics_Ripper::~Graphics_Ripper() {
    this->Close_Files();
    for (QByteArray *bytes : this->usedOffsets->values()) delete bytes;
    delete this->usedOffsets;
    delete this->graphicsOffsets;
    delete this->marioSpriteBlacklist;
}

bool Graphics_Ripper::Rip_All() {
    if (!this->Rip_Air_Bubble()) return false;
    if (!this->Rip_Blooper()) return false;
    if (!this->Rip_Bowser()) return false;
    if (!this->Rip_Bowser_Fire()) return false;
    if (!this->Rip_Brick_Piece()) return false;
    if (!this->Rip_Bullet_Bill()) return false;
    if (!this->Rip_Buzzy_Beetle()) return false;
    if (!this->Rip_Castle_Flag()) return false;
    if (!this->Rip_Chain()) return false;
    if (!this->Rip_Cheep_Cheep()) return false;
    if (!this->Rip_Coin_Animation()) return false;
    if (!this->Rip_Explosion()) return false;
    if (!this->Rip_Fireball()) return false;
    if (!this->Rip_Flagpole_Flag()) return false;
    if (!this->Rip_Goomba()) return false;
    if (!this->Rip_Hammer()) return false;
    if (!this->Rip_Hammer_Bro()) return false;
    if (!this->Rip_Jump_Spring()) return false;
    if (!this->Rip_Koopa()) return false;
    if (!this->Rip_Lakitu()) return false;
    if (!this->Rip_Lift()) return false;
    //if (!this->Rip_Mario()) return false;
    //if (!this->Rip_Mario_Using_Blacklist()) return false;
    if (!this->Rip_One_Up_Font()) return false;
    if (!this->Rip_Peach()) return false;
    if (!this->Rip_Piranha_Plant()) return false;
    if (!this->Rip_Podoboo()) return false;
    if (!this->Rip_Score_Font()) return false;
    if (!this->Rip_Sky_Lift()) return false;
    if (!this->Rip_Spiny()) return false;
    if (!this->Rip_Spiny_Egg()) return false;
    if (!this->Rip_Toad()) return false;
    if (!this->Rip_Axe()) return false;
    if (!this->Rip_Brick_Block()) return false;
    if (!this->Rip_Bowser_Bridge()) return false;
    if (!this->Rip_Bridge()) return false;
    if (!this->Rip_Bullet_Bill_Cannon()) return false;
    if (!this->Rip_Castle_Block()) return false;
    if (!this->Rip_Cloud_Block()) return false;
    if (!this->Rip_Coin()) return false;
    if (!this->Rip_Coin_Icon()) return false;
    if (!this->Rip_Coral()) return false;
    if (!this->Rip_Fire_Flower()) return false;
    if (!this->Rip_Flagpole()) return false;
    if (!this->Rip_Font()) return false;
    if (!this->Rip_Mushroom_Powerup()) return false;
    if (!this->Rip_Mushroom_Platform()) return false;
    if (!this->Rip_Overworld_Block()) return false;
    if (!this->Rip_Pipe()) return false;
    if (!this->Rip_Question_Block()) return false;
    if (!this->Rip_Rope()) return false;
    if (!this->Rip_Selector_Icon()) return false;
    if (!this->Rip_Solid_Block()) return false;
    if (!this->Rip_Starman()) return false;
    if (!this->Rip_Tree_Platform()) return false;
    if (!this->Rip_Underwater_Block()) return false;
    if (!this->Rip_Vine()) return false;
    if (!this->Rip_Water()) return false;
    return true;
}

bool Graphics_Ripper::Dump_Tile_Order_Map(const QString &graphicsOffsetsFileLocation) {
    qInfo() << "Dumping tile order map";
    QFile inputFile(graphicsOffsetsFileLocation);
    if (!inputFile.open(QIODevice::ReadOnly)) return false;
    QFile outputFile(this->applicationLocation+"/Graphics_Offsets.cpp");
    outputFile.remove();
    if (!outputFile.open(QIODevice::ReadWrite)) { inputFile.close(); return false; }

    Value_Manipulator valueManipulator;
    QTextStream inputStream(&inputFile);
    QTextStream outputStream(&outputFile);
    QString headerLine1 = "    //=========================================================================================================================";
    QString headerLine2 = "    //====================================================== DO NOT EDIT ======================================================";
    QString headerLine3 = "    //============================= THIS SECTION IS AUTOMATICALLY GENERATED BY THE GRAPHICS RIPPER ============================";
    int section = 0;
    bool success = false;
    while (!inputStream.atEnd()) {
        QString line = inputStream.readLine();
        switch (section) {
        case 0: //Look for header 1
            if (line == headerLine1) ++section;
            else outputStream << line << Patch_Strings::STRING_NEW_LINE;
            break;
        case 1: //Look for header 2
            if (line == headerLine2) ++section;
            else section = 0;
            break;
        case 2: //Look for header 3
            if (line == headerLine3) ++section;
            else section = 0;
            break;
        case 3: //Look for header 1 again
            if (line == headerLine1) ++section;
            else section = 0;
            break;
        case 4: //Write the tile order map
            outputStream << headerLine1 << Patch_Strings::STRING_NEW_LINE;
            outputStream << headerLine2 << Patch_Strings::STRING_NEW_LINE;
            outputStream << headerLine3 << Patch_Strings::STRING_NEW_LINE;
            outputStream << headerLine1 << Patch_Strings::STRING_NEW_LINE;
            for (qint64 offset : this->usedOffsets->keys()) {
                outputStream << "    this->tileOrderMap->insert(0x"+QString::number(offset, 0x10).toUpper()+", new QByteArray(QByteArray::fromHex(QString(\""
                       << valueManipulator.Convert_QByteArray_To_QString(*this->usedOffsets->find(offset).value()) << "\").toLatin1())));" << Patch_Strings::STRING_NEW_LINE;
            }
            outputStream << headerLine1 << Patch_Strings::STRING_NEW_LINE;
            ++section;
            success = true;
            break;
        case 5: //Scan past the old tile order map
            if (line == headerLine1) ++section;
            break;
        case 6: //Done scanning and writing, so just copy the rest
            outputStream << line << Patch_Strings::STRING_NEW_LINE;
            break;
        }
    }
    inputFile.close();
    outputStream.flush();
    outputFile.close();
    if (!success) return false;

    //Copy the new file
    inputFile.remove();
    if (!inputFile.open(QIODevice::ReadWrite)) return false;
    if (!outputFile.open(QIODevice::ReadOnly)) { inputFile.close(); return false; }
    success = inputFile.write(outputFile.readAll()) == outputFile.size();
    inputFile.close();
    outputFile.close();
    return success;
}

bool Graphics_Ripper::Rip_Air_Bubble() {
    if (!this->Apply_Patch("Air Bubble")) return false;
    if (!this->Write_Sprite_Tiles_To_Working_File(QByteArray(1, static_cast<char>(0x75)))) return false;
    return this->Create_Patch();
}

bool Graphics_Ripper::Rip_Blooper() {
    if (!this->Apply_Patch("Blooper")) return false;
    bool sprite = true;
    QStack<qint64> offsets = this->graphicsOffsets->Get_Blooper_Offsets();
    if (this->Does_Patch_Use_New_Tiles(offsets, sprite, 0)) return true;
    if (!this->Write_Tiles_And_Order_To_Working_File(offsets, sprite, 0)) return false;
    return this->Create_Patch();
}

bool Graphics_Ripper::Rip_Bowser() {
    if (!this->Apply_Patch("Bowser")) return false;
    bool sprite = true;
    QStack<qint64> offsets = this->graphicsOffsets->Get_Bowser_Offsets();
    if (this->Does_Patch_Use_New_Tiles(offsets, sprite, 0)) return true;
    if (!this->Write_Tiles_And_Order_To_Working_File(offsets, sprite, 0)) return false;
    if (!this->Write_Data_To_Working_File(0x0D60, 3)) return false; //write the palette
    return this->Create_Patch();
}

bool Graphics_Ripper::Rip_Bowser_Fire() {
    if (!this->Apply_Patch("Bowser Fire")) return false;
    if (!this->Write_Sprite_Tiles_To_Working_File(QByteArray::fromHex(QString("515253").toLatin1()))) return false;
    return this->Create_Patch();
}

bool Graphics_Ripper::Rip_Brick_Piece() {
    if (!this->Apply_Patch("Brick Piece")) return false;
    if (!this->Write_Sprite_Tiles_To_Working_File(QByteArray::fromHex(QString("84").toLatin1()))) return false;
    return this->Create_Patch();
}

bool Graphics_Ripper::Rip_Bullet_Bill() {
    if (!this->Apply_Patch("Bullet Bill")) return false;
    bool sprite = true;
    QStack<qint64> offsets = this->graphicsOffsets->Get_Bullet_Bill_Offsets();
    if (this->Does_Patch_Use_New_Tiles(offsets, sprite, 0)) return true;
    if (!this->Write_Tiles_And_Order_To_Working_File(offsets, sprite, 0)) return false;
    return this->Create_Patch();
}

bool Graphics_Ripper::Rip_Buzzy_Beetle() {
    if (!this->Apply_Patch("Buzzy Beetle")) return false;
    bool sprite = true;
    QStack<qint64> offsets = this->graphicsOffsets->Get_Buzzy_Beetle_Offsets();
    if (this->Does_Patch_Use_New_Tiles(offsets, sprite, 0)) return true;
    if (!this->Write_Tiles_And_Order_To_Working_File(offsets, sprite, 0)) return false;
    return this->Create_Patch();
}

bool Graphics_Ripper::Rip_Castle_Flag() {
    if (!this->Apply_Patch("Castle Flag")) return false;
    if (!this->Write_Sprite_Tiles_To_Working_File(QByteArray::fromHex(QString("54555657").toLatin1()))) return false;
    return this->Create_Patch();
}

bool Graphics_Ripper::Rip_Cheep_Cheep() {
    if (!this->Apply_Patch("Cheep Cheep")) return false;
    bool sprite = true;
    QStack<qint64> offsets = this->graphicsOffsets->Get_Cheep_Cheep_Offsets();
    if (this->Does_Patch_Use_New_Tiles(offsets, sprite, 0)) return true;
    if (!this->Write_Tiles_And_Order_To_Working_File(offsets, sprite, 0)) return false;
    return this->Create_Patch();
}

bool Graphics_Ripper::Rip_Coin_Animation() {
    if (!this->Apply_Patch("Coin Animation")) return false;
    if (!this->Write_Sprite_Tiles_To_Working_File(QByteArray::fromHex(QString("60616263").toLatin1()))) return false;
    return this->Create_Patch();
}

bool Graphics_Ripper::Rip_Explosion() {
    if (!this->Apply_Patch("Explosion")) return false;
    if (!this->Write_Sprite_Tiles_To_Working_File(QByteArray::fromHex(QString("666768").toLatin1()))) return false;
    return this->Create_Patch();
}

bool Graphics_Ripper::Rip_Fireball() {
    if (!this->Apply_Patch("Fireball")) return false;
    if (!this->Write_Sprite_Tiles_To_Working_File(QByteArray::fromHex(QString("6465").toLatin1()))) return false;
    return this->Create_Patch();
}

bool Graphics_Ripper::Rip_Fire_Flower() {
    if (!this->Apply_Patch("Powerup Fire Flower")) return false;
    if (!this->Write_Sprite_Tiles_To_Working_File(QByteArray::fromHex(QString("D6D9").toLatin1()))) return false;
    return this->Create_Patch();
}

bool Graphics_Ripper::Rip_Flagpole_Flag() {
    if (!this->Apply_Patch("Flagpole Flag")) return false;
    if (!this->Write_Sprite_Tiles_To_Working_File(QByteArray::fromHex(QString("7E7F").toLatin1()))) return false;
    return this->Create_Patch();
}

bool Graphics_Ripper::Rip_Goomba() {
    if (!this->Apply_Patch("Goomba")) return false;
    bool sprite = true;
    QStack<qint64> offsets = this->graphicsOffsets->Get_Goomba_Offsets();
    if (this->Does_Patch_Use_New_Tiles(offsets, sprite, 0)) return true;
    if (!this->Write_Tiles_And_Order_To_Working_File(offsets, sprite, 0)) return false;
    return this->Create_Patch();
}

bool Graphics_Ripper::Rip_Hammer() {
    if (!this->Apply_Patch("Hammer")) return false;
    if (!this->Write_Sprite_Tiles_To_Working_File(QByteArray::fromHex(QString("80818283").toLatin1()))) return false;
    return this->Create_Patch();
}

bool Graphics_Ripper::Rip_Hammer_Bro() {
    if (!this->Apply_Patch("Hammer Bro")) return false;
    bool sprite = true;
    QStack<qint64> offsets = this->graphicsOffsets->Get_Hammer_Bro_Offsets();
    if (this->Does_Patch_Use_New_Tiles(offsets, sprite, 0)) return true;
    if (!this->Write_Tiles_And_Order_To_Working_File(offsets, sprite, 0)) return false;
    return this->Create_Patch();
}

bool Graphics_Ripper::Rip_Jump_Spring() {
    if (!this->Apply_Patch("Jump Spring")) return false;

    //Jump Spring Sprite
    bool sprite = true;
    QStack<qint64> offsets = this->graphicsOffsets->Get_Jump_Spring_Animation_Offsets();
    if (this->Does_Patch_Use_New_Tiles(offsets, sprite, 0)) return true;
    if (!this->Write_Tiles_And_Order_To_Working_File(offsets, sprite, 0)) return false;

    //Brick Base
    sprite = false;
    offsets = this->graphicsOffsets->Get_Jump_Spring_Base_Offsets();
    if (this->Does_Patch_Use_New_Tiles(offsets, sprite, 0)) return true;
    if (!this->Write_Tiles_And_Order_To_Working_File(offsets, sprite, 0)) return false;
    return this->Create_Patch();
}

bool Graphics_Ripper::Rip_Koopa() {
    if (!this->Apply_Patch("Koopa")) return false;
    bool sprite = true;
    QStack<qint64> offsets = this->graphicsOffsets->Get_Koopa_Offsets();
    if (this->Does_Patch_Use_New_Tiles(offsets, sprite, 0)) return true;
    if (!this->Write_Tiles_And_Order_To_Working_File(offsets, sprite, 0)) return false;
    return this->Create_Patch();
}

bool Graphics_Ripper::Rip_Lakitu() {
    if (!this->Apply_Patch("Lakitu")) return false;
    bool sprite = true;
    QStack<qint64> offsets = this->graphicsOffsets->Get_Lakitu_Offsets();
    if (this->Does_Patch_Use_New_Tiles(offsets, sprite, 0)) return true;
    if (!this->Write_Tiles_And_Order_To_Working_File(offsets, sprite, 0)) return false;
    return this->Create_Patch();
}

bool Graphics_Ripper::Rip_Lift() {
    if (!this->Apply_Patch("Lift")) return false;
    if (!this->Write_Sprite_Tiles_To_Working_File(QByteArray::fromHex(QString("5B").toLatin1()))) return false;
    return this->Create_Patch();
}

bool Graphics_Ripper::Rip_Mario() {
    if (!this->Apply_Patch("Mario")) return false;

    //Write the Tile Order
    bool sprite = true;
    QStack<qint64> offsets = this->graphicsOffsets->Get_Mario_Offsets();
    if (!this->Write_Tiles_And_Order_To_Working_File(offsets, sprite, 8)) return false;

    //Write the Palette
    if (!this->Write_Data_To_Working_File(0x05E8, 3)) return false;
    if (!this->Write_Data_To_Working_File(0x05EC, 3)) return false;
    if (!this->Write_Data_To_Working_File(0x05F0, 3)) return false;
    return this->Create_Patch();
}

bool Graphics_Ripper::Rip_Mario_Using_Blacklist() {
    if (!this->marioSpriteBlacklist) {
        this->marioSpriteBlacklist = new Blacklist();
        this->marioSpriteBlacklist->Populate_Mario_Sprite_Blacklist();
    }
    QString patchName = this->Get_Base_Name_From_Path(this->patchFileLocation);
    if (this->marioSpriteBlacklist->Is_Blacklisted(patchName)) return true;
    if (!this->Apply_Patch("Mario", this->marioSpriteBlacklist->Get_Suggested_File_Name(patchName))) return false;

    //Write the Tile Order
    bool sprite = true;
    QStack<qint64> offsets = this->graphicsOffsets->Get_Mario_Offsets();
    if (this->Does_Patch_Use_New_Tiles(offsets, sprite, 8)) return true;
    if (!this->Write_Tiles_And_Order_To_Working_File(offsets, sprite, 8)) return false;

    //Write the Palette
    if (!this->Write_Data_To_Working_File(0x05E8, 3)) return false;
    if (!this->Write_Data_To_Working_File(0x05EC, 3)) return false;
    if (!this->Write_Data_To_Working_File(0x05F0, 3)) return false;
    return this->Create_Patch();
}

bool Graphics_Ripper::Rip_Mushroom_Powerup() {
    if (!this->Apply_Patch("Powerup Mushroom")) return false;
    if (!this->Write_Sprite_Tiles_To_Working_File(QByteArray::fromHex(QString("76777879").toLatin1()))) return false;
    return this->Create_Patch();
}

bool Graphics_Ripper::Rip_One_Up_Font() {
    if (!this->Apply_Patch("Font One Up")) return false;
    if (!this->Write_Sprite_Tiles_To_Working_File(QByteArray::fromHex(QString("FDFE").toLatin1()))) return false;
    return this->Create_Patch();
}

bool Graphics_Ripper::Rip_Peach() {
    if (!this->Apply_Patch("Peach")) return false;
    bool sprite = true;
    QStack<qint64> offsets = this->graphicsOffsets->Get_Peach_Offsets();
    if (this->Does_Patch_Use_New_Tiles(offsets, sprite, 0)) return true;
    if (!this->Write_Tiles_And_Order_To_Working_File(offsets, sprite, 0)) return false;
    return this->Create_Patch();
}

bool Graphics_Ripper::Rip_Piranha_Plant() {
    if (!this->Apply_Patch("Piranha Plant")) return false;
    bool sprite = true;
    QStack<qint64> offsets = this->graphicsOffsets->Get_Piranha_Plant_Offsets();
    if (this->Does_Patch_Use_New_Tiles(offsets, sprite, 0)) return true;
    if (!this->Write_Tiles_And_Order_To_Working_File(offsets, sprite, 0)) return false;
    return this->Create_Patch();
}

bool Graphics_Ripper::Rip_Podoboo() {
    if (!this->Apply_Patch("Podoboo")) return false;
    bool sprite = true;
    QStack<qint64> offsets = this->graphicsOffsets->Get_Podoboo_Offsets();
    if (this->Does_Patch_Use_New_Tiles(offsets, sprite, 0)) return true;
    if (!this->Write_Tiles_And_Order_To_Working_File(offsets, sprite, 0)) return false;
    return this->Create_Patch();
}

bool Graphics_Ripper::Rip_Score_Font() {
    if (!this->Apply_Patch("Font Score")) return false;
    if (!this->Write_Sprite_Tiles_To_Working_File(QByteArray::fromHex(QString("50F6F7F8F9FAFB").toLatin1()))) return false;
    return this->Create_Patch();
}

bool Graphics_Ripper::Rip_Sky_Lift() {
    if (!this->Apply_Patch("Lift Sky")) return false;
    if (!this->Write_Sprite_Tiles_To_Working_File(QByteArray(1, static_cast<char>(0x75)))) return false;
    return this->Create_Patch();
}

bool Graphics_Ripper::Rip_Spiny() {
    if (!this->Apply_Patch("Spiny")) return false;
    bool sprite = true;
    QStack<qint64> offsets = this->graphicsOffsets->Get_Spiny_Offsets();
    if (this->Does_Patch_Use_New_Tiles(offsets, sprite, 0)) return true;
    if (!this->Write_Tiles_And_Order_To_Working_File(offsets, sprite, 0)) return false;
    return this->Create_Patch();
}

bool Graphics_Ripper::Rip_Spiny_Egg() {
    if (!this->Apply_Patch("Spiny Egg")) return false;
    bool sprite = true;
    QStack<qint64> offsets = this->graphicsOffsets->Get_Spiny_Egg_Offsets();
    if (this->Does_Patch_Use_New_Tiles(offsets, sprite, 0)) return true;
    if (!this->Write_Tiles_And_Order_To_Working_File(offsets, sprite, 0)) return false;
    return this->Create_Patch();
}

bool Graphics_Ripper::Rip_Starman() {
    if (!this->Apply_Patch("Starman")) return false;
    if (!this->Write_Sprite_Tiles_To_Working_File(QByteArray::fromHex(QString("8DE4").toLatin1()))) return false;
    return this->Create_Patch();
}

bool Graphics_Ripper::Rip_Toad() {
    if (!this->Apply_Patch("Toad")) return false;
    bool sprite = true;
    QStack<qint64> offsets = this->graphicsOffsets->Get_Toad_Offsets();
    if (this->Does_Patch_Use_New_Tiles(offsets, sprite, 0)) return true;
    if (!this->Write_Tiles_And_Order_To_Working_File(offsets, sprite, 0)) return false;
    return this->Create_Patch();
}

bool Graphics_Ripper::Rip_Axe() {
    if (!this->Apply_Patch("Axe")) return false;
    bool sprite = false;
    QStack<qint64> offsets = this->graphicsOffsets->Get_Axe_Offsets();
    if (this->Does_Patch_Use_New_Tiles(offsets, sprite, 0)) return true;
    if (!this->Write_Tiles_And_Order_To_Working_File(offsets, sprite, 0)) return false;
    return this->Create_Patch();
}

bool Graphics_Ripper::Rip_Brick_Block() {
    if (!this->Apply_Patch("Brick Block")) return false;
    bool sprite = false;
    QStack<qint64> offsets = this->graphicsOffsets->Get_Brick_Block_Offsets();
    QStack<qint64> brickHitOffsets = this->graphicsOffsets->Get_Brick_Block_Animation_Offsets();
    if (this->Does_Patch_Use_New_Tiles(offsets, sprite, 0)) return true;
    if (this->Does_Patch_Use_New_Tiles(brickHitOffsets, true, 4)) return true;
    if (!this->Write_Tiles_And_Order_To_Working_File(offsets, sprite, 0)) return false;
    if (!this->Write_Tiles_And_Order_To_Working_File(brickHitOffsets, true, 4)) return false;
    if (!this->Write_Background_Tiles_To_Working_File(QByteArray(1, static_cast<char>(0x45)))) return false;
    return this->Create_Patch();
}

bool Graphics_Ripper::Rip_Bowser_Bridge() {
    if (!this->Apply_Patch("Bowser Bridge")) return false;
    bool sprite = false;
    QStack<qint64> offsets = this->graphicsOffsets->Get_Bowser_Bridge_Offsets();
    if (this->Does_Patch_Use_New_Tiles(offsets, sprite, 0)) return true;
    if (!this->Write_Tiles_And_Order_To_Working_File(offsets, sprite, 0)) return false;
    return this->Create_Patch();
}

bool Graphics_Ripper::Rip_Bridge() {
    if (!this->Apply_Patch("Bridge")) return false;
    bool sprite = false;
    QStack<qint64> offsets = this->graphicsOffsets->Get_Bridge_Offsets();
    if (this->Does_Patch_Use_New_Tiles(offsets, sprite, 0)) return true;
    if (!this->Write_Tiles_And_Order_To_Working_File(offsets, sprite, 0)) return false;
    return this->Create_Patch();
}

bool Graphics_Ripper::Rip_Bullet_Bill_Cannon() {
    if (!this->Apply_Patch("Bullet Bill Cannon")) return false;
    bool sprite = false;
    QStack<qint64> offsets = this->graphicsOffsets->Get_Bullet_Bill_Cannon_Offsets();
    if (this->Does_Patch_Use_New_Tiles(offsets, sprite, 0)) return true;
    if (!this->Write_Tiles_And_Order_To_Working_File(offsets, sprite, 0)) return false;
    return this->Create_Patch();
}

bool Graphics_Ripper::Rip_Castle_Block() {
    if (!this->Apply_Patch("Block Castle")) return false;
    bool sprite = false;
    QStack<qint64> offsets = this->graphicsOffsets->Get_Castle_Block_Offsets();
    if (this->Does_Patch_Use_New_Tiles(offsets, sprite, 0)) return true;
    if (!this->Write_Tiles_And_Order_To_Working_File(offsets, sprite, 0)) return false;
    return this->Create_Patch();
}

bool Graphics_Ripper::Rip_Chain() {
    if (!this->Apply_Patch("Chain")) return false;
    bool sprite = false;
    QStack<qint64> offsets = this->graphicsOffsets->Get_Chain_Offsets();
    if (this->Does_Patch_Use_New_Tiles(offsets, sprite, 0)) return true;
    if (!this->Write_Tiles_And_Order_To_Working_File(offsets, sprite, 0)) return false;
    return this->Create_Patch();
}

bool Graphics_Ripper::Rip_Cloud_Block() {
    if (!this->Apply_Patch("Block Cloud")) return false;
    bool sprite = false;
    QStack<qint64> offsets = this->graphicsOffsets->Get_Cloud_Block_Offsets();
    if (this->Does_Patch_Use_New_Tiles(offsets, sprite, 0)) return true;
    if (!this->Write_Tiles_And_Order_To_Working_File(offsets, sprite, 0)) return false;
    return this->Create_Patch();
}

bool Graphics_Ripper::Rip_Coin() {
    if (!this->Apply_Patch("Coin")) return false;
    bool sprite = false;
    QStack<qint64> offsets = this->graphicsOffsets->Get_Coin_Offsets();
    if (this->Does_Patch_Use_New_Tiles(offsets, sprite, 0)) return true;
    if (!this->Write_Tiles_And_Order_To_Working_File(offsets, sprite, 0)) return false;
    return this->Create_Patch();
}

bool Graphics_Ripper::Rip_Coin_Icon() {
    if (!this->Apply_Patch("Coin Icon")) return false;
    if (!this->Write_Sprite_Tiles_To_Working_File(QByteArray::fromHex(QString("FF").toLatin1()))) return false;
    if (!this->Write_Background_Tiles_To_Working_File(QByteArray::fromHex(QString("2E").toLatin1()))) return false;
    return this->Create_Patch();
}

bool Graphics_Ripper::Rip_Coral() {
    if (!this->Apply_Patch("Coral")) return false;
    bool sprite = false;
    QStack<qint64> offsets = this->graphicsOffsets->Get_Coral_Offsets();
    if (this->Does_Patch_Use_New_Tiles(offsets, sprite, 0)) return true;
    if (!this->Write_Tiles_And_Order_To_Working_File(offsets, sprite, 0)) return false;
    return this->Create_Patch();
}

bool Graphics_Ripper::Rip_Flagpole() {
    if (!this->Apply_Patch("Flagpole")) return false;
    bool sprite = false;
    QStack<qint64> offsets = this->graphicsOffsets->Get_Flagpole_Offsets();
    if (this->Does_Patch_Use_New_Tiles(offsets, sprite, 0)) return true;
    if (!this->Write_Tiles_And_Order_To_Working_File(offsets, sprite, 0)) return false;
    return this->Create_Patch();
}

bool Graphics_Ripper::Rip_Font() {
    if (!this->Apply_Patch("Font")) return false;
    if (!this->Write_Background_Tiles_To_Working_File(QByteArray::fromHex(QString("000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F2021222328292BAF").toLatin1()))) return false;
    return this->Create_Patch();
}

bool Graphics_Ripper::Rip_Mushroom_Platform() {
    if (!this->Apply_Patch("Island Mushroom")) return false;
    bool sprite = false;
    QStack<qint64> offsets = this->graphicsOffsets->Get_Mushroom_Platform_Offsets();
    if (this->Does_Patch_Use_New_Tiles(offsets, sprite, 0)) return true;
    if (!this->Write_Tiles_And_Order_To_Working_File(offsets, sprite, 0)) return false;
    return this->Create_Patch();
}

bool Graphics_Ripper::Rip_Overworld_Block() {
    if (!this->Apply_Patch("Block Overworld")) return false;
    bool sprite = false;
    QStack<qint64> offsets = this->graphicsOffsets->Get_Overworld_Block_Offsets();
    if (this->Does_Patch_Use_New_Tiles(offsets, sprite, 0)) return true;
    if (!this->Write_Tiles_And_Order_To_Working_File(offsets, sprite, 0)) return false;
    return this->Create_Patch();
}

bool Graphics_Ripper::Rip_Pipe() {
    if (!this->Apply_Patch("Pipe")) return false;
    bool sprite = false;
    QStack<qint64> offsets = this->graphicsOffsets->Get_Pipe_Offsets();
    if (this->Does_Patch_Use_New_Tiles(offsets, sprite, 0)) return true;
    if (!this->Write_Tiles_And_Order_To_Working_File(offsets, sprite, 0)) return false;
    return this->Create_Patch();
}

bool Graphics_Ripper::Rip_Question_Block() {
    if (!this->Apply_Patch("Question Block")) return false;
    bool sprite = false;
    QStack<qint64> offsets = this->graphicsOffsets->Get_Question_Block_Offsets();
    if (this->Does_Patch_Use_New_Tiles(offsets, sprite, 0)) return true;
    if (!this->Write_Tiles_And_Order_To_Working_File(offsets, sprite, 0)) return false;
    if (!this->Write_Sprite_Tiles_To_Working_File(QByteArray::fromHex(QString("87").toLatin1()))) return false;
    return this->Create_Patch();
}

bool Graphics_Ripper::Rip_Rope() {
    if (!this->Apply_Patch("Rope")) return false;
    bool sprite = false;
    QStack<qint64> offsets = this->graphicsOffsets->Get_Rope_Offsets();
    if (this->Does_Patch_Use_New_Tiles(offsets, sprite, 0)) return true;
    if (!this->Write_Tiles_And_Order_To_Working_File(offsets, sprite, 0)) return false;
    return this->Create_Patch();
}

bool Graphics_Ripper::Rip_Selector_Icon() {
    if (!this->Apply_Patch("Selector Icon")) return false;
    if (!this->Write_Background_Tiles_To_Working_File(QByteArray::fromHex(QString("CE").toLatin1()))) return false;
    return this->Create_Patch();
}

bool Graphics_Ripper::Rip_Solid_Block() {
    if (!this->Apply_Patch("Solid Block")) return false;
    bool sprite = false;
    QStack<qint64> offsets = this->graphicsOffsets->Get_Solid_Block_Offsets();
    if (this->Does_Patch_Use_New_Tiles(offsets, sprite, 0)) return true;
    if (!this->Write_Tiles_And_Order_To_Working_File(offsets, sprite, 0)) return false;
    return this->Create_Patch();
}

bool Graphics_Ripper::Rip_Tree_Platform() {
    if (!this->Apply_Patch("Island Tree")) return false;
    bool sprite = false;
    QStack<qint64> offsets = this->graphicsOffsets->Get_Tree_Platform_Offsets();
    if (this->Does_Patch_Use_New_Tiles(offsets, sprite, 0)) return true;
    if (!this->Write_Tiles_And_Order_To_Working_File(offsets, sprite, 0)) return false;
    return this->Create_Patch();
}

bool Graphics_Ripper::Rip_Underwater_Block() {
    if (!this->Apply_Patch("Block Underwater")) return false;
    bool sprite = false;
    QStack<qint64> offsets = this->graphicsOffsets->Get_Underwater_Block_Offsets();
    if (this->Does_Patch_Use_New_Tiles(offsets, sprite, 0)) return true;
    if (!this->Write_Tiles_And_Order_To_Working_File(offsets, sprite, 0)) return false;
    return this->Create_Patch();
}

bool Graphics_Ripper::Rip_Vine() {
    if (!this->Apply_Patch("Vine")) return false;
    if (!this->Write_Sprite_Tiles_To_Working_File(QByteArray::fromHex(QString("E0E1E2").toLatin1()))) return false;
    return this->Create_Patch();
}

bool Graphics_Ripper::Rip_Water() {
    if (!this->Apply_Patch("Water")) return false;
    bool sprite = false;
    QStack<qint64> offsets = this->graphicsOffsets->Get_Water_Offsets();
    if (this->Does_Patch_Use_New_Tiles(offsets, sprite, 0)) return true;
    if (!this->Write_Tiles_And_Order_To_Working_File(offsets, sprite, 0)) return false;
    return this->Create_Patch();
}

bool Graphics_Ripper::Apply_Patch(const QString &sprite, QString suggestedName) {
    QDir dir(this->applicationLocation);
    dir.mkdir("Sprites");
    if (!dir.cd("Sprites")) { this->Close_Files(); return false; }
    dir.mkdir(sprite);
    QString patchName = suggestedName;
    if (patchName.isEmpty()) patchName = this->Get_Base_Name_From_Path(this->patchFileLocation);
    if (this->hexagon->Start_Creating_Patch(this->applicationLocation+"/Sprites/"+sprite+"/"+patchName+".hexp") != Hexagon_Error_Codes::OK) {
        this->Close_Files();
        return false;
    }
    if (this->outputFile) return true; //patch already applied
    if (!this->Scan_For_Palette_Allowed()) { this->Close_Files(); return false; }

    //Create the Patched file
    int lineNum = 0;
    QString outputLocation = this->applicationLocation+"/"+this->Get_Base_Name_From_Path(this->patchFileLocation)+".nes";
    if (this->hexagon->Apply_Hexagon_Patch(this->patchFileLocation, this->originalFileLocation, outputLocation, false, lineNum) != Hexagon_Error_Codes::OK) return false;
    this->outputFile = new QFile(outputLocation);
    if (!this->outputFile->open(QIODevice::ReadWrite)) { this->Close_Files(); return false; }

    //Open the original file and create a working copy
    if (!this->Open_Original_File()) { this->Close_Files(); return false; }
    return true;
}

bool Graphics_Ripper::Create_Patch() {
    if (this->hexagon->Finish_Creating_Patch()) return false;
    return this->Open_Original_File();
}

void Graphics_Ripper::Close_Files() {
    this->hexagon->Finish_Creating_Patch();
    if (this->outputFile) {
        this->outputFile->close();
        this->outputFile->remove();
    }
    delete this->outputFile;
    this->outputFile = nullptr;
    this->Close_Working_Files();
}

void Graphics_Ripper::Close_Working_Files() {
    if (this->originalFile) this->originalFile->close();
    delete this->originalFile;
    this->writtenSpriteTiles.clear();
    this->writtenBackgroundTiles.clear();
}

bool Graphics_Ripper::Does_Patch_Use_New_Tiles(qint64 offset, bool sprite, int tileOrderSize) {
    QStack<qint64> offsets;
    offsets.push(offset);
    return this->Does_Patch_Use_New_Tiles(offsets, sprite, tileOrderSize);
}

bool Graphics_Ripper::Does_Patch_Use_New_Tiles(QStack<qint64> offsets, bool sprite, int tileOrderSize) {
    if (this->palettesDisabled) return true;

    //Read the old tiles
    QSet<char> tiles;
    QByteArray oldTiles;
    QStack<qint64> oldOffsets = offsets;
    if (sprite) tiles.insert(static_cast<char>(0xFC));
    else tiles.insert(static_cast<char>(0x24));
    if (tileOrderSize == 0) {
        if (sprite) tileOrderSize = 6;
        else tileOrderSize = 4;
    }
    while (!oldOffsets.isEmpty()) {
        qint64 offset = oldOffsets.pop();
        assert(this->originalFile->seek(offset));
        QByteArray oldTiles = this->originalFile->read(tileOrderSize);
        if (!this->usedOffsets->contains(offset)) this->usedOffsets->insert(offset, new QByteArray(oldTiles));
        assert(oldTiles.size() == tileOrderSize);
        for (char c : oldTiles) tiles.insert(c);
    }

    //Compare against the new tiles
    while (!offsets.isEmpty()) {
        qint64 offset = offsets.pop();
        assert(this->outputFile->seek(offset));
        QByteArray newTiles = this->outputFile->read(tileOrderSize);
        assert(newTiles.size() == tileOrderSize);
        for (char c : newTiles) {
            if (!tiles.contains(c)) return true;
        }
    }
    return false;
}

QString Graphics_Ripper::Get_Base_Name_From_Path(const QString &path) {
    QString baseName;
    QStringList strings = QFileInfo(path).fileName().split('.');
    strings.removeLast();
    for (int i = 0; i < strings.size()-1; ++i) {
        baseName += strings.at(i) + ".";
    }
    baseName += strings.last();
    return baseName;
}

bool Graphics_Ripper::Is_Tile_Blank(char tileID, bool sprite) {
    QByteArray graphicsBytes;
    if (sprite) assert(this->Read_Graphics_Bytes_From_Sprite_Tile_ID(tileID, graphicsBytes));
    else assert(this->Read_Graphics_Bytes_From_Background_Tile_ID(tileID, graphicsBytes));
    for (int i = 0; i < graphicsBytes.size(); ++i) {
        if (graphicsBytes.at(i) != static_cast<char>(0x00)) return false;
    }
    return true;
}

bool Graphics_Ripper::Read_Graphics_Bytes_From_Sprite_Tile_ID(char tileID, QByteArray &graphicsBytes) {
    unsigned char c = static_cast<unsigned char>(tileID);
    qint64 spriteGraphicsOffset = 0x8010+(c*0x10); //get the graphics offset for the tile
    if (!this->outputFile->seek(spriteGraphicsOffset)) return false;
    graphicsBytes = this->outputFile->read(16);
    return graphicsBytes.size() == 16;
}

bool Graphics_Ripper::Read_Graphics_Bytes_From_Background_Tile_ID(char tileID, QByteArray &graphicsBytes) {
    unsigned char c = static_cast<unsigned char>(tileID);
    qint64 spriteGraphicsOffset = 0x9010+(c*0x10); //get the graphics offset for the tile
    if (!this->outputFile->seek(spriteGraphicsOffset)) return false;
    graphicsBytes = this->outputFile->read(16);
    return graphicsBytes.size() == 16;
}

bool Graphics_Ripper::Open_Original_File() {
    //Open the original file
    if (!this->originalFile && !this->originalFileLocation.isEmpty()) {
        this->originalFile = new QFile(originalFileLocation);
        if (!this->originalFile->open(QIODevice::ReadWrite)) { this->Close_Working_Files(); return false; }
    }
    return true;
}

bool Graphics_Ripper::Scan_For_Palette_Allowed() {
    QFile patchFile(this->patchFileLocation);
    if (!patchFile.open(QIODevice::ReadOnly)) return false;
    QTextStream stream(&patchFile);
    QString line = stream.readLine();
    bool done = false;
    while (!stream.atEnd() && !done) {
        if (line.startsWith(Patch_Strings::STRING_OFFSET)) {
            this->palettesDisabled = false;
            done = true;
        } else if (line.startsWith(Fix_Strings::STRING_ALLOW_PALETTES)) {
            this->palettesDisabled = true;
            done = true;
        } else if (line.startsWith(Fix_Strings::STRING_ALLOW_ONLY_COIN_PALETTES)) {
            this->palettesDisabled = true;
            done = true;
        }
    }
    patchFile.close();
    return true;
}

bool Graphics_Ripper::Write_Background_Tiles_To_Working_File(const QByteArray &tiles) {
    return this->Write_Tiles_To_Working_File(tiles, false);
}

bool Graphics_Ripper::Write_Sprite_Tiles_To_Working_File(const QByteArray &tiles) {
    return this->Write_Tiles_To_Working_File(tiles, true);
}

bool Graphics_Ripper::Write_Data_To_Working_File(qint64 offset, int amount) {
    if (!this->outputFile->seek(offset)) return false;
    QByteArray bytes = this->outputFile->read(amount);
    if (bytes.size() != amount) return false;
    return this->hexagon->Write_Next_Patch(offset, bytes) == Hexagon_Error_Codes::OK;
}

bool Graphics_Ripper::Write_Tiles_And_Order_To_Working_File(qint64 offset, bool sprite, int tileOrderSize) {
    QStack<qint64> offsets;
    offsets.push(offset);
    return this->Write_Tiles_And_Order_To_Working_File(offsets, sprite, tileOrderSize);
}

bool Graphics_Ripper::Write_Tiles_And_Order_To_Working_File(QStack<qint64> offsets, bool sprite, int tileOrderSize) {
    if (tileOrderSize == 0) {
        if (sprite) tileOrderSize = 6;
        else tileOrderSize = 4;
    }
    while (!offsets.isEmpty()) {
        qint64 offset = offsets.pop();
        //Read the tile order
        if (!this->outputFile->seek(offset)) return false;
        QByteArray tileOrder = this->outputFile->read(tileOrderSize);
        if (tileOrder.size() != tileOrderSize) return false;

        //Update blank tiles
        for (int i = 0; i < tileOrder.size(); ++i) {
            if (this->Is_Tile_Blank(tileOrder.at(i), sprite)) {
                if (sprite) tileOrder.data()[i] = static_cast<char>(0xFC);
                else tileOrder.data()[i] = static_cast<char>(0x24);
            }
        }

        //Write the tile order
        if (this->hexagon->Write_Next_Patch(offset, tileOrder) != Hexagon_Error_Codes::OK) return false;

        //Write the tiles themselves
        if (sprite) {
            if (!this->Write_Sprite_Tiles_To_Working_File(tileOrder)) return false;
        } else {
            if (!this->Write_Background_Tiles_To_Working_File(tileOrder)) return false;
        }
    }
    return true;
}

bool Graphics_Ripper::Write_Tiles_To_Working_File(const QByteArray &tiles, bool sprite) {
    for (char tile : tiles) {
        //Don't write the tile if it has already been written
        if (sprite) {
            if (this->writtenSpriteTiles.contains(tile)) continue;
        } else {
            if (this->writtenBackgroundTiles.contains(tile)) continue;
        }
        QByteArray graphicsBytes;
        qint64 offset = 0;
        if (sprite) {
            this->Read_Graphics_Bytes_From_Sprite_Tile_ID(tile, graphicsBytes);
            offset = 0x8010+(static_cast<unsigned char>(tile)*0x10);
        } else {
            this->Read_Graphics_Bytes_From_Background_Tile_ID(tile, graphicsBytes);
            offset = 0x9010+(static_cast<unsigned char>(tile)*0x10);
        }
        if (this->hexagon->Write_Next_Patch(offset, graphicsBytes) != Hexagon_Error_Codes::OK) return false;
        if (sprite) this->writtenSpriteTiles.insert(tile);
        else this->writtenBackgroundTiles.insert(tile);
    }
    return true;
}
