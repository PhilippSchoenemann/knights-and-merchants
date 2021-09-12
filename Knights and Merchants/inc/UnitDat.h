#ifndef KNIGHTS_AND_MERCHANTS_UNIT_DAT_H
#define KNIGHTS_AND_MERCHANTS_UNIT_DAT_H

#include "AnimationEntry.h"
#include "DefinedSounds.h"

namespace knights_and_merchants::io
{
    class FileIo;
}

class UnitDefineData
{
public:

    bool read(knights_and_merchants::io::FileIo & fileIO);

    short i0;
    short i2;

    short i8;
    short i10;
    short i12;
    short i14_clearUpRange;
    char i16;
    char i17;
    int i18;

    AnimationEntry i22[8][8];
    AnimationEntry i4502_troupFlagAnimations[8];
    DefinedSounds i7862;
};


class UnitDat
{
public:
    UnitDat(const char * filePath);

    AnimationEntry i0[224];
    UnitDefineData i15680[41];
};

#endif