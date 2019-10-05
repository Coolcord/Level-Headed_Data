#include "Graphics_Ripper.h"
#include <assert.h>
#include <QFileInfo>

Graphics_Ripper::Graphics_Ripper(const QString &originalFileLocation, const QString &patchFileLocation, Hexagon_Interface *hexagon) {
    assert(hexagon);
    this->originalFileLocation = originalFileLocation;
    this->patchFileLocation = patchFileLocation;
    this->outputFile = nullptr;
    this->hexagon = hexagon;
}

Graphics_Ripper::~Graphics_Ripper() {
    this->outputFile->close();
    this->outputFile->remove();
    delete this->outputFile;
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
    if (!this->Rip_Text()) return false;
    if (!this->Rip_Tree_Platform()) return false;
    if (!this->Rip_Underwater_Block()) return false;
    if (!this->Rip_Water()) return false;
    return true;
}

bool Graphics_Ripper::Rip_Blooper() {
    if (!this->Apply_Patch()) return false;

}

bool Graphics_Ripper::Rip_Bowser() {
    if (!this->Apply_Patch()) return false;

}

bool Graphics_Ripper::Rip_Bullet_Bill() {
    if (!this->Apply_Patch()) return false;

}

bool Graphics_Ripper::Rip_Buzzy_Beetle() {
    if (!this->Apply_Patch()) return false;

}

bool Graphics_Ripper::Rip_Cheep_Cheep() {
    if (!this->Apply_Patch()) return false;

}

bool Graphics_Ripper::Rip_Goomba() {
    if (!this->Apply_Patch()) return false;

}

bool Graphics_Ripper::Rip_Hammer_Bro() {
    if (!this->Apply_Patch()) return false;

}

bool Graphics_Ripper::Rip_Koopa() {
    if (!this->Apply_Patch()) return false;

}

bool Graphics_Ripper::Rip_Lakitu() {
    if (!this->Apply_Patch()) return false;

}

bool Graphics_Ripper::Rip_Jump_Spring() {
    if (!this->Apply_Patch()) return false;

}

bool Graphics_Ripper::Rip_Mario() {
    if (!this->Apply_Patch()) return false;

}

bool Graphics_Ripper::Rip_Peach() {
    if (!this->Apply_Patch()) return false;

}

bool Graphics_Ripper::Rip_Piranha_Plant() {
    if (!this->Apply_Patch()) return false;

}

bool Graphics_Ripper::Rip_Podoboo() {
    if (!this->Apply_Patch()) return false;

}

bool Graphics_Ripper::Rip_Spiny() {
    if (!this->Apply_Patch()) return false;

}

bool Graphics_Ripper::Rip_Spiny_Egg() {
    if (!this->Apply_Patch()) return false;

}

bool Graphics_Ripper::Rip_Toad() {
    if (!this->Apply_Patch()) return false;

}

bool Graphics_Ripper::Rip_Axe() {
    if (!this->Apply_Patch()) return false;

}

bool Graphics_Ripper::Rip_Brick_Block() {
    if (!this->Apply_Patch()) return false;

}

bool Graphics_Ripper::Rip_Bridge() {
    if (!this->Apply_Patch()) return false;

}

bool Graphics_Ripper::Rip_Bowser_Bridge() {
    if (!this->Apply_Patch()) return false;

}

bool Graphics_Ripper::Rip_Bullet_Bill_Cannon() {
    if (!this->Apply_Patch()) return false;

}

bool Graphics_Ripper::Rip_Castle_Block() {
    if (!this->Apply_Patch()) return false;

}

bool Graphics_Ripper::Rip_Chain() {
    if (!this->Apply_Patch()) return false;

}

bool Graphics_Ripper::Rip_Cloud_Block() {
    if (!this->Apply_Patch()) return false;

}

bool Graphics_Ripper::Rip_Coin() {
    if (!this->Apply_Patch()) return false;

}

bool Graphics_Ripper::Rip_Coral() {
    if (!this->Apply_Patch()) return false;

}

bool Graphics_Ripper::Rip_Fire_Flower() {
    if (!this->Apply_Patch()) return false;

}

bool Graphics_Ripper::Rip_Flagpole() {
    if (!this->Apply_Patch()) return false;

}

bool Graphics_Ripper::Rip_Mushroom_Powerup() {
    if (!this->Apply_Patch()) return false;

}

bool Graphics_Ripper::Rip_Mushroom_Platform() {
    if (!this->Apply_Patch()) return false;

}

bool Graphics_Ripper::Rip_Overworld_Block() {
    if (!this->Apply_Patch()) return false;

}

bool Graphics_Ripper::Rip_Pipe() {
    if (!this->Apply_Patch()) return false;

}

bool Graphics_Ripper::Rip_Question_Block() {
    if (!this->Apply_Patch()) return false;

}

bool Graphics_Ripper::Rip_Rope() {
    if (!this->Apply_Patch()) return false;

}

bool Graphics_Ripper::Rip_Solid_Block() {
    if (!this->Apply_Patch()) return false;

}

bool Graphics_Ripper::Rip_Text() {
    if (!this->Apply_Patch()) return false;

}

bool Graphics_Ripper::Rip_Tree_Platform() {
    if (!this->Apply_Patch()) return false;

}

bool Graphics_Ripper::Rip_Underwater_Block() {
    if (!this->Apply_Patch()) return false;

}

bool Graphics_Ripper::Rip_Water() {
    if (!this->Apply_Patch()) return false;

}

bool Graphics_Ripper::Apply_Patch() {
    if (this->outputFile) return true; //patch already applied
    int lineNum = 0;
    QString outputLocation = "./"+QFileInfo(this->patchFileLocation).baseName()+".nes";
    if (this->hexagon->Apply_Hexagon_Patch(this->patchFileLocation, this->originalFileLocation, outputLocation, false, lineNum) != Hexagon_Error_Codes::OK) return false;
    this->outputFile = new QFile(outputLocation);
    return this->outputFile->open(QIODevice::ReadWrite);
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
