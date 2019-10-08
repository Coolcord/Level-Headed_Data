QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        ../../../Hexagon/Hexagon/Value_Manipulator.cpp \
        ../../../Level-Headed/SMB1/SMB1_Writer/Graphics_Offsets.cpp \
        Duplicate_Remover.cpp \
        Graphics_Ripper.cpp \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    ../../../Hexagon/Hexagon/Hexagon_Interface.h \
    ../../../Hexagon/Hexagon/Patch_Strings.h \
    ../../../Hexagon/Hexagon/Value_Manipulator.h \
    ../../../Hexagon/Hexagon_GUI/Common_Strings.h \
    ../../../Level-Headed/SMB1/Common_SMB1_Files/Fix_Strings.h \
    ../../../Level-Headed/SMB1/SMB1_Writer/Graphics_Offsets.h \
    Duplicate_Remover.h \
    Graphics_Ripper.h
