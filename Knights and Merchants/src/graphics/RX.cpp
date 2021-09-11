#include "graphics/RX.h"

#include "io/FileIo.h"
#include "engine/Bitmap.h"

using std::string;

namespace knights_and_merchants::graphics
{
    RX::RX(const string & filePath)
            : i0_bitmaps { }, i4_bitmapCount { }
    {
        FileIo fileIo { filePath };
        read(fileIo);
    }

    RX::~RX()
    {
        for (auto i = 0; i < i4_bitmapCount; ++i)
            delete i0_bitmaps[i];

        delete i0_bitmaps;
    }

    const Bitmap * RX::getBitmap(const int i) const
    {
        return i < i4_bitmapCount ? i0_bitmaps[i] : nullptr;
    }

    bool RX::read(FileIo & fileIO)
    {
        int bitmapCount;
        fileIO.read(&bitmapCount, 4);

        unk123(bitmapCount);

        auto * const available = new unsigned char[i4_bitmapCount];
        fileIO.read(available, i4_bitmapCount);

        for (int i = 0; i < i4_bitmapCount; ++i) {
            if (available[i] == 1) {
                i0_bitmaps[i] = new Bitmap();
                i0_bitmaps[i]->read(fileIO);
            }
        }

        delete[] available;
        return true;
    }

    void RX::unk123(const int bitmapCount)
    {
        i0_bitmaps = new Bitmap * [bitmapCount] { };
        i4_bitmapCount = bitmapCount;
    }

}
