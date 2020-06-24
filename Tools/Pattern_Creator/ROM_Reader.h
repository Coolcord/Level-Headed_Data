#ifndef ROM_READER_H
#define ROM_READER_H

#include <QString>

class Graphics_Offsets;

class ROM_Reader {
public:
    ROM_Reader(const QString &romLocation);
    ~ROM_Reader();
    bool Open_ROM();
    QByteArray Read_Bytes_From_ROM(qint64 offset, int amount);
    QByteArray Read_Background_Tile_From_ROM(char tileID);
    QByteArray Read_Sprite_Tile_From_ROM(char tileID);


private:
    bool Is_ROM_Valid(QByteArray &bytes);
    void Remove_Header_From_Bytes(QByteArray &bytes);

    QString romLocation;
    QByteArray romBytes;
    Graphics_Offsets *graphicsOffsets;
};

#endif // ROM_READER_H
