@ECHO OFF
COLOR 0A
C:
CD "\Program Files (x86)\Coolcord\SAM"
SAM.exe --pack "F:\Documents\Source_Code\Level-Headed_Data\Level_Scripts\SMB1"
RENAME "F:\Documents\Source_Code\Level-Headed_Data\Level_Scripts\SMB1.sa" SMB1.lvls
DELETE "F:\Documents\Source_Code\Level-Headed\build-Level-Headed-Desktop_Qt_5_12_2_MinGW_32_bit-Debug\debug\Levels\SMB1\SMB1.lvls"
MOVE "F:\Documents\Source_Code\Level-Headed_Data\Level_Scripts\SMB1.lvls" "F:\Documents\Source_Code\Level-Headed\build-Level-Headed-Desktop_Qt_5_12_2_MinGW_32_bit-Debug\debug\Levels\SMB1\SMB1.lvls"
