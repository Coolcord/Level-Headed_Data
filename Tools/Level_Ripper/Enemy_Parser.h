#ifndef ENEMY_PARSER_H
#define ENEMY_PARSER_H

#include "../../../Level-Headed/SMB1/SMB1_Compliance_Generator/SMB1_Compliance_Generator_Arguments.h"
#include <QTextStream>

class Coordinates;
class Enemy_Buffer;
class Object_Buffer;
class Pipe_Pointer_Buffer;

class Enemy_Parser {
public:
    Enemy_Parser(int numBytesLeft, SMB1_Compliance_Generator_Arguments *args);
    ~Enemy_Parser();
    bool At_End(char coordinates);
    bool Is_Pipe_Pointer(char coordinates, char enemy);
    bool Parse_Enemy(char coordinates, char enemy);
    bool Parse_Pipe_Pointer(char coordinates, char levelSlot, char page);

private:
    Coordinates *coordinates;
    Object_Buffer *objects;
    Enemy_Buffer *enemies;
    Pipe_Pointer_Buffer *pipePointerWriter;
    SMB1_Compliance_Generator_Arguments *args;
    bool lastWasPageChange;
};

#endif // ENEMY_PARSER_H
