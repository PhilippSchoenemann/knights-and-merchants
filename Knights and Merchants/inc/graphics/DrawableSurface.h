#ifndef KNIGHTS_AND_MERCHANTS_ENGINE_DRAWABLE_SURFACE_H
#define KNIGHTS_AND_MERCHANTS_ENGINE_DRAWABLE_SURFACE_H

namespace knights_and_merchants::utilities
{
    class Rect;
}

namespace knights_and_merchants::graphics
{
    class DrawableSurface
    {
        typedef utilities::Rect Rect;

    public:
        short i0_width;
        short i2_height;
        short i4_pitch;
        unsigned char * i6_surface;

        void fillRectangle(Rect & rectangle, unsigned char p4);
        void remapRectangle(const Rect & rectangle, unsigned char * p4);
        void remapRow(int x1, int x2, int y, unsigned char * p12);
        void remapColumn(int y1, int y2, int x, unsigned char * p12);

        void fillRow(int x1, int x2, int y, int p12);
        void fillColumn(int y1, int y2, int x, int p12);

        void unk1(const Rect & p0, int p4);
    };
}

#endif
