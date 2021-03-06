#ifndef OBJECT_PARSER_H
#define OBJECT_PARSER_H

#include "../../../Level-Headed/SMB1/SMB1_Compliance_Generator/SMB1_Compliance_Generator_Arguments.h"
#include <QTextStream>

class Coordinates;
class Object_Buffer;

class Object_Parser {
public:
    Object_Parser(int numBytesLeft, SMB1_Compliance_Generator_Arguments *args);
    ~Object_Parser();
    bool At_End(char coordinates);
    bool Parse_Object(char coordinates, char object, Level_Type::Level_Type levelType);

private:
    bool Parse_B_Object(int x, int y, char object);
    bool Parse_C_Object(int x, char object);
    bool Parse_D_Object(int x, char object, Level_Type::Level_Type levelType);
    bool Parse_E_Object(int x, char object);
    bool Parse_F_Object(int x, char object);

    Object_Buffer *objectWriter;
    Coordinates *coordinates;
    SMB1_Compliance_Generator_Arguments *args;
};

#endif // OBJECT_PARSER_H
