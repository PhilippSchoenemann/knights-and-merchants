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
        UnkGraphicsClass(HWND hWnd, const Rect & canvasRect) noexcept;

        UnkGraphicsClass(const UnkGraphicsClass &) = delete;
        UnkGraphicsClass(UnkGraphicsClass &&) = delete;

        UnkGraphicsClass & operator=(const UnkGraphicsClass &) = delete;
        UnkGraphicsClass & operator=(UnkGraphicsClass &&) = delete;

        ~UnkGraphicsClass() noexcept;

        void setDisplayMode(int width, int height) noexcept;

        void unk() const noexcept;

        bool unk100() const noexcept;
        bool unk200() const noexcept;
        bool setPalette(const UnkClass5 & p0) noexcept;
        bool draw() const noexcept;
        bool unk222(int width, int height) const noexcept;

        void * i64;

    private:
        void reset() noexcept;

        HBITMAP i0;
        HGDIOBJ i4;
        HDC i8_memoryDC;
        HDC i12_windowDC;
        HWND i16_hWnd;
        BITMAPINFO i20;
        RGBQUAD i68[256];
        HPALETTE i1092;
        HPALETTE i1096;
        Rect i1100_canvasRect;
    };
}

#endif
