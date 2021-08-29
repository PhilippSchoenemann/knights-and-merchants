#ifndef KNIGHTS_AND_MERCHANTS_ENGINE_UNK_GRAPHICS_CLASS_H
#define KNIGHTS_AND_MERCHANTS_ENGINE_UNK_GRAPHICS_CLASS_H

#include "UnkClass5.h"
#include "utilities/Rect.h"

using knights_and_merchants::utilities::Rect;

namespace knights_and_merchants::engine
{
    class UnkGraphicsClass
    {
    public:
        UnkGraphicsClass(HWND p0, const Rect & p4);

        UnkGraphicsClass(const UnkGraphicsClass &) = delete;
        UnkGraphicsClass(UnkGraphicsClass &&) = delete;

        UnkGraphicsClass & operator=(const UnkGraphicsClass &) = delete;
        UnkGraphicsClass & operator=(UnkGraphicsClass &&) = delete;

        ~UnkGraphicsClass();

        void unk();

        bool unk100();
        bool unk200();
        bool setPalette(const UnkClass5 & p0);
        bool draw();


        void * i64;

    private:
        void reset();

        HBITMAP i0;
        HGDIOBJ i4;
        HDC i8;
        HDC i12;
        HWND i16;
        BITMAPINFO i20;
        RGBQUAD i68[256];
        HPALETTE i1092;
        HPALETTE i1096;
        Rect i1100;
    };
}

#endif
