QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

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
    ../../../Level-Headed/SMB1/SMB1_Writer/Graphics_Offsets.cpp \
    Graphics_Question_Block.cpp \
    Object_Block.cpp \
    Palettes.cpp \
    ROM_Reader.cpp \
    Sprite_Block.cpp \
    Tile.cpp \
    main.cpp \
    Main_Window.cpp

HEADERS += \
    ../../../Level-Headed/SMB1/SMB1_Writer/Graphics_Offsets.h \
    Graphics_Question_Block.h \
    Main_Window.h \
    Object_Block.h \
    Palette.h \
    Palettes.h \
    ROM_Reader.h \
    Sprite_Block.h \
    Tile.h \
    Weather.h

FORMS += \
    Main_Window.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
