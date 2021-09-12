#ifndef KNIGHTS_AND_MERCHANTS_DEFINED_SOUNDS_H
#define KNIGHTS_AND_MERCHANTS_DEFINED_SOUNDS_H

namespace knights_and_merchants::io
{
    class FileIo;
}

class DefinedSounds
{
public:
    char i0[12];
    short i12[12];

    DefinedSounds();

    char getSound(short p0);

    bool read(knights_and_merchants::io::FileIo & fileIO);

};

#endif