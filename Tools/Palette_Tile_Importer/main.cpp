#include <QCoreApplication>
#include <QByteArray>
#include <QDebug>
#include <QString>
#include "../../../Level-Headed/SMB1/SMB1_Writer/Level_Offset.h"
#include "../Palette_Color_Mover/Palette_Color_Mover.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    //Show help screen
    if (argc == 1) {
        qInfo() << argv[0] << "<source_file>" << "<destination_file>" << "<tile_type>" << "<list_of_source_tile_IDs_separated_by_spaces>" << "to" << "<list_of_destination_tile_IDs_separated_by_spaces>";
        qInfo() << "<tile_type> can be either \"background\" or \"sprite\"";
        return 0;
    }

    //Open the source file
    QString sourceFileLocation = QString(argv[1]);
    QFile sourceFile(sourceFileLocation);
    if (!sourceFile.open(QIODevice::ReadWrite)) {
        qWarning() << "Unable to open" << sourceFileLocation << "!";
        return 1;
    }

    //Open the destination file
    QString destinationFileLocation = QString(argv[2]);
    QFile destinationFile(destinationFileLocation);
    if (!destinationFile.open(QIODevice::ReadWrite)) {
        sourceFile.close();
        qWarning() << "Unable to open" << destinationFileLocation << "!";
        return 1;
    }

    //Prepare the mover classes
    Level_Offset sourceLevelOffset(&sourceFile, ROM_Type::DEFAULT); //assume default ROM type
    Level_Offset destinationLevelOffset(&destinationFile, ROM_Type::DEFAULT); //assume default ROM type
    Palette_Color_Mover sourceMover(&sourceFile, &sourceLevelOffset);
    Palette_Color_Mover destinationMover(&destinationFile, &destinationLevelOffset);

    //Read the tile type
    bool background = false;
    QString backgroundString = QString(argv[3]).toLower();
    if (backgroundString == "background") background = true;
    else if (backgroundString == "sprite") background = false;
    else {
        qWarning() << argv[3] << "is an invalid <tile_type>!";
        qWarning() << "<tile_type> must be either \"background\" or \"sprite\"!";
        sourceFile.close();
        destinationFile.close();
        return 1;
    }

    //Read the source tile IDs
    QByteArray sourceTileIDs;
    bool success = true;
    int currentArgNum = 4;
    for (int i = currentArgNum; i < argc && success; ++i) {
        char tileID = 0x00;
        success = sourceMover.Get_Hex_From_Char_Arg(argv[i], tileID);
        if (!success) {
            if (QString(argv[i]).toLower() == "to") {
                currentArgNum = i+1;
                break;
            } else {
                qWarning() << "Invalid tile ID format! Make sure to use the word \"to\" between the source and destination tile IDs!";
                sourceFile.close();
                destinationFile.close();
                return 1;
            }
        }
        sourceTileIDs.append(tileID);
    }

    //Read the destination tile IDs
    QByteArray destinationTileIDs;
    success = true;
    for (int i = currentArgNum; i < argc && success; ++i) {
        char tileID = 0x00;
        success = destinationMover.Get_Hex_From_Char_Arg(argv[i], tileID);
        if (!success) {
            qWarning() << "Invalid tile ID format!";
            sourceFile.close();
            destinationFile.close();
            return 1;
        }
        destinationTileIDs.append(tileID);
    }

    //Make sure the argument size is corrent
    if (sourceTileIDs.size() != destinationTileIDs.size()) {
        qWarning() << "Source tile IDs and Destination tile IDs must have the same number of arguments!";
        sourceFile.close();
        destinationFile.close();
        return 1;
    }

    //Perform the tile import
    qInfo() << "Performing tile import...";
    for (int i = 0; i < sourceTileIDs.size(); ++i) {
        QByteArray graphicsBytes;
        if (background) {
            if (!sourceMover.Read_Graphics_Bytes_From_Background_Tile_ID(sourceTileIDs.at(i), graphicsBytes)) {
                qWarning() << "Failed to read tile" << sourceTileIDs.at(i);
                sourceFile.close(); destinationFile.close(); return 1;
            }
            if (!destinationMover.Write_Graphics_Bytes_To_Background_Tile_ID(destinationTileIDs.at(i), graphicsBytes)) {
                qWarning() << "Failed to write tile" << destinationTileIDs.at(i);
                sourceFile.close(); destinationFile.close(); return 1;
            }
        } else {
            if (!sourceMover.Read_Graphics_Bytes_From_Sprite_Tile_ID(sourceTileIDs.at(i), graphicsBytes)) {
                qWarning() << "Failed to read tile" << sourceTileIDs.at(i);
                sourceFile.close(); destinationFile.close(); return 1;
            }
            if (!destinationMover.Write_Graphics_Bytes_To_Sprite_Tile_ID(destinationTileIDs.at(i), graphicsBytes)) {
                qWarning() << "Failed to write tile" << destinationTileIDs.at(i);
                sourceFile.close(); destinationFile.close(); return 1;
            }
        }
    }

    qInfo() << "Import complete!";
    sourceFile.close();
    destinationFile.close();
    return 0;
}
