#ifndef KNIGHTS_AND_MERCHANTS_GRAPHICS_RX_H
#define KNIGHTS_AND_MERCHANTS_GRAPHICS_RX_H

namespace knights_and_merchants
{
    namespace engine
    {
        class Bitmap;
    }

    namespace io
    {
        class FileIo;
    }

    namespace graphics
    {
        using knights_and_merchants::engine::Bitmap;
        using knights_and_merchants::io::FileIo;

        class RX
        {
        public:
            RX(const char * filePath);
            ~RX();

            Bitmap * getBitmap(int i);

            bool read(FileIo & fileIo);
            void unk123(int p0);
            void reset();


            Bitmap ** i0;
            int i4;
        };
    }
}

#endif
