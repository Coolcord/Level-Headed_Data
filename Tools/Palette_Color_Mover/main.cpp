#include <QCoreApplication>
#include "../../../Level-Headed/SMB1/SMB1_Writer/Level_Offset.h"
#include "../../../Level-Headed/SMB1/SMB1_Writer/ROM_Type.h"
#include "Palette_Color_Mover.h"
#include <QFile>
#include <QFileInfo>
#include <QDebug>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    QString operation(argv[2]);
    operation = operation.toLower();
    bool allowMoreArguments = (operation == "background" || operation == "sprite");
    if ((allowMoreArguments && argc < 6) || (!allowMoreArguments && argc != 5)) {
        qInfo() << argv[0] << "[file] [operand] [color1] [color2]";
        qInfo() << "";
        qInfo() << "Colors must be between 1-3";
        qInfo() << "";
        qInfo() << "Possible operands:";
        qInfo() << "rgb";
        qInfo() << "rg";
        qInfo() << "rb (not recommended!)";
        qInfo() << "gb (not recommended!)";
        qInfo() << "red (not recommended!)";
        qInfo() << "green (not recommended!)";
        qInfo() << "blue";
        qInfo() << "black (alias for blue)";
        qInfo() << "mario";
        qInfo() << "bowser";
        qInfo() << "";
        qInfo() << "Additional operands (will not change the color palette):";
        qInfo() << "background [color1] [color2] [titleIDs]";
        qInfo() << "sprite [color1] [color2] [titleIDs]";
        qInfo() << "";
        qInfo() << "[titleIDs] should be formated like this (specify as many as needed): 00 01 02 03";
        qInfo() << "";
        return 1;
    }

    QFile originalFile(argv[1]);
    if (!originalFile.open(QIODevice::ReadWrite)) {
        qWarning() << "Unable to open" << argv[1] << "!";
        return 1;
    }
    QByteArray bytes = originalFile.readAll();
    QFileInfo fileInfo(argv[1]);
    QStringList splitName = fileInfo.fileName().split('.');
    QString fileNameWithoutExtension;
    for (int i = 0; i < splitName.size()-1; ++i) {
        fileNameWithoutExtension += splitName.at(i);
        if (i != splitName.size()-2) fileNameWithoutExtension += ".";
    }
    QString filePath = fileInfo.path()+"/"+fileNameWithoutExtension+"_Swapped."+fileInfo.suffix();
    QFile file(filePath);
    if (!file.open(QIODevice::ReadWrite) || file.write(bytes) != bytes.size()) {
        qWarning() << "Unable to open" << fileInfo.baseName() << "for writing!";
        return 1;
    }
    file.flush();
    file.reset();

    Level_Offset levelOffset(&file, ROM_Type::DEFAULT);
    Palette_Color_Mover paletteColorMover(&file, &levelOffset);
    QString color1String(argv[3]);
    QString color2String(argv[4]);
    bool valid = false;
    int color1 = color1String.toInt(&valid);
    if (!valid) {
        qWarning() << argv[3] << "is not a valid color! Color must be 1, 2, or 3";
        return 1;
    }
    int color2 = color2String.toInt(&valid);
    if (!valid) {
        qWarning() << argv[4] << "is not a valid color! Color must be 1, 2, or 3";
        return 1;
    }

    bool success = false;
    if (operation == "rgb") {
        success = paletteColorMover.Swap_Colors_In_RGB_Groups(color1, color2);
    } else if (operation == "rg") {
        success = paletteColorMover.Swap_Colors_In_Red_Group(color1, color2);
        if (success) success = paletteColorMover.Swap_Colors_In_Green_Group(color1, color2);
    } else if (operation == "rb") {
        success = paletteColorMover.Swap_Colors_In_Red_Group(color1, color2);
        if (success) success = paletteColorMover.Swap_Colors_In_Blue_Group(color1, color2);
    } else if (operation == "gb") {
        success = paletteColorMover.Swap_Colors_In_Green_Group(color1, color2);
        if (success) success = paletteColorMover.Swap_Colors_In_Blue_Group(color1, color2);
    } else if (operation == "red") {
        success = paletteColorMover.Swap_Colors_In_Red_Group(color1, color2);
    } else if (operation == "green") {
        success = paletteColorMover.Swap_Colors_In_Green_Group(color1, color2);
    } else if (operation == "blue" || operation == "black") {
        success = paletteColorMover.Swap_Colors_In_Blue_Group(color1, color2);
    } else if (operation == "mario") {
        success = paletteColorMover.Swap_Colors_In_Mario_Group(color1, color2);
    } else if (operation == "bowser") {
        success = paletteColorMover.Swap_Colors_In_Bowser_Group(color1, color2);
    } else if (operation == "background") {
        success = true;
        for (int i = 5; i < argc && success; ++i) {
            char tileID = 0x00;
            success = paletteColorMover.Get_Hex_From_Char_Arg(argv[i], tileID);
            if (!success) break;
            success = paletteColorMover.Swap_Colors_In_Background_Tile_Without_Touching_Palette(color1, color2, tileID);
        }
    } else if (operation == "sprite") {
        success = true;
        for (int i = 5; i < argc && success; ++i) {
            char tileID = 0x00;
            success = paletteColorMover.Get_Hex_From_Char_Arg(argv[i], tileID);
            if (!success) break;
            success = paletteColorMover.Swap_Colors_In_Sprite_Tile_Without_Touching_Palette(color1, color2, tileID);
        }
    } else {
        qWarning() << "Unknown operation!";
        return 1;
    }

    if (success) {
        qInfo() << QFileInfo(filePath).fileName() << "created!";
        return 0;
    } else {
        qWarning() << "Operation failed!";
        return 1;
    }
}
