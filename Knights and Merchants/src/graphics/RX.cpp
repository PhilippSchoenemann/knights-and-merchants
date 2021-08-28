#include "graphics/RX.h"

#include "io/FileIo.h"
#include "engine/Bitmap.h"

namespace knights_and_merchants::graphics
{
    RX::RX(const char * const filePath)
    {
        FileIo fileIo { filePath };
        read(fileIo);
    }

    RX::~RX()
    {
        for (auto i = 0; i < i4; ++i)
            if (i0[i] != nullptr)
                delete i0[i];

        delete i0;
        reset();
    }

    Bitmap * RX::getBitmap(int i)
    {
        return (i < i4) ? i0[i] : nullptr;
    }

    bool RX::read(FileIo & fileIO)
    {
        int var;

        fileIO.read(&var, 4);
        //if (!fileIO.read(&var, 4)) TODO: Changed bool to exception
        //    return false;

        unk123(var);

        auto * const available = new unsigned char[i4];
        fileIO.read(available, i4);

        for (int i = 0; i < i4; ++i) {
            if (available[i] == 1) {
                i0[i] = new Bitmap();
                i0[i]->read(fileIO);
            }
        }

        delete[] available;
        return true;
    }

    void RX::unk123(int p0)
    {
        i4 = p0;
        reset();
        i0 = new Bitmap *[p0];

        if (i0 != nullptr) {
            for (int i = 0; i < i4; ++i) {
                i0[i] = nullptr;
            }
        }
    }

    void RX::reset()
    {
        i0 = nullptr;
    }
}
