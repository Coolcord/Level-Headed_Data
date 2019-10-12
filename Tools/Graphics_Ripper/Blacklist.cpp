#include "Blacklist.h"
#include <QFile>
#include <QTextStream>

const QString STRING_NONE = "none";

Blacklist::Blacklist() {
    this->blacklistMap = new QMap<QString, QString>();
}

Blacklist::~Blacklist() {
    delete this->blacklistMap;
}

bool Blacklist::Read_Blacklist_From_File(const QString &fileLocation) {
    QFile file(fileLocation);
    if (!file.open(QIODevice::ReadOnly)) return false;
    QTextStream stream(&file);
    while (!stream.atEnd()) {
        QString line = stream.readLine();
        if (line.contains(": ")) {
            QStringList strings = line.split(": ");
            this->blacklistMap->insert(strings.at(0), strings.at(1));
        }
    }
    file.close();
    return true;
}

bool Blacklist::Is_Blacklisted(const QString &fileName) {
    QMap<QString, QString>::iterator iter = this->blacklistMap->find(fileName);
    if (iter == this->blacklistMap->end()) return false;
    return iter.value().toLower() == STRING_NONE;
}

QString Blacklist::Get_Suggested_File_Name(const QString &fileName) {
    QMap<QString, QString>::iterator iter = this->blacklistMap->find(fileName);
    if (iter == this->blacklistMap->end()) return fileName; //file not in blacklist
    if (iter.value().toLower() == STRING_NONE) return fileName;
    return iter.value();
}

void Blacklist::Populate_Mario_Sprite_Blacklist() {
    this->blacklistMap->insert("Hyper Mario (Rev A)", "None");
    this->blacklistMap->insert("Hyper Mario (Rev B)", "Hyper Mario");
    this->blacklistMap->insert("Mario 2001", "None");
    this->blacklistMap->insert("Mario Bros. Untold (by Dark_Lord05)", "None");
    this->blacklistMap->insert("New Mario Bros. (Palette 1) (by Super Stiviboy)", "SMB1 Modern");
    this->blacklistMap->insert("New Mario Bros. (Palette 2) (by Super Stiviboy)", "None");
    this->blacklistMap->insert("Original (by Nintendo)", "Original (by Nintendo)");
    this->blacklistMap->insert("Pocket Edition (by Fantendo)", "None");
    this->blacklistMap->insert("Super Bubba Bros.", "None");
    this->blacklistMap->insert("Super Mario Bros. 4 (by Guscraft808Beta2)", "None");
    this->blacklistMap->insert("Super Mario Bros. DX v2.0 (by flamepanther)", "SMB3");
    this->blacklistMap->insert("Super Mario Bros. DX v3.4 (by flamepanther)", "None");
    this->blacklistMap->insert("Super Mario MCB Color Edition (by MacBee)", "MCB");
    this->blacklistMap->insert("Super Mario S (by Sogun)", "None");
    this->blacklistMap->insert("Zoku Jun (Palette 1) (by Mikachu)", "None");
    this->blacklistMap->insert("Zoku Jun (Palette 2) (by Mikachu)", "None");
}
