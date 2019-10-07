#include <QCoreApplication>
#include "../../../Hexagon/Hexagon/Hexagon_Interface.h"
#include "../../../Hexagon/Hexagon_GUI/Common_Strings.h"
#include "Duplicate_Remover.h"
#include "Graphics_Ripper.h"
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QPluginLoader>
#include <QTextStream>

//Arguments
const static QString STRING_GRAPHICS_PATCHES_LOCATION = "F:/Documents/Source_Code/Level-Headed_Data/Graphics";

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    QString applicationLocation = QCoreApplication::applicationDirPath();
    if (!QFileInfo(applicationLocation+"/SMB1.nes").exists())  { qWarning() << "SMB1.nes does not exist!"; return 1; }

    //Copy all patches over to the patches directory
    qInfo() << "Preparing patches...";
    QDir patchDir(STRING_GRAPHICS_PATCHES_LOCATION);
    QDir dir(applicationLocation);
    dir.mkdir("Patches");
    if (patchDir.exists()) {
        QDir(applicationLocation+"/Patches").removeRecursively();
        dir.mkdir("Patches");
        for (QString fileName : patchDir.entryList(QStringList("*.hexp"), QDir::Files | QDir::NoDotAndDotDot)) {
            QFile file(STRING_GRAPHICS_PATCHES_LOCATION+"/"+fileName);
            if (!file.open(QIODevice::ReadOnly)) continue;
            QFile outputFile(applicationLocation+"/Patches/"+fileName);
            if (!outputFile.open(QIODevice::ReadWrite)) { file.close(); continue; }
            outputFile.write(file.readAll());
            file.close();
            outputFile.close();
        }
    }

    //Generate the original patch file
    QFile originalPatchFile(applicationLocation+"/Patches/Original (by Nintendo).hexp");
    originalPatchFile.remove();
    if (!originalPatchFile.open(QIODevice::ReadWrite)) { qWarning() << "Unable to generate the original patch file!"; return 1; }
    QTextStream originalPatchFileStream(&originalPatchFile);
    originalPatchFileStream << "A: 0x1CCC" << Common_Strings::STRING_NEW_LINE;
    originalPatchFileStream << "V: 2529C0" << Common_Strings::STRING_NEW_LINE;
    originalPatchFileStream.flush();
    originalPatchFile.flush(); originalPatchFile.close();

    //Scan for .hexp files to extract graphics from
    if (!dir.cd("Patches") || dir.isEmpty()) { qWarning() << "The patches directory is empty!"; return 1; }
    QStringList files = dir.entryList(QStringList("*.hexp"), QDir::Files | QDir::NoDotAndDotDot);
    if (files.isEmpty()) { qWarning() << "The patches directory does not contain any .hexp files!"; return 1; }
    QDir(applicationLocation+"/Sprites").removeRecursively();

    //Load the Hexagon Plugin
    QPluginLoader *pluginLoader = new QPluginLoader(Common_Strings::STRING_PLUGIN_LOCATION);
    QObject *validPlugin = pluginLoader->instance();
    if (!validPlugin) { qWarning() << "Unable to load the backend plugin! Make sure the plugin is in the plugins folder!"; return 1; }
    Hexagon_Interface *hexagonPlugin = qobject_cast<Hexagon_Interface*>(validPlugin);
    if (!hexagonPlugin) { qWarning() << "Unable to load the backend plugin! Make sure the plugin is in the plugins folder!"; return 1; }

    //Rip the Graphics
    for (QString file : files) {
        qInfo() << "Ripping from" << file;
        Graphics_Ripper ripper(applicationLocation, applicationLocation+"/SMB1.nes", applicationLocation+"/Patches/"+file, hexagonPlugin);
        if (!ripper.Rip_All()) { qWarning() << "Failed to rip from" << file; return 1; }
    }
    qInfo() << "Removing duplicates...";
    if (!Duplicate_Remover(applicationLocation+"/Sprites").Scan_And_Remove_All_Duplicates()) { qWarning() << "Failed to remove duplicates!"; return 1; }
    qInfo() << "Ripping complete!";
    return 0;
}
