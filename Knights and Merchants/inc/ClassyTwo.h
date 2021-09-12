#ifndef KNIGHTS_AND_MERCHANTS_CLASSY_TWO_H
#define KNIGHTS_AND_MERCHANTS_CLASSY_TWO_H

class ClassyTwo
{
public:
    ClassyTwo(int p0, int p4, unsigned char p8, unsigned char p12);

    void setPosition(unsigned char x, unsigned char y);

    bool move(char direction);

    bool moveOpposite(char direction);

    void saveCurrentPosition();

    void restoreSavedPosition();

    bool isNeighbor(unsigned char x, unsigned char y);

    char unk7(unsigned char x, unsigned char y);

    unsigned char i0_x;
    unsigned char i1_y;
    int i2_maxX;
    int i6_maxY;
    unsigned char i10_savedX;
    unsigned char i11_savedY;
};

#endif