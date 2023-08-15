cmake_minimum_required(VERSION 3.14)

project(Graphics_Ripper LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Wdeprecated -Werror")

find_package(Qt6 REQUIRED COMPONENTS Core)

set(SOURCES
    ../../../Hexagon/Hexagon/Value_Manipulator.cpp
    ../../../Level-Headed/SMB1/SMB1_Writer/Graphics_Offsets.cpp
    Duplicate_Remover.cpp
    Graphics_Ripper.cpp
    main.cpp
)

set(HEADERS
    ../../../Hexagon/Hexagon/Hexagon_Interface.h
    ../../../Hexagon/Hexagon/Patch_Strings.h
    ../../../Hexagon/Hexagon/Value_Manipulator.h
    ../../../Hexagon/Hexagon_GUI/Common_Strings.h
    ../../../Level-Headed/SMB1/Common_SMB1_Files/Fix_Strings.h
    ../../../Level-Headed/SMB1/SMB1_Writer/Graphics_Offsets.h
    Duplicate_Remover.h
    Graphics_Ripper.h
)

# Remove WIN32 if you want the console window
add_executable(${PROJECT_NAME} WIN32 ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
)

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
