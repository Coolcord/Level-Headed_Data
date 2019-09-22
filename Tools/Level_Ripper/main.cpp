#include <QCoreApplication>
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include "../../../Level-Headed/SMB1/SMB1_Compliance_Generator/SMB1_Compliance_Generator_Arguments.h"
#include "Enemy_Parser.h"
#include "Object_Parser.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    QFile file(a.applicationDirPath()+"/SMB1.nes");
    QFile output(a.applicationDirPath()+"/dump.txt");
    if (!file.open(QIODevice::ReadOnly)) return 1;
    if (!output.open(QIODevice::WriteOnly | QIODevice::Truncate)) { file.close(); return 1; }
    QTextStream stream(&output);
    SMB1_Compliance_Generator_Arguments args;
    args.endCastle = Castle::SMALL;
    args.startCastle = Castle::SMALL;
    args.difficulty = 1;
    args.useMidpoints = true;



    //Place Arguments Here
    //=======================================================
    args.levelType = Level_Type::UNDERGROUND;
    args.levelCompliment = Level_Compliment::TREES;
    bool object = true;
    //qint64 offset = 0x000026A0; //Level 1-1 Objects
    //qint64 offset = 0x00001F11; //Level 1-1 Enemies
    //qint64 offset = 0x00002C47; //Level 1-2 Objects
    //qint64 offset = 0x000020E8; //Level 1-2 Enemies
    //qint64 offset = 0x00002705; //Level 1-3 Objects
    //qint64 offset = 0x00001F2F; //Level 1-3 Enemies
    //qint64 offset = 0x000021C1; //Level 1-4 Objects
    //qint64 offset = 0x00001D80; //Level 1-4 Enemies
    qint64 offset = 0x000027DF; //Level 2-1 Objects
    //qint64 offset = 0x00001F61; //Level 2-1 Enemies
    //=======================================================



    //Parse the level
    if (!file.seek(offset)) { output.close(); file.close(); return 1; }
    if (object) {
        Object_Parser objectParser(&stream, 10000, &args);
        QByteArray bytes = file.read(2);
        while (!objectParser.At_End(bytes.at(0))) {
            if (!objectParser.Parse_Object(bytes.at(0), bytes.at(1))) { output.close(); file.close(); return 1; }
            bytes = file.read(2);
        }
    } else {
        Enemy_Parser enemyParser(&stream, 10000, &args);
        QByteArray bytes = file.read(2);
        while (!enemyParser.At_End(bytes.at(0))) {
            if (enemyParser.Is_Pipe_Pointer(bytes.at(0), bytes.at(1))) {
                bytes += file.read(1);
                if (!enemyParser.Parse_Pipe_Pointer(bytes.at(0), bytes.at(1), bytes.at(2))) { output.close(); file.close(); return 1; }
            } else {
                if (!enemyParser.Parse_Enemy(bytes.at(0), bytes.at(1))) { output.close(); file.close(); return 1; }
            }
            bytes = file.read(2);
        }
    }
    stream.flush();
    output.flush();
    output.close();
    file.close();
    qDebug() << "Dump.txt generated!";
    return 0;
}
