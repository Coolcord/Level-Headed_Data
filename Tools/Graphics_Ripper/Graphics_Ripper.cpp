#include "Graphics_Ripper.h"
#include <assert.h>
#include <QDebug>
#include <QDir>
#include <QFileInfo>

Graphics_Ripper::Graphics_Ripper(const QString &applicationLocation, const QString &originalFileLocation, const QString &patchFileLocation, Hexagon_Interface *hexagon) {
    assert(hexagon);
    this->applicationLocation = applicationLocation;
    this->originalFileLocation = originalFileLocation;
    this->patchFileLocation = patchFileLocation;
    this->outputFile = nullptr;
    this->originalFile = nullptr;
    this->workingFile = nullptr;
    this->hexagon = hexagon;
}

Graphics_Ripper::~Graphics_Ripper() {
    this->Close_Files();
}

bool Graphics_Ripper::Rip_All() {
    if (!this->Rip_Blooper()) return false;
    if (!this->Rip_Bowser()) return false;
    if (!this->Rip_Bullet_Bill()) return false;
    if (!this->Rip_Buzzy_Beetle()) return false;
    if (!this->Rip_Cheep_Cheep()) return false;
    if (!this->Rip_Goomba()) return false;
    if (!this->Rip_Hammer_Bro()) return false;
    if (!this->Rip_Koopa()) return false;
    if (!this->Rip_Lakitu()) return false;
    if (!this->Rip_Jump_Spring()) return false;
    if (!this->Rip_Mario()) return false;
    if (!this->Rip_Peach()) return false;
    if (!this->Rip_Piranha_Plant()) return false;
    if (!this->Rip_Podoboo()) return false;
    if (!this->Rip_Spiny()) return false;
    if (!this->Rip_Spiny_Egg()) return false;
    if (!this->Rip_Toad()) return false;
    if (!this->Rip_Axe()) return false;
    if (!this->Rip_Brick_Block()) return false;
    if (!this->Rip_Bridge()) return false;
    if (!this->Rip_Bowser_Bridge()) return false;
    if (!this->Rip_Bullet_Bill_Cannon()) return false;
    if (!this->Rip_Castle_Block()) return false;
    if (!this->Rip_Chain()) return false;
    if (!this->Rip_Cloud_Block()) return false;
    if (!this->Rip_Coin()) return false;
    if (!this->Rip_Coral()) return false;
    if (!this->Rip_Fire_Flower()) return false;
    if (!this->Rip_Flagpole()) return false;
    if (!this->Rip_Mushroom_Powerup()) return false;
    if (!this->Rip_Mushroom_Platform()) return false;
    if (!this->Rip_Overworld_Block()) return false;
    if (!this->Rip_Pipe()) return false;
    if (!this->Rip_Question_Block()) return false;
    if (!this->Rip_Rope()) return false;
    if (!this->Rip_Solid_Block()) return false;
    if (!this->Rip_Font()) return false;
    if (!this->Rip_Tree_Platform()) return false;
    if (!this->Rip_Underwater_Block()) return false;
    if (!this->Rip_Water()) return false;
    return true;
}

bool Graphics_Ripper::Rip_Air_Bubble() {
    if (!this->Apply_Patch()) return false;
    if (!this->Write_Sprite_Tiles_To_Working_File(QByteArray::fromHex(QString("74").toLatin1()))) return false;
    return this->Create_Patch("Fireball");
}

bool Graphics_Ripper::Rip_Blooper() {
    if (!this->Apply_Patch()) return false;


    //TODO: WRITE THIS!!!
    return this->Create_Patch("Blooper");
}

bool Graphics_Ripper::Rip_Bowser() {
    if (!this->Apply_Patch()) return false;


    //TODO: WRITE THIS!!!
    return this->Create_Patch("Bowser");
}

bool Graphics_Ripper::Rip_Bullet_Bill() {
    if (!this->Apply_Patch()) return false;


    //TODO: WRITE THIS!!!
    return this->Create_Patch("Bullet_Bill");
}

bool Graphics_Ripper::Rip_Buzzy_Beetle() {
    if (!this->Apply_Patch()) return false;


    //TODO: WRITE THIS!!!
    return this->Create_Patch("Buzzy_Beetle");
}

bool Graphics_Ripper::Rip_Castle_Flag() {
    if (!this->Apply_Patch()) return false;


    //TODO: WRITE THIS!!!
    return this->Create_Patch("Castle_Flag");
}

bool Graphics_Ripper::Rip_Cheep_Cheep() {
    if (!this->Apply_Patch()) return false;


    //TODO: WRITE THIS!!!
    return this->Create_Patch("Cheep_Cheep");
}

bool Graphics_Ripper::Rip_Coin_Animation() {
    if (!this->Apply_Patch()) return false;


    //TODO: WRITE THIS!!!
    return this->Create_Patch("Coin_Animation");
}

bool Graphics_Ripper::Rip_Explosion() {
    if (!this->Apply_Patch()) return false;
    if (!this->Write_Sprite_Tiles_To_Working_File(QByteArray::fromHex(QString("666768").toLatin1()))) return false;
    return this->Create_Patch("Explosion");
}

bool Graphics_Ripper::Rip_Fireball() {
    if (!this->Apply_Patch()) return false;
    if (!this->Write_Sprite_Tiles_To_Working_File(QByteArray::fromHex(QString("6465").toLatin1()))) return false;
    return this->Create_Patch("Fireball");
}

bool Graphics_Ripper::Rip_Flagpole_Flag() {
    if (!this->Apply_Patch()) return false;


    //TODO: WRITE THIS!!!
    return this->Create_Patch("Flagpole_Flag");
}

bool Graphics_Ripper::Rip_Goomba() {
    if (!this->Apply_Patch()) return false;


    //TODO: WRITE THIS!!!
    return this->Create_Patch("Goomba");
}

bool Graphics_Ripper::Rip_Hammer_Bro() {
    if (!this->Apply_Patch()) return false;


    //TODO: WRITE THIS!!!
    return this->Create_Patch("Hammer_Bro");
}

bool Graphics_Ripper::Rip_Jump_Spring() {
    if (!this->Apply_Patch()) return false;


    //TODO: WRITE THIS!!!
    return this->Create_Patch("Jump_Spring");
}

bool Graphics_Ripper::Rip_Koopa() {
    if (!this->Apply_Patch()) return false;


    //TODO: WRITE THIS!!!
    return this->Create_Patch("Koopa");
}

bool Graphics_Ripper::Rip_Lakitu() {
    if (!this->Apply_Patch()) return false;


    //TODO: WRITE THIS!!!
    return this->Create_Patch("Lakitu");
}

bool Graphics_Ripper::Rip_Lift() {
    if (!this->Apply_Patch()) return false;
    if (!this->Write_Sprite_Tiles_To_Working_File(QByteArray::fromHex(QString("5B").toLatin1()))) return false;
    return this->Create_Patch("Lift");
}

bool Graphics_Ripper::Rip_Mario() {
    if (!this->Apply_Patch()) return false;


    //TODO: WRITE THIS!!!
    return this->Create_Patch("Mario");
}

bool Graphics_Ripper::Rip_One_Up_Font() {
    if (!this->Apply_Patch()) return false;
    if (!this->Write_Sprite_Tiles_To_Working_File(QByteArray::fromHex(QString("FDFE").toLatin1()))) return false;
    return this->Create_Patch("Score_Font");
}

bool Graphics_Ripper::Rip_Peach() {
    if (!this->Apply_Patch()) return false;


    //TODO: WRITE THIS!!!
    return this->Create_Patch("Peach");
}

bool Graphics_Ripper::Rip_Piranha_Plant() {
    if (!this->Apply_Patch()) return false;


    //TODO: WRITE THIS!!!
    return this->Create_Patch("Piranha_Plant");
}

bool Graphics_Ripper::Rip_Podoboo() {
    if (!this->Apply_Patch()) return false;


    //TODO: WRITE THIS!!!
    return this->Create_Patch("Podoboo");
}

bool Graphics_Ripper::Rip_Score_Font() {
    if (!this->Apply_Patch()) return false;
    if (!this->Write_Sprite_Tiles_To_Working_File(QByteArray::fromHex(QString("50F6F7F8F9FAFB").toLatin1()))) return false;
    return this->Create_Patch("Score_Font");
}

bool Graphics_Ripper::Rip_Sky_Lift() {
    if (!this->Apply_Patch()) return false;
    if (!this->Write_Sprite_Tiles_To_Working_File(QByteArray::fromHex(QString("75").toLatin1()))) return false;
    return this->Create_Patch("Sky_Lift");
}

bool Graphics_Ripper::Rip_Spiny() {
    if (!this->Apply_Patch()) return false;


    //TODO: WRITE THIS!!!
    return this->Create_Patch("Spiny");
}

bool Graphics_Ripper::Rip_Spiny_Egg() {
    if (!this->Apply_Patch()) return false;


    //TODO: WRITE THIS!!!
    return this->Create_Patch("Spiny_Egg");
}

bool Graphics_Ripper::Rip_Toad() {
    if (!this->Apply_Patch()) return false;


    //TODO: WRITE THIS!!!
    return this->Create_Patch("Toad");
}

bool Graphics_Ripper::Rip_Axe() {
    if (!this->Apply_Patch()) return false;


    //TODO: WRITE THIS!!!
    return this->Create_Patch("Axe");
}

bool Graphics_Ripper::Rip_Brick_Block() {
    if (!this->Apply_Patch()) return false;


    //TODO: WRITE THIS!!!
    return this->Create_Patch("Brick_Block");
}

bool Graphics_Ripper::Rip_Bridge() {
    if (!this->Apply_Patch()) return false;


    //TODO: WRITE THIS!!!
    return this->Create_Patch("Bridge");
}

bool Graphics_Ripper::Rip_Bowser_Bridge() {
    if (!this->Apply_Patch()) return false;


    //TODO: WRITE THIS!!!
    return this->Create_Patch("Bowser_Bridge");
}

bool Graphics_Ripper::Rip_Bullet_Bill_Cannon() {
    if (!this->Apply_Patch()) return false;


    //TODO: WRITE THIS!!!
    return this->Create_Patch("Bullet_Bill_Cannon");
}

bool Graphics_Ripper::Rip_Castle_Block() {
    if (!this->Apply_Patch()) return false;


    //TODO: WRITE THIS!!!
    return this->Create_Patch("Castle_Block");
}

bool Graphics_Ripper::Rip_Chain() {
    if (!this->Apply_Patch()) return false;


    //TODO: WRITE THIS!!!
    return this->Create_Patch("Chain");
}

bool Graphics_Ripper::Rip_Cloud_Block() {
    if (!this->Apply_Patch()) return false;


    //TODO: WRITE THIS!!!
    return this->Create_Patch("Cloud_Block");
}

bool Graphics_Ripper::Rip_Coin() {
    if (!this->Apply_Patch()) return false;


    //TODO: WRITE THIS!!!
    return this->Create_Patch("Coin");
}

bool Graphics_Ripper::Rip_Coral() {
    if (!this->Apply_Patch()) return false;


    //TODO: WRITE THIS!!!
    return this->Create_Patch("Coral");
}

bool Graphics_Ripper::Rip_Fire_Flower() {
    if (!this->Apply_Patch()) return false;


    //TODO: WRITE THIS!!!
    return this->Create_Patch("Fire_Flower");
}

bool Graphics_Ripper::Rip_Flagpole() {
    if (!this->Apply_Patch()) return false;


    //TODO: WRITE THIS!!!
    return this->Create_Patch("Flagpole");
}

bool Graphics_Ripper::Rip_Font() {
    if (!this->Apply_Patch()) return false;


    //TODO: WRITE THIS!!!
    return this->Create_Patch("Font");
}

bool Graphics_Ripper::Rip_Mushroom_Powerup() {
    if (!this->Apply_Patch()) return false;


    //TODO: WRITE THIS!!!
    return this->Create_Patch("Mushroom_Powerup");
}

bool Graphics_Ripper::Rip_Mushroom_Platform() {
    if (!this->Apply_Patch()) return false;


    //TODO: WRITE THIS!!!
    return this->Create_Patch("Mushroom_Platform");
}

bool Graphics_Ripper::Rip_Overworld_Block() {
    if (!this->Apply_Patch()) return false;


    //TODO: WRITE THIS!!!
    return this->Create_Patch("Overworld_Block");
}

bool Graphics_Ripper::Rip_Pipe() {
    if (!this->Apply_Patch()) return false;


    //TODO: WRITE THIS!!!
    return this->Create_Patch("Pipe");
}

bool Graphics_Ripper::Rip_Question_Block() {
    if (!this->Apply_Patch()) return false;


    //TODO: WRITE THIS!!!
    return this->Create_Patch("Question_Block");
}

bool Graphics_Ripper::Rip_Rope() {
    if (!this->Apply_Patch()) return false;


    //TODO: WRITE THIS!!!
    return this->Create_Patch("Rope");
}

bool Graphics_Ripper::Rip_Solid_Block() {
    if (!this->Apply_Patch()) return false;


    //TODO: WRITE THIS!!!
    return this->Create_Patch("Solid_Block");
}

bool Graphics_Ripper::Rip_Tree_Platform() {
    if (!this->Apply_Patch()) return false;


    //TODO: WRITE THIS!!!
    return this->Create_Patch("Tree_Platform");
}

bool Graphics_Ripper::Rip_Underwater_Block() {
    if (!this->Apply_Patch()) return false;


    //TODO: WRITE THIS!!!
    return this->Create_Patch("Underwater_Block");
}

bool Graphics_Ripper::Rip_Water() {
    if (!this->Apply_Patch()) return false;


    //TODO: WRITE THIS!!!
    return this->Create_Patch("Water");
}

bool Graphics_Ripper::Apply_Patch() {
    if (this->outputFile) return true; //patch already applied

    //Create the Patched file
    int lineNum = 0;
    QString outputLocation = this->applicationLocation+"/"+QFileInfo(this->patchFileLocation).baseName()+".nes";
    if (this->hexagon->Apply_Hexagon_Patch(this->patchFileLocation, this->originalFileLocation, outputLocation, false, lineNum) != Hexagon_Error_Codes::OK) return false;
    this->outputFile = new QFile(outputLocation);
    if (!this->outputFile->open(QIODevice::ReadWrite)) return false;

    //Open the original file and create a working copy
    if (!this->Recreate_Working_File()) { this->Close_Files(); return false; }

    return this->Make_Directory_Structure(); //create all of the necessary folders
}

bool Graphics_Ripper::Create_Patch(const QString &sprite) {
    if (this->hexagon->Create_Hexagon_Patch(this->originalFileLocation, this->workingFileLocation, this->applicationLocation+"/Sprites/"+sprite+"/"+QFileInfo(this->patchFileLocation).baseName()+".hexp", 5, false, false) != Hexagon_Error_Codes::OK) return false;
    return this->Recreate_Working_File();
}

void Graphics_Ripper::Close_Files() {
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
    if (this->workingFile) {
        this->workingFile->close();
        this->workingFile->remove();
    }
    delete this->originalFile;
    delete this->workingFile;
    this->originalFile = nullptr;
    this->workingFile = nullptr;
}

bool Graphics_Ripper::Make_Directory_Structure() {
    QDir dir(this->applicationLocation);
    dir.mkdir("Sprites");
    if (!dir.cd("Sprites")) return false;
    dir.mkdir("Air_Bubble");
    dir.mkdir("Blooper");
    dir.mkdir("Bowser");
    dir.mkdir("Bullet_Bill");
    dir.mkdir("Buzzy_Beetle");
    dir.mkdir("Castle_Flag");
    dir.mkdir("Cheep_Cheep");
    dir.mkdir("Coin_Animation");
    dir.mkdir("Explosion");
    dir.mkdir("Fireball");
    dir.mkdir("Flagpole_Flag");
    dir.mkdir("Goomba");
    dir.mkdir("Hammer_Bro");
    dir.mkdir("Jump_Spring");
    dir.mkdir("Koopa");
    dir.mkdir("Lakitu");
    dir.mkdir("Lift");
    dir.mkdir("Mario");
    dir.mkdir("One_Up_Font");
    dir.mkdir("Peach");
    dir.mkdir("Piranha_Plant");
    dir.mkdir("Podoboo");
    dir.mkdir("Score_Font");
    dir.mkdir("Sky_Lift");
    dir.mkdir("Spiny");
    dir.mkdir("Spiny_Egg");
    dir.mkdir("Toad");
    dir.mkdir("Axe");
    dir.mkdir("Brick_Block");
    dir.mkdir("Bridge");
    dir.mkdir("Bowser_Bridge");
    dir.mkdir("Bullet_Bill_Cannon");
    dir.mkdir("Castle_Block");
    dir.mkdir("Chain");
    dir.mkdir("Cloud_Block");
    dir.mkdir("Coin");
    dir.mkdir("Coral");
    dir.mkdir("Fire_Flower");
    dir.mkdir("Flagpole");
    dir.mkdir("Font");
    dir.mkdir("Mushroom_Powerup");
    dir.mkdir("Mushroom_Platform");
    dir.mkdir("Overworld_Block");
    dir.mkdir("Pipe");
    dir.mkdir("Question_Block");
    dir.mkdir("Rope");
    dir.mkdir("Solid_Block");
    dir.mkdir("Tree_Platform");
    dir.mkdir("Underwater_Block");
    dir.mkdir("Water");
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

bool Graphics_Ripper::Recreate_Working_File() {
    //Open the original file
    if (!this->originalFile) {
        this->originalFile = new QFile(originalFileLocation);
        if (!this->originalFile->open(QIODevice::ReadWrite)) { this->Close_Working_Files(); return false; }
    }

    //Delete the old working file if it exists
    if (this->workingFile) {
        this->workingFile->close();
        this->workingFile->remove();
        delete this->workingFile;
        this->workingFile = nullptr;
    }

    //Create a copy of the original file to work with
    this->workingFileLocation = this->applicationLocation+"/"+QFileInfo(this->patchFileLocation).baseName()+"_working.nes";
    if (QFileInfo(this->workingFileLocation).exists()) QFile(this->workingFileLocation).remove();
    this->workingFile = new QFile(this->workingFileLocation);
    if (!this->workingFile->open(QIODevice::ReadWrite)) { this->Close_Working_Files(); return false; }
    if (!this->originalFile->reset()) return false;
    QByteArray buffer = this->originalFile->readAll();
    if (!this->originalFile->reset()) return false;
    if (this->workingFile->write(buffer) != buffer.size()) return false;
    if (!this->workingFile->reset()) return false;
    return true;
}

bool Graphics_Ripper::Write_Background_Tiles_To_Working_File(const QByteArray &tiles) {
    return this->Write_Tiles_To_Working_File(tiles, false);
}

bool Graphics_Ripper::Write_Sprite_Tiles_To_Working_File(const QByteArray &tiles) {
    return this->Write_Tiles_To_Working_File(tiles, true);
}

bool Graphics_Ripper::Write_Tiles_To_Working_File(const QByteArray &tiles, bool sprite) {
    for (int i = 0; i < tiles.size(); ++i) {
        QByteArray graphicsBytes;
        qint64 offset = 0;
        if (sprite) {
            this->Read_Graphics_Bytes_From_Sprite_Tile_ID(tiles.at(i), graphicsBytes);
            offset = 0x8010+(tiles.at(i)*0x10);
        } else {
            this->Read_Graphics_Bytes_From_Background_Tile_ID(tiles.at(i), graphicsBytes);
            offset = 0x9010+(tiles.at(i)*0x10);
        }
        if (!this->workingFile->seek(offset)) return false;
        if (this->workingFile->write(graphicsBytes) != graphicsBytes.size()) return false;
    }
    return true;
}
