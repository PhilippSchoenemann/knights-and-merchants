#ifndef KNIGHTS_AND_MERCHANTS_GRAPHICS_FONT_H
#define KNIGHTS_AND_MERCHANTS_GRAPHICS_FONT_H

namespace knights_and_merchants
{
    namespace engine
    {
        class Bitmap;
        class DrawableSurface;
    }

    namespace io
    {
        class FileIo;
    }

    namespace graphics
    {
        using knights_and_merchants::engine::Bitmap;
        using knights_and_merchants::engine::DrawableSurface;
        using knights_and_merchants::io::FileIo;

        class Font
        {
        public:
            explicit Font(const char* fileName);

            Font(short height, int tracking, short spaceWidth);
            // TODO: Implement copy and move ctors and =.
            ~Font();

            void reset();

            bool read(FileIo & fileIO);

            short someUnk(int p0);

            int calculateTextWidth(char * p0, int p4, int p8);

            // TODO: Transform to overloads.
            void drawString(DrawableSurface & p0, int p4, int p8, const char * p12);
            void drawStringEx(DrawableSurface & p0, int p4, int p8, const char * p12, short p16, short p20, int p24);
            void drawStringExEx(DrawableSurface & p0, int p4, int p8, const char * p12, short p16);

            short unk2(int p0, char * p4);

            short unk1();

            short i0_spaceWidth;
            short i2_height;
            int i4_tracking;
            Bitmap * i8[256];
        };
    }
}

#endif
