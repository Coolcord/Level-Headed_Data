#include "Duplicate_Remover.h"
#include <QCryptographicHash>
#include <QDir>
#include <QFileInfo>

Duplicate_Remover::Duplicate_Remover(const QString &spritesLocation) {
    this->spritesLocation = spritesLocation;
}

bool Duplicate_Remover::Scan_And_Remove_All_Duplicates() {
    QDir dir(this->spritesLocation);
    for (QString folder : QDir(this->spritesLocation).entryList(QDir::Dirs | QDir::NoDotAndDotDot)) {
        QSet<QString> hashes;

        //Add original first
        QString originalPatchLocation = this->spritesLocation+"/"+folder+"/Original (by Nintendo).hexp";
        if (QFileInfo(originalPatchLocation).exists()) {
            QFile file(originalPatchLocation);
            if (!this->Add_File_Hash_To_Set(file, hashes)) return false;
        }

        //Scan all other patches
        for (QString patchFile : QDir(this->spritesLocation+"/"+folder).entryList(QStringList("*.hexp"), QDir::Files | QDir::NoDotAndDotDot)) {
            QString patchFileLocation = this->spritesLocation+"/"+folder+"/"+patchFile;
            if (patchFileLocation == originalPatchLocation) continue; //don't delete the original file
            QFile file(patchFileLocation);
            if (patchFile.startsWith("+")) { //bonus graphics packs are not allowed
                file.remove();
                continue;
            }
            if (!this->Add_File_Hash_To_Set(file, hashes)) return false;
        }
    }
    return true;
}

bool Duplicate_Remover::Add_File_Hash_To_Set(QFile &file, QSet<QString> &hashes) {
    if (!file.open(QIODevice::ReadOnly)) return false;
    QByteArray buffer = file.readAll();
    if (buffer.size() == 0) { //delete empty files
        file.close();
        file.remove();
    } else { //store the hash of the file and remove duplicates
        QString hash = QString(QCryptographicHash::hash(buffer, QCryptographicHash::Sha512).toHex().toUpper());
        if (hashes.contains(hash)) {
            file.close();
            file.remove();
        } else {
            hashes.insert(hash);
        }
    }
    file.close();
    return true;
}
