#ifndef COORDINATES_H
#define COORDINATES_H

class Object_Writer;

class Coordinates {
public:
    Coordinates(Object_Writer *objectWriter);
    ~Coordinates() {}
    void Get_Coordinates(char coordinates, char object, int &x, int &y);

private:
    Object_Writer *objectWriter;
    int lastX;
};

#endif // COORDINATES_H
