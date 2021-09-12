#ifndef KNIGHTS_AND_MERCHANTS_ARRAY_UNK_MAP_H
#define KNIGHTS_AND_MERCHANTS_ARRAY_UNK_MAP_H

#include "Array.h"

namespace knights_and_merchants::io
{
    class FileIo;
}

struct MapElem
{
    int i0;
    int i4;
    int i8;
    int i12;
    char i16;

    void read(knights_and_merchants::io::FileIo & fileIO);

    static bool isUsed(const MapElem & p0)
    {
        return p0.i16 != -1;
    }

    static void setUnused(MapElem & p0)
    {
        p0.i16 = -1;
    }
};

class ArrayUnkMap : public Array<MapElem>
{
public:
    ArrayUnkMap(const int p0);

    ~ArrayUnkMap();

    void reset();

    bool read(knights_and_merchants::io::FileIo & fileIO);

    short i32;
};

#endif
