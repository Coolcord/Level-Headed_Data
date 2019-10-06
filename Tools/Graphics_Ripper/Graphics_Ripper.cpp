#include "Graphics_Ripper.h"
#include "../../../Level-Headed/SMB1/Common_SMB1_Files/Fix_Strings.h"
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
    this->palettesDisabled = false;
    this->outputFile = nullptr;
    this->originalFile = nullptr;
    this->workingFile = nullptr;
    this->baseFile = nullptr;
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
    return this->Create_Patch("Bullet Bill");
}

bool Graphics_Ripper::Rip_Buzzy_Beetle() {
    if (!this->Apply_Patch()) return false;
    bool sprite = true;
    QStack<qint64> offsets; offsets.push(0x674E); offsets.push(0x6754); offsets.push(0x67C0); offsets.push(0x67C6); offsets.push(0x67CC); offsets.push(0x67D2);
    if (this->Does_Patch_Use_New_Tiles(QByteArray::fromHex(QString("AAABACADAEAFB0B1F4F5").toLatin1()), offsets, sprite)) return true; //nothing to do
    if (!this->Write_Tiles_And_Order_To_Working_File(offsets, sprite)) return false;
    return this->Create_Patch("Buzzy Beetle");
}

bool Graphics_Ripper::Rip_Castle_Flag() {
    if (!this->Apply_Patch()) return false;


    //TODO: WRITE THIS!!!
    return this->Create_Patch("Castle Flag");
}

bool Graphics_Ripper::Rip_Cheep_Cheep() {
    if (!this->Apply_Patch()) return false;


    //TODO: WRITE THIS!!!
    return this->Create_Patch("Cheep Cheep");
}

bool Graphics_Ripper::Rip_Coin_Animation() {
    if (!this->Apply_Patch()) return false;


    //TODO: WRITE THIS!!!
    return this->Create_Patch("Coin Animation");
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
    return this->Create_Patch("Flagpole Flag");
}

bool Graphics_Ripper::Rip_Goomba() {
    if (!this->Apply_Patch()) return false;


    //TODO: WRITE THIS!!!
    return this->Create_Patch("Goomba");
}

bool Graphics_Ripper::Rip_Hammer_Bro() {
    if (!this->Apply_Patch()) return false;


    //TODO: WRITE THIS!!!
    return this->Create_Patch("Hammer Bro");
}

bool Graphics_Ripper::Rip_Jump_Spring() {
    if (!this->Apply_Patch()) return false;


    //TODO: WRITE THIS!!!
    return this->Create_Patch("Jump Spring");
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
    return this->Create_Patch("Font One Up");
}

bool Graphics_Ripper::Rip_Peach() {
    if (!this->Apply_Patch()) return false;


    //TODO: WRITE THIS!!!
    return this->Create_Patch("Peach");
}

bool Graphics_Ripper::Rip_Piranha_Plant() {
    if (!this->Apply_Patch()) return false;


    //TODO: WRITE THIS!!!
    return this->Create_Patch("Piranha Plant");
}

bool Graphics_Ripper::Rip_Podoboo() {
    if (!this->Apply_Patch()) return false;


    //TODO: WRITE THIS!!!
    return this->Create_Patch("Podoboo");
}

bool Graphics_Ripper::Rip_Score_Font() {
    if (!this->Apply_Patch()) return false;
    if (!this->Write_Sprite_Tiles_To_Working_File(QByteArray::fromHex(QString("50F6F7F8F9FAFB").toLatin1()))) return false;
    return this->Create_Patch("Font Score");
}

bool Graphics_Ripper::Rip_Sky_Lift() {
    if (!this->Apply_Patch()) return false;
    if (!this->Write_Sprite_Tiles_To_Working_File(QByteArray::fromHex(QString("75").toLatin1()))) return false;
    return this->Create_Patch("Lift Sky");
}

bool Graphics_Ripper::Rip_Spiny() {
    if (!this->Apply_Patch()) return false;


    //TODO: WRITE THIS!!!
    return this->Create_Patch("Spiny");
}

bool Graphics_Ripper::Rip_Spiny_Egg() {
    if (!this->Apply_Patch()) return false;


    //TODO: WRITE THIS!!!
    return this->Create_Patch("Spiny Egg");
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
    return this->Create_Patch("Brick Block");
}

bool Graphics_Ripper::Rip_Bridge() {
    if (!this->Apply_Patch()) return false;


    //TODO: WRITE THIS!!!
    return this->Create_Patch("Bridge");
}

bool Graphics_Ripper::Rip_Bowser_Bridge() {
    if (!this->Apply_Patch()) return false;


    //TODO: WRITE THIS!!!
    return this->Create_Patch("Bowser Bridge");
}

bool Graphics_Ripper::Rip_Bullet_Bill_Cannon() {
    if (!this->Apply_Patch()) return false;


    //TODO: WRITE THIS!!!
    return this->Create_Patch("Bullet Bill Cannon");
}

bool Graphics_Ripper::Rip_Castle_Block() {
    if (!this->Apply_Patch()) return false;


    //TODO: WRITE THIS!!!
    return this->Create_Patch("Block Castle");
}

bool Graphics_Ripper::Rip_Chain() {
    if (!this->Apply_Patch()) return false;


    //TODO: WRITE THIS!!!
    return this->Create_Patch("Chain");
}

bool Graphics_Ripper::Rip_Cloud_Block() {
    if (!this->Apply_Patch()) return false;


    //TODO: WRITE THIS!!!
    return this->Create_Patch("Block Cloud");
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
    return this->Create_Patch("Powerup Fire Flower");
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
    return this->Create_Patch("Powerup Mushroom");
}

bool Graphics_Ripper::Rip_Mushroom_Platform() {
    if (!this->Apply_Patch()) return false;


    //TODO: WRITE THIS!!!
    return this->Create_Patch("Island Mushroom");
}

bool Graphics_Ripper::Rip_Overworld_Block() {
    if (!this->Apply_Patch()) return false;


    //TODO: WRITE THIS!!!
    return this->Create_Patch("Block Overworld");
}

bool Graphics_Ripper::Rip_Pipe() {
    if (!this->Apply_Patch()) return false;


    //TODO: WRITE THIS!!!
    return this->Create_Patch("Pipe");
}

bool Graphics_Ripper::Rip_Question_Block() {
    if (!this->Apply_Patch()) return false;


    //TODO: WRITE THIS!!!
    return this->Create_Patch("Question Block");
}

bool Graphics_Ripper::Rip_Rope() {
    if (!this->Apply_Patch()) return false;


    //TODO: WRITE THIS!!!
    return this->Create_Patch("Rope");
}

bool Graphics_Ripper::Rip_Solid_Block() {
    if (!this->Apply_Patch()) return false;


    //TODO: WRITE THIS!!!
    return this->Create_Patch("Solid Block");
}

bool Graphics_Ripper::Rip_Tree_Platform() {
    if (!this->Apply_Patch()) return false;


    //TODO: WRITE THIS!!!
    return this->Create_Patch("Island Tree");
}

bool Graphics_Ripper::Rip_Underwater_Block() {
    if (!this->Apply_Patch()) return false;


    //TODO: WRITE THIS!!!
    return this->Create_Patch("Block Underwater");
}

bool Graphics_Ripper::Rip_Water() {
    if (!this->Apply_Patch()) return false;


    //TODO: WRITE THIS!!!
    return this->Create_Patch("Water");
}

bool Graphics_Ripper::Apply_Patch() {
    if (this->outputFile) return true; //patch already applied
    if (!this->Scan_For_Palette_Allowed()) return false;

    //Create the Patched file
    int lineNum = 0;
    QString outputLocation = this->applicationLocation+"/"+this->Get_Base_Name_From_Path(this->patchFileLocation)+".nes";
    if (this->hexagon->Apply_Hexagon_Patch(this->patchFileLocation, this->originalFileLocation, outputLocation, false, lineNum) != Hexagon_Error_Codes::OK) return false;
    this->outputFile = new QFile(outputLocation);
    if (!this->outputFile->open(QIODevice::ReadWrite)) return false;

    //Open the original file and create a working copy
    if (!this->Recreate_Working_File()) { this->Close_Files(); return false; }
    return true;
}

bool Graphics_Ripper::Create_Patch(const QString &sprite) {
    QDir dir(this->applicationLocation);
    dir.mkdir("Sprites");
    if (!dir.cd("Sprites")) return false;
    dir.mkdir(sprite);
    if (this->hexagon->Create_Hexagon_Patch(this->baseFileLocation, this->workingFileLocation, this->applicationLocation+"/Sprites/"+sprite+"/"+this->Get_Base_Name_From_Path(this->patchFileLocation)+".hexp", 5, false, false) != Hexagon_Error_Codes::OK) return false;
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
    if (this->baseFile) {
        this->baseFile->close();
        this->baseFile->remove();
    }
    delete this->originalFile;
    delete this->workingFile;
    delete this->baseFile;
    this->originalFile = nullptr;
    this->workingFile = nullptr;
    this->baseFile = nullptr;
    this->writtenSpriteTiles.clear();
    this->writtenBackgroundTiles.clear();
}

bool Graphics_Ripper::Does_Patch_Use_New_Tiles(const QByteArray &oldTiles, qint64 offset, bool sprite) {
    QStack<qint64> offsets;
    offsets.push(offset);
    return this->Does_Patch_Use_New_Tiles(oldTiles, offsets, sprite);
}

bool Graphics_Ripper::Does_Patch_Use_New_Tiles(const QByteArray &oldTiles, QStack<qint64> offsets, bool sprite) {
    if (this->palettesDisabled) return true;
    QSet<char> tiles;
    if (sprite) tiles.insert(static_cast<char>(0xFC));
    else tiles.insert(static_cast<char>(0x24));
    for (char c : oldTiles) tiles.insert(c);
    while (!offsets.isEmpty()) {
        qint64 offset = offsets.pop();
        assert(this->outputFile->seek(offset));
        QByteArray newTiles = this->outputFile->read(6);
        assert(newTiles.size() == 6);
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

bool Graphics_Ripper::Recreate_Working_File() {
    //Open the original file
    if (!this->originalFile) {
        this->originalFile = new QFile(originalFileLocation);
        if (!this->originalFile->open(QIODevice::ReadWrite)) { this->Close_Working_Files(); return false; }
    }

    //Create the base file if necessary
    QByteArray buffer(static_cast<int>(this->originalFile->size()), static_cast<char>(0x52));
    if (!this->baseFile) {
        this->baseFileLocation = this->applicationLocation+"/"+this->Get_Base_Name_From_Path(this->patchFileLocation)+"_base.nes";
        if (QFileInfo(this->baseFileLocation).exists()) QFile(this->baseFileLocation).remove();
        this->baseFile = new QFile(this->baseFileLocation);
        if (!this->baseFile->open(QIODevice::ReadWrite)) { this->Close_Working_Files(); return false; }
        if (this->baseFile->write(buffer) != buffer.size()) return false;
        if (!this->baseFile->reset()) return false;
    }

    //Delete the old working file if it exists
    this->writtenSpriteTiles.clear();
    this->writtenBackgroundTiles.clear();
    if (this->workingFile) {
        this->workingFile->close();
        this->workingFile->remove();
        delete this->workingFile;
        this->workingFile = nullptr;
    }

    //Create a copy of the original file to work with
    this->workingFileLocation = this->applicationLocation+"/"+this->Get_Base_Name_From_Path(this->patchFileLocation)+"_working.nes";
    if (QFileInfo(this->workingFileLocation).exists()) QFile(this->workingFileLocation).remove();
    this->workingFile = new QFile(this->workingFileLocation);
    if (!this->workingFile->open(QIODevice::ReadWrite)) { this->Close_Working_Files(); return false; }
    if (this->workingFile->write(buffer) != buffer.size()) return false;
    if (!this->workingFile->reset()) return false;
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

bool Graphics_Ripper::Write_Tiles_And_Order_To_Working_File(qint64 offset, bool sprite) {
    QStack<qint64> offsets;
    offsets.push(offset);
    return this->Write_Tiles_And_Order_To_Working_File(offsets, sprite);
}

bool Graphics_Ripper::Write_Tiles_And_Order_To_Working_File(QStack<qint64> offsets, bool sprite) {
    while (!offsets.isEmpty()) {
        qint64 offset = offsets.pop();
        //Read the tile order
        if (!this->outputFile->seek(offset)) return false;
        QByteArray tileOrder = this->outputFile->read(6);
        if (tileOrder.size() != 6) return false;

        //Update blank tiles
        for (int i = 0; i < tileOrder.size(); ++i) {
            if (this->Is_Tile_Blank(tileOrder.at(i), sprite)) {
                if (sprite) tileOrder.data()[i] = static_cast<char>(0xFC);
                else tileOrder.data()[i] = static_cast<char>(0x24);
            }
        }

        //Write the tile order
        if (!this->workingFile->seek(offset)) return false;
        if (this->workingFile->write(tileOrder) != tileOrder.size()) return false;

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
        if (!this->workingFile->seek(offset)) return false;
        if (this->workingFile->write(graphicsBytes) != graphicsBytes.size()) return false;
        if (sprite) this->writtenSpriteTiles.insert(tile);
        else this->writtenBackgroundTiles.insert(tile);
    }
    return true;
}
