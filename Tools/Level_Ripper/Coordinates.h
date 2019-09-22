#ifndef COORDINATES_H
#define COORDINATES_H

class Item_Writer;

class Coordinates {
public:
    Coordinates(Item_Writer *itemWriter);
    ~Coordinates() {}
    void Get_Coordinates(char coordinates, char object, int &x, int &y);

private:
    Item_Writer *itemWriter;
    int lastX;
};

#endif // COORDINATES_H
