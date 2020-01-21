#ifndef COORDINATES_H
#define COORDINATES_H

class Item_Buffer;

class Coordinates {
public:
    Coordinates(Item_Buffer *itemWriter);
    ~Coordinates() {}
    void Set_Last_Was_Group(bool lastWasGroup);
    void Get_Coordinates(char coordinates, char object, int &x, int &y, bool peek);

private:
    Item_Buffer *itemWriter;
    bool lastWasGroup;
};

#endif // COORDINATES_H
