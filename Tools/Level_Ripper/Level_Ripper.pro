QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

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
        ../../../C_Common_Code/Qt/Text_Insertion_Buffer/Text_Insertion_Buffer.cpp \
        ../../../Level-Headed/Common_Files/Random.cpp \
        ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Bridge_Generator.cpp \
        ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Castle_Generator.cpp \
        ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Common_Pattern_Spawner.cpp \
        ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Continuous_Enemies_Spawner.cpp \
        ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/End_Spawner.cpp \
        ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Enemy_Spawner.cpp \
        ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Enemy_Buffer.cpp \
        ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/First_Page_Handler.cpp \
        ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Header_Writer.cpp \
        ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Island_Generator.cpp \
        ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Item_Spawner.cpp \
        ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Item_Buffer.cpp \
        ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Level_Crawler.cpp \
        ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Level_Generator.cpp \
        ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Midpoint_Handler.cpp \
        ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Object_Spawner.cpp \
        ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Object_Buffer.cpp \
        ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Pipe_Exit_Generator.cpp \
        ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Pipe_Pointer_Buffer.cpp \
        ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Required_Enemy_Spawns.cpp \
        ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/SMB1_Compliance_Generator.cpp \
        ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/SMB1_Compliance_Map.cpp \
        ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/SMB1_Compliance_Object_Parser.cpp \
        ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Simple_Object_Spawner.cpp \
        ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Standard_Overworld_Generator.cpp \
        ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Underground_Generator.cpp \
        ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Underwater_Generator.cpp \
        Coordinates.cpp \
        Enemy_Parser.cpp \
        Object_Parser.cpp \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    ../../../C_Common_Code/Qt/Text_Insertion_Buffer/Text_Insertion_Buffer.h \
    ../../../Level-Headed/Common_Files/Random.h \
    ../../../Level-Headed/Level-Headed/Interpreter_Interface.h \
    ../../../Level-Headed/SMB1/Common_SMB1_Files/Background.h \
    ../../../Level-Headed/SMB1/Common_SMB1_Files/Background_String.h \
    ../../../Level-Headed/SMB1/Common_SMB1_Files/Brick.h \
    ../../../Level-Headed/SMB1/Common_SMB1_Files/Brick_String.h \
    ../../../Level-Headed/SMB1/Common_SMB1_Files/Castle.h \
    ../../../Level-Headed/SMB1/Common_SMB1_Files/Enemy_Item.h \
    ../../../Level-Headed/SMB1/Common_SMB1_Files/Enemy_Item_String.h \
    ../../../Level-Headed/SMB1/Common_SMB1_Files/Fix_Strings.h \
    ../../../Level-Headed/SMB1/Common_SMB1_Files/Header_String.h \
    ../../../Level-Headed/SMB1/Common_SMB1_Files/Level.h \
    ../../../Level-Headed/SMB1/Common_SMB1_Files/Level_Attribute.h \
    ../../../Level-Headed/SMB1/Common_SMB1_Files/Level_Attribute_String.h \
    ../../../Level-Headed/SMB1/Common_SMB1_Files/Level_Compliment.h \
    ../../../Level-Headed/SMB1/Common_SMB1_Files/Level_Compliment_String.h \
    ../../../Level-Headed/SMB1/Common_SMB1_Files/Level_String.h \
    ../../../Level-Headed/SMB1/Common_SMB1_Files/Level_Type.h \
    ../../../Level-Headed/SMB1/Common_SMB1_Files/Level_Type_String.h \
    ../../../Level-Headed/SMB1/Common_SMB1_Files/Object_Item.h \
    ../../../Level-Headed/SMB1/Common_SMB1_Files/Object_Item_String.h \
    ../../../Level-Headed/SMB1/Common_SMB1_Files/Scenery.h \
    ../../../Level-Headed/SMB1/Common_SMB1_Files/Scenery_String.h \
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Bridge_Generator.h \
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Castle_Generator.h \
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Common_Pattern_Spawner.h \
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Continuous_Enemies_Spawner.h \
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Difficulty.h \
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/End_Pattern.h \
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/End_Spawner.h \
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Enemy_Buffer_Data.h \
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Enemy_Spawner.h \
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Enemy_Buffer.h \
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Extra_Enemy_Args.h \
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/First_Page_Handler.h \
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Header_Writer.h \
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Island_Generator.h \
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Item_Spawner.h \
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Item_Buffer.h \
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Level_Crawler.h \
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Level_Generator.h \
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Midpoint_Handler.h \
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Object_Buffer_Data.h \
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Object_Spawner.h \
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Object_Buffer.h \
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Physics.h \
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Pipe_Exit_Generator.h \
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Pipe_Pointer_Buffer.h \
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Required_Enemy_Spawns.h \
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/SMB1_Compliance_Generator.h \
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/SMB1_Compliance_Generator_Arguments.h \
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/SMB1_Compliance_Generator_Interface.h \
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/SMB1_Compliance_Map.h \
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/SMB1_Compliance_Object_Parser.h \
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Simple_Object_Spawner.h \
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Standard_Overworld_Generator.h \
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Underground_Generator.h \
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Underwater_Generator.h \
    Coordinates.h \
    Enemy_Parser.h \
    Object_Parser.h
