#ifndef PALETTES_H
#define PALETTES_H

#include "Palette.h"
#include "Weather.h"
#include <QColor>

class ROM_Reader;

class Palettes {
public:
    Palettes(ROM_Reader *romReader);
    ~Palettes();
    Palette Get_Overworld_Palette(Weather::Weather weather, bool mushroom);
    Palette Get_Underground_Palette(Weather::Weather weather, bool mushroom);
    Palette Get_Underwater_Palette(Weather::Weather weather, bool mushroom);
    Palette Get_Castle_Palette(Weather::Weather weather, bool mushroom);

private:
    QColor Get_Color_From_Byte(char byte);

    ROM_Reader *romReader;
};

#endif // PALETTES_H
