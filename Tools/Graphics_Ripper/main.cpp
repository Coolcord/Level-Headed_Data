#include <QCoreApplication>
#include "../../../Hexagon/Hexagon/Hexagon_Interface.h"
#include "../../../Hexagon/Hexagon_GUI/Common_Strings.h"
#include "Graphics_Ripper.h"
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QPluginLoader>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    QString applicationLocation = QCoreApplication::applicationDirPath();
    if (!QFileInfo(applicationLocation+"/SMB1.nes").exists())  { qWarning() << "SMB1.nes does not exist!"; return 1; }

    //Scan for .hexp files to extract graphics from
    QDir dir(applicationLocation);
    dir.mkdir("Patches");
    if (!dir.cd("Patches") || dir.isEmpty()) { qWarning() << "The patches directory is empty!"; return 1; }
    QStringList files = dir.entryList(QStringList("*.hexp"), QDir::Files | QDir::NoDotAndDotDot);
    if (files.isEmpty()) { qWarning() << "The patches directory does not contain any .hexp files!"; return 1; }

    //Load the Hexagon Plugin
    QPluginLoader *pluginLoader = new QPluginLoader(Common_Strings::STRING_PLUGIN_LOCATION);
    QObject *validPlugin = pluginLoader->instance();
    if (!validPlugin) { qWarning() << "Unable to load the backend plugin! Make sure the plugin is in the plugins folder!"; return 1; }
    Hexagon_Interface *hexagonPlugin = qobject_cast<Hexagon_Interface*>(validPlugin);
    if (!hexagonPlugin) { qWarning() << "Unable to load the backend plugin! Make sure the plugin is in the plugins folder!"; return 1; }

    //Rip the Graphics
    for (QString file : files) {
        Graphics_Ripper ripper(applicationLocation, applicationLocation+"/SMB1.nes", applicationLocation+"/Patches/"+file, hexagonPlugin);
        if (!ripper.Rip_Fireball()) { qWarning() << "Failed to rip from" << file; return 1; }
    }
    return 0;
}
