@ECHO OFF
COLOR 0A
C:
CD "\Program Files (x86)\Coolcord\SAM"
SAM.exe --pack "F:\Documents\Source_Code\Level-Headed_Data\Level_Scripts\Super Mario Bros. 1 (Original Levels without Castle Loops)"
RENAME "F:\Documents\Source_Code\Level-Headed_Data\Level_Scripts\Super Mario Bros. 1 (Original Levels without Castle Loops).sa" "Super Mario Bros. 1 (Original Levels without Castle Loops).lvls"
DELETE "F:\Documents\Source_Code\Level-Headed\build-Level-Headed-Desktop_Qt_5_12_2_MinGW_32_bit-Debug\debug\Levels\SMB1\Super Mario Bros. 1 (Original Levels without Castle Loops).lvls"
MOVE "F:\Documents\Source_Code\Level-Headed_Data\Level_Scripts\Super Mario Bros. 1 (Original Levels without Castle Loops).lvls" "F:\Documents\Source_Code\Level-Headed\build-Level-Headed-Desktop_Qt_5_12_2_MinGW_32_bit-Debug\debug\Levels\SMB1\Super Mario Bros. 1 (Original Levels without Castle Loops).lvls"
