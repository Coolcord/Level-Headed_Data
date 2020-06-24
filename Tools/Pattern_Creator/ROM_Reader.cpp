#include "ROM_Reader.h"
#include "../../../Level-Headed/SMB1/SMB1_Writer/Graphics_Offsets.h"
#include <QDebug>
#include <QFile>
#include <assert.h>

const static int UNHEADERED_ROM_SIZE = 40960;

ROM_Reader::ROM_Reader() {
    this->romBytes = QByteArray();
    this->graphicsOffsets = new Graphics_Offsets();
}

ROM_Reader::~ROM_Reader() {
    delete this->graphicsOffsets;
}

bool ROM_Reader::Open_ROM(const QString &romLocation) {
    QFile file(romLocation);
    if (!file.exists() || !file.open(QIODevice::ReadOnly)) return false;
    QByteArray bytes = file.readAll();
    file.close();
    if (!this->Is_ROM_Valid(bytes)) return false;
    this->romBytes = bytes;
    return true;
}

QByteArray ROM_Reader::Read_Bytes_From_ROM(qint64 offset, int amount) {
    QByteArray bytes = QByteArray(amount, static_cast<char>(0xFF));
    if (this->romBytes.isEmpty()) return bytes;
    if (offset + amount >= this->romBytes.size()) return bytes;
    for (int i = 0; i < amount; ++i) bytes[i] = this->romBytes.at(offset+i);
    return bytes;
}

QByteArray ROM_Reader::Read_Background_Tile_From_ROM(char tileID) {
    unsigned char c = static_cast<unsigned char>(tileID);
    qint64 spriteGraphicsOffset = 0x9000+(c*0x10); //get the graphics offset for the tile
    return this->Read_Bytes_From_ROM(spriteGraphicsOffset, 0x10);
}

QByteArray ROM_Reader::Read_Sprite_Tile_From_ROM(char tileID) {
    unsigned char c = static_cast<unsigned char>(tileID);
    qint64 spriteGraphicsOffset = 0x8000+(c*0x10); //get the graphics offset for the tile
    return this->Read_Bytes_From_ROM(spriteGraphicsOffset, 0x10);
}

bool ROM_Reader::Is_ROM_Valid(QByteArray &bytes) {
    if (bytes.size() < UNHEADERED_ROM_SIZE) return false;
    this->Remove_Header_From_Bytes(bytes);
    if (bytes.size() != UNHEADERED_ROM_SIZE) return false;

    //Check against first chunk
    if (bytes.at(0x0000) != static_cast<char>(0x78)) return false;
    if (bytes.at(0x0001) != static_cast<char>(0xD8)) return false;
    if (bytes.at(0x0002) != static_cast<char>(0xA9)) return false;
    if (bytes.at(0x0003) != static_cast<char>(0x10)) return false;
    if (bytes.at(0x0004) != static_cast<char>(0x8D)) return false;
    if (bytes.at(0x0005) != static_cast<char>(0x00)) return false;
    if (bytes.at(0x0006) != static_cast<char>(0x20)) return false;
    if (bytes.at(0x0007) != static_cast<char>(0xA2)) return false;
    if (bytes.at(0x0008) != static_cast<char>(0xFF)) return false;
    if (bytes.at(0x0009) != static_cast<char>(0x9A)) return false;
    if (bytes.at(0x000A) != static_cast<char>(0xAD)) return false;
    if (bytes.at(0x000B) != static_cast<char>(0x02)) return false;
    if (bytes.at(0x000C) != static_cast<char>(0x20)) return false;
    if (bytes.at(0x000D) != static_cast<char>(0x10)) return false;
    if (bytes.at(0x000E) != static_cast<char>(0xFB)) return false;
    if (bytes.at(0x000F) != static_cast<char>(0xAD)) return false;
    if (bytes.at(0x0010) != static_cast<char>(0x02)) return false;
    if (bytes.at(0x0011) != static_cast<char>(0x20)) return false;

    //Check against second chunk
    if (bytes.at(0x3FF0) != static_cast<char>(0xB5)) return false;
    if (bytes.at(0x3FF1) != static_cast<char>(0x65)) return false;
    if (bytes.at(0x3FF2) != static_cast<char>(0x07)) return false;
    if (bytes.at(0x3FF3) != static_cast<char>(0x95)) return false;
    if (bytes.at(0x3FF4) != static_cast<char>(0xB5)) return false;
    if (bytes.at(0x3FF5) != static_cast<char>(0xBD)) return false;
    if (bytes.at(0x3FF6) != static_cast<char>(0x33)) return false;
    if (bytes.at(0x3FF7) != static_cast<char>(0x04)) return false;
    if (bytes.at(0x3FF8) != static_cast<char>(0x18)) return false;
    if (bytes.at(0x3FF9) != static_cast<char>(0x65)) return false;
    if (bytes.at(0x3FFA) != static_cast<char>(0x00)) return false;
    if (bytes.at(0x3FFB) != static_cast<char>(0x9D)) return false;
    if (bytes.at(0x3FFC) != static_cast<char>(0x33)) return false;
    if (bytes.at(0x3FFD) != static_cast<char>(0x04)) return false;
    if (bytes.at(0x3FFE) != static_cast<char>(0xB5)) return false;
    if (bytes.at(0x3FFF) != static_cast<char>(0x9F)) return false;
    if (bytes.at(0x4000) != static_cast<char>(0x69)) return false;
    if (bytes.at(0x4001) != static_cast<char>(0x00)) return false;

    //Check against third chunk
    if (bytes.at(0x9FFA) != static_cast<char>(0xFF)) return false;
    if (bytes.at(0x9FFB) != static_cast<char>(0xFF)) return false;
    if (bytes.at(0x9FFC) != static_cast<char>(0xFF)) return false;
    if (bytes.at(0x9FFD) != static_cast<char>(0xFF)) return false;
    if (bytes.at(0x9FFE) != static_cast<char>(0xFF)) return false;
    if (bytes.at(0x9FFF) != static_cast<char>(0xFF)) return false;
    return true;
}

void ROM_Reader::Remove_Header_From_Bytes(QByteArray &bytes) {
    assert(bytes.size() > 0x10);
    if (bytes.at(0) == static_cast<char>(0x4E) && bytes.at(1) == static_cast<char>(0x45)
            && bytes.at(2) == static_cast<char>(0x53) && bytes.at(3) == static_cast<char>(0x1A)) {
        bytes.remove(0, 0x10);
    }
}
