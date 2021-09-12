#ifndef KNIGHTS_AND_MERCHANTS_SELECTION_H
#define KNIGHTS_AND_MERCHANTS_SELECTION_H

class Selection
{
public:
    Selection(short width, short height);

    void move(int dx, int dy);

    void setSize(short width, short height);

    void setPosition(int x, int y);

    void resetPosition();

private:

    void unk1();

    short i0_width;
    short i2_height;
    int i4_x;
    int i8_y;
    int i12;
    int i16;
};

#endif