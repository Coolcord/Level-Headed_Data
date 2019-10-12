#ifndef BLACKLIST_H
#define BLACKLIST_H

#include <QMap>
#include <QString>

class Blacklist {
public:
    Blacklist();
    ~Blacklist();
    bool Read_Blacklist_From_File(const QString &fileLocation);
    bool Is_Blacklisted(const QString &fileName);
    QString Get_Suggested_File_Name(const QString &fileName);

    void Populate_Mario_Sprite_Blacklist();

private:
    QMap<QString, QString> *blacklistMap;
};

#endif // BLACKLIST_H
