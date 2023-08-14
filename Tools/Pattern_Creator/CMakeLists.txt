cmake_minimum_required(VERSION 3.14)

project(Pattern_Creator LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Wdeprecated -Werror")

find_package(QT NAMES Qt6 COMPONENTS Core Gui Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Gui Widgets REQUIRED)

set(SOURCES
    ../../../Level-Headed/SMB1/SMB1_Writer/Graphics_Offsets.cpp
    Graphics_Question_Block.cpp
    Object_Block.cpp
    Palettes.cpp
    ROM_Reader.cpp
    Sprite_Block.cpp
    Tile.cpp
    main.cpp
    Main_Window.cpp
)

set(HEADERS
    ../../../Level-Headed/SMB1/SMB1_Writer/Graphics_Offsets.h
    Graphics_Question_Block.h
    Main_Window.h
    Object_Block.h
    Palette.h
    Palettes.h
    ROM_Reader.h
    Sprite_Block.h
    Tile.h
    Weather.h
)

set(FORMS
    Main_Window.ui
)

# Remove WIN32 if you want the console window
add_executable(${PROJECT_NAME} WIN32 ${SOURCES} ${HEADERS} ${FORMS})
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
