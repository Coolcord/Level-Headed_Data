#ifndef DUPLICATE_REMOVER_H
#define DUPLICATE_REMOVER_H

#include <QFile>
#include <QSet>
#include <QString>

class Duplicate_Remover {
public:
    Duplicate_Remover(const QString &spritesLocation);
    ~Duplicate_Remover() {}
    bool Scan_And_Remove_All_Duplicates();

private:
    bool Add_File_Hash_To_Set(QFile &file, QSet<QString> &hashes);

    QString spritesLocation;
};

#endif // DUPLICATE_REMOVER_H
