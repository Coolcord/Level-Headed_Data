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
    args.difficultyBulletTime = 11;



    //Place Arguments Here
    //=======================================================
    args.levelType = Level_Type::STANDARD_OVERWORLD;
    args.levelCompliment = Level_Compliment::TREES;
    bool object = false;
    //qint64 offset = 0x000026A0; //Level 1-1 Objects
    //qint64 offset = 0x00001F11; //Level 1-1 Enemies
    //qint64 offset = 0x00002C47; //Level 1-2 Objects
    //qint64 offset = 0x000020E8; //Level 1-2 Enemies
    //qint64 offset = 0x00002705; //Level 1-3 Objects
    //qint64 offset = 0x00001F2F; //Level 1-3 Enemies
    //qint64 offset = 0x000021C1; //Level 1-4 Objects
    //qint64 offset = 0x00001D80; //Level 1-4 Enemies
    //qint64 offset = 0x000027DF; //Level 2-1 Objects
    //qint64 offset = 0x00001F61; //Level 2-1 Enemies
    //qint64 offset = 0x00002E57; //Level 2-2 Objects
    //qint64 offset = 0x00002181; //Level 2-2 Enemies
    //qint64 offset = 0x0000275A; //Level 2-3 Objects
    //qint64 offset = 0x00001F4C; //Level 2-3 Enemies
    //qint64 offset = 0x000022A1; //Level 2-4 Objects
    //qint64 offset = 0x00001DC0; //Level 2-4 Enemies
    //qint64 offset = 0x0000262B; //Level 3-1 Objects
    //qint64 offset = 0x00001EE0; //Level 3-1 Enemies
    //qint64 offset = 0x00002C14; //Level 3-2 Objects
    //qint64 offset = 0x000020C3; //Level 3-2 Enemies
    //qint64 offset = 0x0000247D; //Level 3-3 Objects
    //qint64 offset = 0x00001E69; //Level 3-3 Enemies
    //qint64 offset = 0x00002314; //Level 3-4 Objects
    //qint64 offset = 0x00001DEF; //Level 3-4 Enemies
    //qint64 offset = 0x00002549; //Level 4-1 Objects
    //qint64 offset = 0x00001EAB; //Level 4-1 Enemies
    //qint64 offset = 0x00002CEA; //Level 4-2 Objects
    //qint64 offset = 0x00002115; //Level 4-2 Enemies
    //qint64 offset = 0x000028A1; //Level 4-3 Objects
    //qint64 offset = 0x00001FB9; //Level 4-3 Enemies
    //qint64 offset = 0x00002222; //Level 4-4 Objects
    //qint64 offset = 0x00001DA7; //Level 4-4 Enemies
    //qint64 offset = 0x0000284D; //Level 5-1 Objects
    //qint64 offset = 0x00001F8C; //Level 5-1 Enemies
    //qint64 offset = 0x00002AA4; //Level 5-2 Objects
    //qint64 offset = 0x00002045; //Level 5-2 Enemies
    //qint64 offset = 0x00002705; //Level 5-3 Objects
    //qint64 offset = 0x00001F2F; //Level 5-3 Enemies
    //qint64 offset = 0x000022A1; //Level 5-4 Objects
    //qint64 offset = 0x00001DC0; //Level 5-4 Enemies
    //qint64 offset = 0x0000296D; //Level 6-1 Objects
    //qint64 offset = 0x00002001; //Level 6-1 Enemies
    //qint64 offset = 0x0000259C; //Level 6-2 Objects
    //qint64 offset = 0x00001EB9; //Level 6-2 Enemies
    //qint64 offset = 0x00002908; //Level 6-3 Objects
    //qint64 offset = 0x00001FDE; //Level 6-3 Enemies
    //qint64 offset = 0x000021C1; //Level 6-4 Objects
    //qint64 offset = 0x00001D80; //Level 6-4 Enemies
    //qint64 offset = 0x00002B90; //Level 7-1 Objects
    //qint64 offset = 0x0000209E; //Level 7-1 Enemies
    //qint64 offset = 0x00002E57; //Level 7-2 Objects
    //qint64 offset = 0x00002181; //Level 7-2 Enemies
    //qint64 offset = 0x0000275A; //Level 7-3 Objects
    //qint64 offset = 0x00001F4C; //Level 7-3 Enemies
    //qint64 offset = 0x00002381; //Level 7-4 Objects
    //qint64 offset = 0x00001E1A; //Level 7-4 Enemies
    //qint64 offset = 0x00002A11; //Level 8-1 Objects
    //qint64 offset = 0x0000200B; //Level 8-1 Enemies
    //qint64 offset = 0x00002B17; //Level 8-2 Objects
    //qint64 offset = 0x00002070; //Level 8-2 Enemies
    //qint64 offset = 0x000024E0; //Level 8-3 Objects
    //qint64 offset = 0x00001E8E; //Level 8-3 Enemies
    //qint64 offset = 0x0000240C; //Level 8-4 Objects
    qint64 offset = 0x00001E2F; //Level 8-4 Enemies

    //qint64 offset = 0x00002844; //Pipe_Intro Objects
    //qint64 offset = 0x00002D8B; //Underground_Bonus Objects
    //qint64 offset = 0x00002143; //Underground_Bonus Enemies
    //qint64 offset = 0x0000288C; //Cloud_Bonus_1 Objects
    //qint64 offset = 0x00001FB0; //Cloud_Bonus_1 Enemies
    //qint64 offset = 0x00002BE9; //Cloud_Bonus_2 Objects
    //qint64 offset = 0x000020BA; //Cloud_Bonus_2 Enemies
    //qint64 offset = 0x000029E0; //Warp_Zone Objects
    //qint64 offset = 0x00002E18; //Underwater_Bonus Objects
    //qint64 offset = 0x00002170; //Underwater_Bonus Enemies
    //qint64 offset = 0x00002ED2; //Castle_Underwater Objects
    //qint64 offset = 0x000021AB; //Castle_Underwater Enemies
    //=======================================================



    //Parse the level
    if (!file.seek(offset)) { output.close(); file.close(); return 1; }
    if (object) {
        Object_Parser objectParser(&stream, 10000, &args);
        QByteArray bytes = file.read(2);
        while (!objectParser.At_End(bytes.at(0))) {
            if (!objectParser.Parse_Object(bytes.at(0), bytes.at(1), args.levelType)) { output.close(); file.close(); return 1; }
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
