QT += core gui widgets

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        ../../../Level-Headed/SMB1/SMB1_Writer/Graphics_Combiner.cpp \
        ../../../Level-Headed/SMB1/SMB1_Writer/Graphics_Offsets.cpp \
        ../../../Level-Headed/SMB1/SMB1_Writer/SMB1_Writer.cpp \
        ../../../Level-Headed/SMB1/SMB1_Writer/Bowser_Bridge_Destroyer.cpp \
        ../../../Level-Headed/SMB1/SMB1_Writer/Item_Buffer.cpp \
        ../../../Level-Headed/SMB1/SMB1_Writer/Binary_Manipulator.cpp \
        ../../../Level-Headed/SMB1/SMB1_Writer/Object_Buffer.cpp \
        ../../../Level-Headed/SMB1/SMB1_Writer/Header_Writer.cpp \
        ../../../Level-Headed/SMB1/SMB1_Writer/Enemy_Buffer.cpp \
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
        ../../../C_Common_Code/Qt/Random/Random.cpp \
        ../Palette_Color_Mover/Palette_Color_Mover.cpp \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    ../../../Level-Headed/SMB1/SMB1_Writer/Graphics_Combiner.h \
    ../../../Level-Headed/SMB1/SMB1_Writer/Graphics_Offsets.h \
    ../../../Level-Headed/SMB1/SMB1_Writer/SMB1_Writer.h \
    ../../../Level-Headed/SMB1/SMB1_Writer/Bowser_Bridge_Destroyer.h \
    ../../../Level-Headed/SMB1/SMB1_Writer/Item_Buffer.h \
    ../../../Level-Headed/SMB1/SMB1_Writer/Binary_Manipulator.h \
    ../../../Level-Headed/SMB1/SMB1_Writer/Object_Buffer.h \
    ../../../Level-Headed/SMB1/SMB1_Writer/Header_Writer.h \
    ../../../Level-Headed/SMB1/SMB1_Writer/Enemy_Buffer.h \
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
    ../../../C_Common_Code/Qt/Random/Random.h \
    ../Palette_Color_Mover/Palette_Color_Mover.h
