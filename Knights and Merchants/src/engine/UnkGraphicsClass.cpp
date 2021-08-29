#include "engine/UnkGraphicsClass.h"

namespace knights_and_merchants::engine
{
    UnkGraphicsClass::UnkGraphicsClass(HWND p0, const Rect & p4)
        : i1100 { p4 }
    {
        reset();
        i16 = p0;
        i12 = GetWindowDC(p0);
        i8 = CreateCompatibleDC(nullptr);

        i20.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        i20.bmiHeader.biPlanes = 1;
        i20.bmiHeader.biBitCount = 8;
        i20.bmiHeader.biHeight = -i1100.getHeight();
        i20.bmiHeader.biCompression = 0;
        i20.bmiHeader.biClrUsed = 0;
        i20.bmiHeader.biClrImportant = 0;
        i20.bmiHeader.biWidth = i1100.getWidth();
        i20.bmiHeader.biXPelsPerMeter = 0;
        i20.bmiHeader.biYPelsPerMeter = 0;
        i20.bmiHeader.biSizeImage = i1100.getWidth() * i1100.getHeight();

        i0 = CreateDIBSection(i8, &i20, DIB_RGB_COLORS, &i64, nullptr, 0);

        if (i0 == nullptr) {
            DeleteDC(i8);
            return;
        }

        i4 = SelectObject(i8, i0);

        if (i4 == nullptr) {
            DeleteObject(i0);
            DeleteDC(i8);
            return;
        }

        memset(i64, -1, i1100.getWidth() * i1100.getHeight());
    }

    UnkGraphicsClass::~UnkGraphicsClass()
    {
        unk();

        if (DeleteDC(i8)) {
            SelectObject(i8, i4);
            DeleteObject(i0);
            ReleaseDC(i16, i12);
        }
    }

    void UnkGraphicsClass::unk()
    {
        if (i1092 != nullptr)
            DeleteObject(i1092);

        if (i1096 != nullptr)
            SelectPalette(i12, i1096, false);
    }



    bool UnkGraphicsClass::unk100()
    {
        return SetDIBColorTable(i8, 0, 255, i68) > 0;
    }

    bool UnkGraphicsClass::unk200()
    {
        if (SelectPalette(i12, i1092, false) == nullptr)
            return false;

        return RealizePalette(i12) != GDI_ERROR;
    }

    bool UnkGraphicsClass::setPalette(const UnkClass5 & p0)
    {
        unk();

        char alloc[sizeof(LOGPALETTE) + (256 - 1) * sizeof(PALETTEENTRY)];
        LOGPALETTE & plpal = *reinterpret_cast<LOGPALETTE*>(&alloc);

        plpal.palVersion = 0x300;
        plpal.palNumEntries = 0x100;

        for (int edi = 1; edi <= 254; ++edi) {
            auto esi = p0.getColorPtr(edi);

            plpal.palPalEntry[edi].peRed = esi->r;
            i68[edi].rgbRed = esi->r;

            plpal.palPalEntry[edi].peGreen = esi->g;
            i68[edi].rgbGreen = esi->g;

            plpal.palPalEntry[edi].peBlue = esi->b;
            i68[edi].rgbBlue = esi->b;

            i68[edi].rgbReserved = 0;
        }

        GetSystemPaletteEntries(i8, 0, 10, &plpal.palPalEntry[0]);
        GetSystemPaletteEntries(i8, 246, 10, &plpal.palPalEntry[246]);

        i1092 = CreatePalette(&plpal);

        if (i1092 == nullptr)
            return false;

        i1096 = SelectPalette(i12, i1092, false);

        if (i1096 == nullptr)
            return false;

        unk100();
        unk200();

        return true;
    }

    bool UnkGraphicsClass::draw()
    {
        const auto ebx = SelectPalette(i12, i1092, false);
        if (ebx == nullptr)
            return false;

        if (BitBlt(i12, i1100.left, i1100.top, i1100.getWidth(), i1100.getHeight(), i8, 0, 0, SRCCOPY) == 0)
            return false;

        SelectPalette(i12, ebx, false);
        return true;
    }

    void UnkGraphicsClass::reset()
    {
        i0 = nullptr;
        i4 = nullptr;
        i8 = nullptr;
        i12 = nullptr;
        i64 = nullptr;
        i1092 = nullptr;
        i1096 = nullptr;
    }
}
