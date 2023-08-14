cmake_minimum_required(VERSION 3.14)

project(Palette_Tile_Importer LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Wdeprecated -Werror")

find_package(QT NAMES Qt6 COMPONENTS Core Gui Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Gui Widgets REQUIRED)

set(SOURCES
    ../../../Level-Headed/SMB1/SMB1_Writer/Graphics_Combiner.cpp
    ../../../Level-Headed/SMB1/SMB1_Writer/Graphics_Offsets.cpp
    ../../../Level-Headed/SMB1/SMB1_Writer/SMB1_Writer.cpp
    ../../../Level-Headed/SMB1/SMB1_Writer/Bowser_Bridge_Destroyer.cpp
    ../../../Level-Headed/SMB1/SMB1_Writer/Item_Buffer.cpp
    ../../../Level-Headed/SMB1/SMB1_Writer/Binary_Manipulator.cpp
    ../../../Level-Headed/SMB1/SMB1_Writer/Object_Buffer.cpp
    ../../../Level-Headed/SMB1/SMB1_Writer/Header_Writer.cpp
    ../../../Level-Headed/SMB1/SMB1_Writer/Enemy_Buffer.cpp
    ../../../Level-Headed/SMB1/SMB1_Writer/SMB1_Writer_Accessors.cpp
    ../../../Level-Headed/SMB1/SMB1_Writer/ROM_Handler.cpp
    ../../../Level-Headed/SMB1/SMB1_Writer/ROM_Checksum.cpp
    ../../../Level-Headed/SMB1/SMB1_Writer/Midpoint_Writer.cpp
    ../../../Level-Headed/SMB1/SMB1_Writer/Room_Order_Writer.cpp
    ../../../Level-Headed/SMB1/SMB1_Writer/Room_ID_Handler.cpp
    ../../../Level-Headed/SMB1/SMB1_Writer/Room_Address_Writer.cpp
    ../../../Level-Headed/SMB1/SMB1_Writer/Level_Offset.cpp
    ../../../Level-Headed/SMB1/SMB1_Writer/Enemy_Bytes_Tracker.cpp
    ../../../Level-Headed/SMB1/SMB1_Writer/Hacks.cpp
    ../../../Level-Headed/SMB1/SMB1_Writer/Music.cpp
    ../../../Level-Headed/SMB1/SMB1_Writer/Byte_Writer.cpp
    ../../../Level-Headed/SMB1/SMB1_Writer/Graphics.cpp
    ../../../Level-Headed/SMB1/SMB1_Writer/Palettes.cpp
    ../../../Level-Headed/SMB1/SMB1_Writer/Colors.cpp
    ../../../Level-Headed/SMB1/SMB1_Writer/Text.cpp
    ../../../Level-Headed/SMB1/SMB1_Writer/Sequential_Archive_Handler.cpp
    ../../../Level-Headed/SMB1/SMB1_Writer/Powerups.cpp
    ../../../Level-Headed/SMB1/SMB1_Writer/Sound.cpp
    ../../../C_Common_Code/Qt/Random/Random.cpp
    ../Palette_Color_Mover/Palette_Color_Mover.cpp
    main.cpp
)

set(HEADERS
    ../../../Level-Headed/SMB1/SMB1_Writer/Graphics_Combiner.h
    ../../../Level-Headed/SMB1/SMB1_Writer/Graphics_Offsets.h
    ../../../Level-Headed/SMB1/SMB1_Writer/SMB1_Writer.h
    ../../../Level-Headed/SMB1/SMB1_Writer/Bowser_Bridge_Destroyer.h
    ../../../Level-Headed/SMB1/SMB1_Writer/Item_Buffer.h
    ../../../Level-Headed/SMB1/SMB1_Writer/Binary_Manipulator.h
    ../../../Level-Headed/SMB1/SMB1_Writer/Object_Buffer.h
    ../../../Level-Headed/SMB1/SMB1_Writer/Header_Writer.h
    ../../../Level-Headed/SMB1/SMB1_Writer/Enemy_Buffer.h
    ../../../Level-Headed/SMB1/SMB1_Writer/ROM_Handler.h
    ../../../Level-Headed/SMB1/SMB1_Writer/ROM_Checksum.h
    ../../../Level-Headed/SMB1/SMB1_Writer/Midpoint_Writer.h
    ../../../Level-Headed/SMB1/SMB1_Writer/Room_Order_Writer.h
    ../../../Level-Headed/SMB1/SMB1_Writer/Room_ID_Handler.h
    ../../../Level-Headed/SMB1/SMB1_Writer/Room_Address_Writer.h
    ../../../Level-Headed/SMB1/SMB1_Writer/Level_Offset.h
    ../../../Level-Headed/SMB1/SMB1_Writer/Enemy_Bytes_Tracker.h
    ../../../Level-Headed/SMB1/SMB1_Writer/Hacks.h
    ../../../Level-Headed/SMB1/SMB1_Writer/Music.h
    ../../../Level-Headed/SMB1/SMB1_Writer/Byte_Writer.h
    ../../../Level-Headed/SMB1/SMB1_Writer/Graphics.h
    ../../../Level-Headed/SMB1/SMB1_Writer/Palettes.h
    ../../../Level-Headed/SMB1/SMB1_Writer/Color.h
    ../../../Level-Headed/SMB1/SMB1_Writer/Colors.h
    ../../../Level-Headed/SMB1/SMB1_Writer/Text.h
    ../../../Level-Headed/SMB1/SMB1_Writer/Sequential_Archive_Handler.h
    ../../../Level-Headed/SMB1/SMB1_Writer/Powerups.h
    ../../../Level-Headed/SMB1/SMB1_Writer/Sound.h
    ../../../C_Common_Code/Qt/Random/Random.h
    ../Palette_Color_Mover/Palette_Color_Mover.h
)

# Remove WIN32 if you want the console window
add_executable(${PROJECT_NAME} WIN32 ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME}
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets
)

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
