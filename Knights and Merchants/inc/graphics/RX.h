#ifndef KNIGHTS_AND_MERCHANTS_GRAPHICS_RX_H
#define KNIGHTS_AND_MERCHANTS_GRAPHICS_RX_H

#include <string>

namespace knights_and_merchants
{
    namespace io
    {
        class FileIo;
    }

    namespace graphics
    {
        using knights_and_merchants::io::FileIo;

        class Bitmap;

        class RX
        {
        public:
            RX(const std::string & filePath);

            ~RX();

            [[nodiscard]]
            const Bitmap * getBitmap(int i) const;

            bool read(FileIo & fileIo);

        private:
            void unk123(int bitmapCount);

        public:
            Bitmap ** i0_bitmaps;
            int i4_bitmapCount;
        };
    }
}

#endif
