#ifndef KNIGHTS_AND_MERCHANTS_GRAPHICS_BITMAP_H
#define KNIGHTS_AND_MERCHANTS_GRAPHICS_BITMAP_H

namespace knights_and_merchants::io
{
    class FileIo;
}

namespace knights_and_merchants::graphics
{
    class DrawableSurface;

    class Bitmap
    {
    public:
        Bitmap() = default;

        Bitmap(short width, short height, const unsigned char * data);

        ~Bitmap();

        void draw(DrawableSurface & surface, int x, int y) const;

        void drawRemapped(DrawableSurface & surface, int x, int y, const unsigned char * table) const;

        void drawResized(DrawableSurface & surface, int x, int y, int width, int height) const;

        void drawSingleColored(DrawableSurface & surface, int x, int y, unsigned char color) const;

        void extractFromSurface(const DrawableSurface & surface, int x, int y);

        void read(knights_and_merchants::io::FileIo & fileIO);

        void unk1(DrawableSurface & p0, int p4, int p8, int p12) const;

        void unk2(DrawableSurface & surface, int x, int y, const unsigned char * table, short height);

        short i0_width;
        short i2_height;
        int i4;
        int i8;
        unsigned char * i12_data;

    private:
        bool unk12345(const DrawableSurface & surface, int & x, int & y, short & width, short & height) const;


        void reset();
    };
}

#endif
