cmake_minimum_required(VERSION 3.14)

project(Level_Ripper LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Wdeprecated -Werror")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

set(SOURCES
    ../../../C_Common_Code/Qt/Text_Insertion_Buffer/Text_Insertion_Buffer.cpp
    ../../../C_Common_Code/Qt/Random/Random.cpp
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Bridge_Generator.cpp
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Castle_Generator.cpp
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Common_Pattern_Spawner.cpp
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Continuous_Enemies_Spawner.cpp
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/End_Spawner.cpp
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Enemy_Spawner.cpp
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Enemy_Buffer.cpp
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/First_Page_Handler.cpp
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Header_Writer.cpp
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Island_Generator.cpp
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Item_Spawner.cpp
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Item_Buffer.cpp
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Level_Crawler.cpp
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Level_Generator.cpp
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Level_Script_Modifier.cpp
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Level_Script_Parser.cpp
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Midpoint_Handler.cpp
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Object_Spawner.cpp
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Object_Buffer.cpp
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Pipe_Exit_Generator.cpp
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Pipe_Pointer_Buffer.cpp
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Powerup_Distributor.cpp
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Required_Enemy_Spawns.cpp
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/SMB1_Compliance_Generator.cpp
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/SMB1_Compliance_Map.cpp
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/SMB1_Compliance_Object_Parser.cpp
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Simple_Object_Spawner.cpp
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Standard_Overworld_Generator.cpp
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Underground_Generator.cpp
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Underwater_Generator.cpp
    Coordinates.cpp
    Enemy_Parser.cpp
    Object_Parser.cpp
    main.cpp
)

set(HEADERS
    ../../../C_Common_Code/Qt/Text_Insertion_Buffer/Text_Insertion_Buffer.h
    ../../../C_Common_Code/Qt/Random/Random.h
    ../../../Level-Headed/Level-Headed/Interpreter_Interface.h
    ../../../Level-Headed/SMB1/Common_SMB1_Files/Background.h
    ../../../Level-Headed/SMB1/Common_SMB1_Files/Background_String.h
    ../../../Level-Headed/SMB1/Common_SMB1_Files/Brick.h
    ../../../Level-Headed/SMB1/Common_SMB1_Files/Brick_String.h
    ../../../Level-Headed/SMB1/Common_SMB1_Files/Castle.h
    ../../../Level-Headed/SMB1/Common_SMB1_Files/Enemy_Item.h
    ../../../Level-Headed/SMB1/Common_SMB1_Files/Enemy_Item_String.h
    ../../../Level-Headed/SMB1/Common_SMB1_Files/Fix_Strings.h
    ../../../Level-Headed/SMB1/Common_SMB1_Files/Header_String.h
    ../../../Level-Headed/SMB1/Common_SMB1_Files/Level.h
    ../../../Level-Headed/SMB1/Common_SMB1_Files/Level_Attribute.h
    ../../../Level-Headed/SMB1/Common_SMB1_Files/Level_Attribute_String.h
    ../../../Level-Headed/SMB1/Common_SMB1_Files/Level_Compliment.h
    ../../../Level-Headed/SMB1/Common_SMB1_Files/Level_Compliment_String.h
    ../../../Level-Headed/SMB1/Common_SMB1_Files/Level_String.h
    ../../../Level-Headed/SMB1/Common_SMB1_Files/Level_Type.h
    ../../../Level-Headed/SMB1/Common_SMB1_Files/Level_Type_String.h
    ../../../Level-Headed/SMB1/Common_SMB1_Files/Object_Item.h
    ../../../Level-Headed/SMB1/Common_SMB1_Files/Object_Item_String.h
    ../../../Level-Headed/SMB1/Common_SMB1_Files/Scenery.h
    ../../../Level-Headed/SMB1/Common_SMB1_Files/Scenery_String.h
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Block_Data.h
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Bridge_Generator.h
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Buffer_Data.h
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Castle_Generator.h
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Common_Pattern_Spawner.h
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Continuous_Enemies_Spawner.h
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Difficulty.h
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/End_Pattern.h
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/End_Spawner.h
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Enemy_Spawner.h
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Enemy_Buffer.h
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Extra_Enemy_Args.h
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/First_Page_Handler.h
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Header_Writer.h
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Island_Generator.h
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Item_Spawner.h
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Item_Buffer.h
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Level_Crawler.h
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Level_Generator.h
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Level_Script_Modifier.h
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Level_Script_Parser.h
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Midpoint_Handler.h
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Object_Spawner.h
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Object_Buffer.h
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Physics.h
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Pipe_Exit_Generator.h
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Pipe_Pointer_Buffer.h
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Powerup_Distributor.h
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Required_Enemy_Spawns.h
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/SMB1_Compliance_Generator.h
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/SMB1_Compliance_Generator_Arguments.h
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/SMB1_Compliance_Generator_Interface.h
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/SMB1_Compliance_Map.h
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/SMB1_Compliance_Object_Parser.h
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/SMB1_Compliance_Parser_Arguments.h
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Simple_Object_Spawner.h
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Standard_Overworld_Generator.h
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Underground_Generator.h
    ../../../Level-Headed/SMB1/SMB1_Compliance_Generator/Underwater_Generator.h
    Coordinates.h
    Enemy_Parser.h
    Object_Parser.h
)

# Remove WIN32 if you want the console window
add_executable(${PROJECT_NAME} WIN32 ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
