#ifndef KNIGHTS_AND_MERCHANTS_SOUND_H
#define KNIGHTS_AND_MERCHANTS_SOUND_H

namespace knights_and_merchants::io
{
    class FileIo;
}

class Sound
{
public:

    static bool isUsed(const Sound & p0);

    static void setUnused(Sound & p0);

    int getVolume();

    int i0_frequency;
    int i4;
    int i8;
    int i12;
    short i16;
    short i18;
    int i20;
    short i24;

    void read(knights_and_merchants::io::FileIo & fileIO);

};

#endif