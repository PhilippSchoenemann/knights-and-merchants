#ifndef KNIGHTS_AND_MERCHANTS_ARRAY_UNK_00_H
#define KNIGHTS_AND_MERCHANTS_ARRAY_UNK_00_H

#include "Array.h"

class ArrayUnk00Element
{
public:

    static bool isUsed(const ArrayUnk00Element & e);

    static void setUnused(ArrayUnk00Element & e);

    char i0;
    short i1;
    short i3;
    char i5;
    char i6;
    char i7;
    short i8;
};

class ArrayUnk00 : public Array<ArrayUnk00Element>
{
public:
    ArrayUnk00(const int maxSlots);

    ~ArrayUnk00();

    short unk1(const int p0, const char p4);

    short unk11(const short p0, const int p4);

};

#endif