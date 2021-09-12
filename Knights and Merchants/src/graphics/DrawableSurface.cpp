#include "graphics/DrawableSurface.h"
#include "utilities/Rect.h"

namespace knights_and_merchants::graphics {

    void DrawableSurface::fillRectangle(Rect& rectangle, unsigned char p4)
    {
        if (rectangle.bottom > i2_height)
            rectangle.bottom = i2_height;

        if (rectangle.right > i0_width)
            rectangle.right = i0_width;

        int width = rectangle.right - rectangle.left;
        int height = rectangle.bottom - rectangle.top;

        if (width != 0 && height != 0) {
            unsigned char* surfaceAddress = i6_surface + rectangle.left + rectangle.top * i4_pitch;
            int var10 = i4_pitch - width;

            while (height--) {
                int x = width;
                while (x--)
                    *surfaceAddress++ = p4;

                surfaceAddress += var10;
            }
        }
    }

    void DrawableSurface::remapRectangle(const Rect& rectangle, unsigned char* p4)
    {
        int width = rectangle.right - rectangle.left;
        int height = rectangle.bottom - rectangle.top;

        unsigned char* surfaceAddress = i6_surface + rectangle.left + i4_pitch * rectangle.top;

        int var10 = i4_pitch - width;

        while (height--) {
            int w = width;
            while (w--) {
                *surfaceAddress = p4[*surfaceAddress];
                ++surfaceAddress;
            }
            surfaceAddress += var10;
        }
    }

    void DrawableSurface::remapRow(int x1, int x2, int y, unsigned char* p12)
    {
        unsigned char* surfaceAddress = i6_surface + x1 + y * i4_pitch;

        short width = x2 - x1;
        for (int i = 0; i < width; ++i, ++surfaceAddress)
            *surfaceAddress = p12[*surfaceAddress];
    }

    void DrawableSurface::remapColumn(int y1, int y2, int x, unsigned char* p12)
    {
        unsigned char* surfaceAddress = i6_surface + x + y1 * i4_pitch;

        short height = y2 - y1;
        for (int i = 0; i < height; ++i, surfaceAddress += i4_pitch)
            *surfaceAddress = p12[*surfaceAddress];
    }

    void DrawableSurface::fillRow(int x1, int x2, int y, int p12) {
        unsigned char* surfaceAddress = i6_surface + x1 + i4_pitch * y;

        for (int i = x1; i < x2; ++i)
            *surfaceAddress++ = p12;
    }

    void DrawableSurface::fillColumn(int y1, int y2, int x, int p12)
    {
        unsigned char* surfaceAddress = i6_surface + x + y1 * i4_pitch;

        for (int i = y1; i < y2; ++i) {
            *surfaceAddress = p12;
            surfaceAddress += i4_pitch;
        }
    }

    void DrawableSurface::unk1(const Rect& p0, int p4)
    {
        fillRow(p0.left, p0.right, p0.top, p4);
        fillRow(p0.left, p0.right - 1, p0.bottom - 1, p4);

        fillColumn(p0.top, p0.bottom, p0.left, p4);
        fillColumn(p0.top, p0.bottom, p0.right - 1, p4);
    }

}