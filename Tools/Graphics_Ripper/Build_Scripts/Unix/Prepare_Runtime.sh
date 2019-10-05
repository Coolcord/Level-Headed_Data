#!/bin/bash

MODE="Debug"
SOURCE_LOCATION="/home/cord/Documents/Source_Code"

echo "Installing plugins for Graphics Ripper..."
mkdir -p "$SOURCE_LOCATION"/Level-Headed_Data/Tools/build-Graphics_Ripper-Desktop/"$MODE"/Plugins
cp -rf "$SOURCE_LOCATION"/Hexagon/build-Hexagon-Desktop-"$MODE"/libHexagon.so "$SOURCE_LOCATION"/Level-Headed_Data/Tools/build-Graphics_Ripper-Desktop/"$MODE"/Plugins/Hexagon.so

echo "Runtime Environment Prepared!"
exit 0

