#include "engine/UnkGraphicsClass.h"
#include <new>

namespace knights_and_merchants::engine
{
    UnkGraphicsClass::UnkGraphicsClass(const HWND hWnd, const Rect & canvasRect) noexcept
        : i1100_canvasRect { canvasRect }
    {
        reset();
        i16_hWnd = hWnd;
        i12_windowDC = GetWindowDC(hWnd);
        i8_memoryDC = CreateCompatibleDC(nullptr);

        i20.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        i20.bmiHeader.biPlanes = 1;
        i20.bmiHeader.biBitCount = 8;
        i20.bmiHeader.biHeight = -i1100_canvasRect.getHeight();
        i20.bmiHeader.biCompression = 0;
        i20.bmiHeader.biClrUsed = 0;
        i20.bmiHeader.biClrImportant = 0;
        i20.bmiHeader.biWidth = i1100_canvasRect.getWidth();
        i20.bmiHeader.biXPelsPerMeter = 0;
        i20.bmiHeader.biYPelsPerMeter = 0;
        i20.bmiHeader.biSizeImage = i1100_canvasRect.getWidth() * i1100_canvasRect.getHeight();

        i0 = CreateDIBSection(i8_memoryDC, &i20, DIB_RGB_COLORS, &i64, nullptr, 0);

        if (i0 == nullptr) {
            DeleteDC(i8_memoryDC);
            return;
        }

        i4 = SelectObject(i8_memoryDC, i0);

        if (i4 == nullptr) {
            DeleteObject(i0);
            DeleteDC(i8_memoryDC);
            return;
        }

        memset(i64, -1, i1100_canvasRect.getWidth() * i1100_canvasRect.getHeight());
    }

    UnkGraphicsClass::~UnkGraphicsClass() noexcept
    {
        unk();

        if (DeleteDC(i8_memoryDC)) {
            SelectObject(i8_memoryDC, i4);
            DeleteObject(i0);
            ReleaseDC(i16_hWnd, i12_windowDC);
        }
    }

    void UnkGraphicsClass::setDisplayMode(const int width, const int height) noexcept
    {
        const Rect canvasRect { 0, 0, width, height };

        this->~UnkGraphicsClass();
        new (this) UnkGraphicsClass(i16_hWnd, canvasRect);
    }

    void UnkGraphicsClass::unk() const noexcept
    {
        if (i1092 != nullptr)
            DeleteObject(i1092);

        if (i1096 != nullptr)
            SelectPalette(i12_windowDC, i1096, false);
    }

    bool UnkGraphicsClass::unk100() const noexcept
    {
        return SetDIBColorTable(i8_memoryDC, 0, 255, i68) > 0;
    }

    bool UnkGraphicsClass::unk200() const noexcept
    {
        if (SelectPalette(i12_windowDC, i1092, false) == nullptr)
            return false;

        return RealizePalette(i12_windowDC) != GDI_ERROR;
    }

    bool UnkGraphicsClass::setPalette(const UnkClass5 & p0) noexcept
    {
        unk();

        char alloc[sizeof(LOGPALETTE) + (256 - 1) * sizeof(PALETTEENTRY)];
        LOGPALETTE & plpal = *reinterpret_cast<LOGPALETTE*>(&alloc);

        plpal.palVersion = 0x300;
        plpal.palNumEntries = 0x100;

        for (int i = 1; i <= 254; ++i) {
            const auto * color = p0.getColorPtr(i);

            plpal.palPalEntry[i].peRed = color->r;
            i68[i].rgbRed = color->r;

            plpal.palPalEntry[i].peGreen = color->g;
            i68[i].rgbGreen = color->g;

            plpal.palPalEntry[i].peBlue = color->b;
            i68[i].rgbBlue = color->b;

            i68[i].rgbReserved = 0;
        }

        GetSystemPaletteEntries(i8_memoryDC, 0, 10, &plpal.palPalEntry[0]);
        GetSystemPaletteEntries(i8_memoryDC, 246, 10, &plpal.palPalEntry[246]);

        i1092 = CreatePalette(&plpal);

        if (i1092 == nullptr)
            return false;

        i1096 = SelectPalette(i12_windowDC, i1092, false);

        if (i1096 == nullptr)
            return false;

        unk100();
        unk200();

        return true;
    }

    bool UnkGraphicsClass::draw() const noexcept
    {
        const auto palette = SelectPalette(i12_windowDC, i1092, false);

        if (palette == nullptr)
            return false;

        if (BitBlt(i12_windowDC, i1100_canvasRect.left, i1100_canvasRect.top, i1100_canvasRect.getWidth(), i1100_canvasRect.getHeight(), i8_memoryDC, 0, 0, SRCCOPY) == 0)
            return false;

        SelectPalette(i12_windowDC, palette, false);
        return true;
    }

    bool UnkGraphicsClass::unk222(const int width, const int height) const noexcept
    {
        const auto palette = SelectPalette(i12_windowDC, i1092, false);

        if (palette == nullptr)
            return false;

        StretchBlt(i12_windowDC, i1100_canvasRect.left, i1100_canvasRect.top, width, height, i8_memoryDC, 0, 0, i1100_canvasRect.getWidth(), i1100_canvasRect.getHeight(), SRCCOPY);
        SelectPalette(i12_windowDC, palette, false);
        return true;
    }

    void UnkGraphicsClass::reset() noexcept
    {
        i0 = nullptr;
        i4 = nullptr;
        i8_memoryDC = nullptr;
        i12_windowDC = nullptr;
        i64 = nullptr;
        i1092 = nullptr;
        i1096 = nullptr;
    }
}
