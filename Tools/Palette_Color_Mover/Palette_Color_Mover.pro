QT += core gui widgets

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
    ../../../Level-Headed/SMB1/SMB1_Writer/SMB1_Writer.cpp \
    ../../../Level-Headed/SMB1/SMB1_Writer/Bowser_Bridge_Destroyer.cpp \
    ../../../Level-Headed/SMB1/SMB1_Writer/Item_Writer.cpp \
    ../../../Level-Headed/SMB1/SMB1_Writer/Binary_Manipulator.cpp \
    ../../../Level-Headed/SMB1/SMB1_Writer/Object_Writer.cpp \
    ../../../Level-Headed/SMB1/SMB1_Writer/Header_Writer.cpp \
    ../../../Level-Headed/SMB1/SMB1_Writer/Enemy_Writer.cpp \
    ../../../Level-Headed/SMB1/SMB1_Writer/SMB1_Writer_Accessors.cpp \
    ../../../Level-Headed/SMB1/SMB1_Writer/ROM_Handler.cpp \
    ../../../Level-Headed/SMB1/SMB1_Writer/ROM_Checksum.cpp \
    ../../../Level-Headed/SMB1/SMB1_Writer/Midpoint_Writer.cpp \
    ../../../Level-Headed/SMB1/SMB1_Writer/Room_Order_Writer.cpp \
    ../../../Level-Headed/SMB1/SMB1_Writer/Room_ID_Handler.cpp \
    ../../../Level-Headed/SMB1/SMB1_Writer/Room_Address_Writer.cpp \
    ../../../Level-Headed/SMB1/SMB1_Writer/Level_Offset.cpp \
    ../../../Level-Headed/SMB1/SMB1_Writer/Enemy_Bytes_Tracker.cpp \
    ../../../Level-Headed/SMB1/SMB1_Writer/Hacks.cpp \
    ../../../Level-Headed/SMB1/SMB1_Writer/Music.cpp \
    ../../../Level-Headed/SMB1/SMB1_Writer/Byte_Writer.cpp \
    ../../../Level-Headed/SMB1/SMB1_Writer/Graphics.cpp \
    ../../../Level-Headed/SMB1/SMB1_Writer/Palettes.cpp \
    ../../../Level-Headed/SMB1/SMB1_Writer/Colors.cpp \
    ../../../Level-Headed/SMB1/SMB1_Writer/Text.cpp \
    ../../../Level-Headed/SMB1/SMB1_Writer/Sequential_Archive_Handler.cpp \
    ../../../Level-Headed/SMB1/SMB1_Writer/Powerups.cpp \
    ../../../Level-Headed/SMB1/SMB1_Writer/Sound.cpp \
    ../../../Level-Headed//Common_Files/Random.cpp \
    Palette_Color_Mover.cpp \
    main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    ../../../Level-Headed/SMB1/SMB1_Writer/SMB1_Writer.h \
    ../../../Level-Headed/SMB1/SMB1_Writer/Bowser_Bridge_Destroyer.h \
    ../../../Level-Headed/SMB1/SMB1_Writer/Item_Writer.h \
    ../../../Level-Headed/SMB1/SMB1_Writer/Binary_Manipulator.h \
    ../../../Level-Headed/SMB1/SMB1_Writer/Object_Writer.h \
    ../../../Level-Headed/SMB1/SMB1_Writer/Header_Writer.h \
    ../../../Level-Headed/SMB1/SMB1_Writer/Enemy_Writer.h \
    ../../../Level-Headed/SMB1/SMB1_Writer/ROM_Handler.h \
    ../../../Level-Headed/SMB1/SMB1_Writer/ROM_Checksum.h \
    ../../../Level-Headed/SMB1/SMB1_Writer/Midpoint_Writer.h \
    ../../../Level-Headed/SMB1/SMB1_Writer/Room_Order_Writer.h \
    ../../../Level-Headed/SMB1/SMB1_Writer/Room_ID_Handler.h \
    ../../../Level-Headed/SMB1/SMB1_Writer/Room_Address_Writer.h \
    ../../../Level-Headed/SMB1/SMB1_Writer/Level_Offset.h \
    ../../../Level-Headed/SMB1/SMB1_Writer/Enemy_Bytes_Tracker.h \
    ../../../Level-Headed/SMB1/SMB1_Writer/Hacks.h \
    ../../../Level-Headed/SMB1/SMB1_Writer/Music.h \
    ../../../Level-Headed/SMB1/SMB1_Writer/Byte_Writer.h \
    ../../../Level-Headed/SMB1/SMB1_Writer/Graphics.h \
    ../../../Level-Headed/SMB1/SMB1_Writer/Palettes.h \
    ../../../Level-Headed/SMB1/SMB1_Writer/Color.h \
    ../../../Level-Headed/SMB1/SMB1_Writer/Colors.h \
    ../../../Level-Headed/SMB1/SMB1_Writer/Text.h \
    ../../../Level-Headed/SMB1/SMB1_Writer/Sequential_Archive_Handler.h \
    ../../../Level-Headed/SMB1/SMB1_Writer/Powerups.h \
    ../../../Level-Headed/SMB1/SMB1_Writer/Sound.h \
    ../../../Level-Headed//Common_Files/Random.h \
    Palette_Color_Mover.h \
    Sprites.h
