#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QSet>
#include <algorithm>

#ifdef Q_OS_WIN32
const static QString STRING_NEW_LINE = "\r\n";
#else
const static QString STRING_NEW_LINE = "\n";
#endif

bool Case_Sensitive_Less_Than(const QString &s1, const QString &s2) {
    return s1 < s2;
}

bool Sort_File(const QString &filePath) {
    QString fileName = QFileInfo(filePath).fileName();
    qInfo().nospace() << "Sorting " << fileName << "...";

    //Read the current file
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) return false;
    QTextStream input(&file);
    QStringList fileNameStrings = fileName.split('.');
    QString fileNameWithoutExtension;
    QSet<QString> words;
    if (fileNameStrings.size() > 1) {
        for (QStringList::iterator iter = fileNameStrings.begin(); iter != fileNameStrings.end()-1; ++iter) fileNameWithoutExtension += *iter + '.';
        fileNameWithoutExtension.chop(1);
    } else {
        fileNameWithoutExtension = fileName;
    }
    int maxCharacters = fileNameWithoutExtension.size();
    input.readLine(); //ignore the first line
    while (!input.atEnd()) {
        QString word = input.readLine().trimmed().toLower();
        if (word.size() <= maxCharacters && !word.isEmpty()) words.insert(word);
    }
    file.close();

    //Sort the words
    QStringList wordList;
    for (QSet<QString>::iterator iter = words.begin(); iter != words.end(); ++iter) wordList.append(*iter);
    std::sort(wordList.begin(), wordList.end(), Case_Sensitive_Less_Than);
    words.clear();

    //Rewrite the file
    if (!file.open(QIODevice::ReadWrite | QIODevice::Truncate)) return false;
    QTextStream output(&file);
    output << QString::number(wordList.size()) << STRING_NEW_LINE; //write the total number of words
    for (int i = 0; i < wordList.size(); ++i) {
        output << wordList.at(i) << STRING_NEW_LINE;
    }
    output.flush();
    file.close();
    return true;
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    QString applicationLocation = QCoreApplication::applicationDirPath();
    QString sourceCodeLocation;
    if (argc != 2) { qWarning() << "The source code location is required for Word_Sorter to operate correctly!"; qWarning() << "E.g. F:/Documents/Source_Code"; return 1; }
    if (argc >= 2) sourceCodeLocation = QString(argv[1]);
    sourceCodeLocation.replace('\\', '/');
    QString textLocation = sourceCodeLocation+"/Level-Headed_Data/Text/";
    if (!Sort_File(textLocation+"Castle.txt")) { qWarning() << "Unable to sort Castle.txt!"; return 1; }
    if (!Sort_File(textLocation+"Princess.txt")) { qWarning() << "Unable to sort Princess.txt!"; return 1; }
    if (!Sort_File(textLocation+"Thank you.txt")) { qWarning() << "Unable to sort Thank you.txt!"; return 1; }
    return 0;
}
