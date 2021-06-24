#include "engine/Bitmap.h"
#include <cstdlib>
#include <cstring>
#include "io/FileIo.h"
#include "engine/DrawableSurface.h"

namespace knights_and_merchants::engine
{
    Bitmap::Bitmap(const short width, const short height, const unsigned char * data)
        : i0_width { width }, i2_height { height }, i4 { 0 }, i8 { 0 },
          i12_data { static_cast<unsigned char *>(malloc(width * height)) }
    {
        if (data == nullptr)
            memset(i12_data, 0, width * height);
        else
            memcpy(i12_data, data, width * height);
    }

    Bitmap::~Bitmap()
    {
        if (i12_data != nullptr)
            free(i12_data);

        reset();
    }

    void Bitmap::reset()
    {
        i4 = 0;
        i8 = 0;
        i12_data = nullptr;
    }

    void Bitmap::read(knights_and_merchants::io::FileIo & fileIO)
    {
        short width;
        short height;
        int var3;
        int var4;

        fileIO.read(&width, 2);
        fileIO.read(&height, 2);
        fileIO.read(&var3, 4);
        fileIO.read(&var4, 4);

        new(this) Bitmap(width, height, nullptr);

        i4 = var3;
        i8 = var4;

        if (i12_data != nullptr)
            fileIO.read(i12_data, width * height);
    }

    void Bitmap::unk1(DrawableSurface & p0, int p4, int p8, int p12) const
    {
        short var4 = i2_height;
        short var10 = i0_width;

        auto dword_53D610 = (256 * abs(p12)) / i2_height;
        auto dword_53D5C8 = 256 * abs(p12);

        var10 += abs(p12);

        auto varC = p4 + i4;
        auto var14 = p8 + i8;

        if (p12 < 0)
            var14 += p12;

        auto var8 = var14;
        auto var18 = varC;

        if (unk12345(p0, varC, var14, var4, var10)) {
            auto dword_53D678 = 0;
            auto dword_53D65C = var10;
            auto dword_53D63C = dword_53D65C;

            if (var8 < var14) {
                dword_53D678 = abs(var14 - var8);
                dword_53D65C += abs(var14 - var8);
            }

            auto dword_53D650 = i12_data;

            if (var18 < varC) {
                dword_53D650 += (varC - var18) * i0_width;
                dword_53D5C8 -= (varC - var18) * dword_53D610;
            }

            auto dword_53D658 = p0.i6_surface + varC + p0.i4_pitch * var14;
            auto dword_53D684 = i0_width;
            auto dword_53D628 = var4;
            auto dword_53D608 = p0.i4_pitch;

            if (p12 >= 0) {
                auto esi = dword_53D650;
                auto ebp = dword_53D658;
                auto edi = ebp;
                auto edx = dword_53D608;
                auto eax = 0;

                while (dword_53D628--) {
                    auto ecx = dword_53D684;

                    auto eax2 = eax / 256;
                    if (eax2 >= dword_53D678) {
                        eax2 -= dword_53D678;
                        ecx += eax2;

                        if (ecx <= dword_53D65C) {
                            ecx -= eax2;
                        }
                        else {
                            ecx = dword_53D63C;
                            ecx -= eax2;

                            if (ecx <= 0)
                                goto end;
                        }
                    }
                    else {
                        esi += dword_53D678 - eax2;
                        ecx -= dword_53D678 - eax2;
                        eax2 = 0;

                        if (ecx <= 0)
                            goto end;
                    }

                    eax2 += edx;
                    edi = ebp;
                    edi += eax2;

                    while (ecx--) {
                        if (*esi != 0)
                            *edi = *esi;

                        esi++;
                        edi += edx;
                    }

                end:
                    ebp++;
                    esi = dword_53D684 + dword_53D650;
                    dword_53D650 = esi;
                    eax += dword_53D610;
                }
            }
            else {
                throw 0; // reverse
            }
        }
    }

    void Bitmap::unk2(DrawableSurface & surface, int x, int y, const unsigned char * table, short height)
    {
        if (height < i2_height) {
            const short normalHeight = i2_height;

            i2_height = height;
            drawRemapped(surface, x, y, table);
            i2_height = normalHeight;
        }
        else {
            drawRemapped(surface, x, y, table);
        }
    }


    void Bitmap::extractFromSurface(const DrawableSurface & surface, int x, int y)
    {
        auto dword_53D604 = x;
        auto dword_53D5C0 = y;
        auto word_53D680 = i0_width;
        auto word_53D674 = i2_height;

        if (unk12345(surface, x, y, word_53D680, word_53D674)) {
            dword_53D604 -= x;
            dword_53D5C0 -= y;

            auto dst = i12_data + abs(dword_53D604) + abs(dword_53D5C0) * i0_width;
            auto src = surface.i6_surface + x + y * surface.i4_pitch;
            auto dword_53D5F8 = surface.i4_pitch - word_53D680;
            auto dword_53D5C4 = i0_width - word_53D680;

            while (word_53D674--) {
                auto width = word_53D680;
                while (width--) {
                    *dst++ = *src++;
                }

                src += dword_53D5F8;
                dst += dword_53D5C4;
            }
        }
    }

    void Bitmap::drawSingleColored(DrawableSurface & surface, int x, int y, unsigned char color) const
    {
        x += i4;
        y += i8;

        auto dword_53D600 = x;
        auto dword_53D64C = y;

        auto word_53D620 = i0_width;
        auto word_53D66C = i2_height;

        if (unk12345(surface, x, y, word_53D620, word_53D66C)) {
            dword_53D600 -= x;
            dword_53D64C -= y;

            auto dword_53D670 = surface.i4_pitch - word_53D620;
            auto dword_53D660 = i0_width - word_53D620;

            auto dst = surface.i6_surface + x + y * surface.i4_pitch;
            auto src = i12_data + abs(dword_53D600) + abs(dword_53D64C) * i0_width;

            while (word_53D66C--) {
                auto width = word_53D620;
                while (width--) {
                    if (*src != 0)
                        *dst = color;

                    ++dst;
                    ++src;
                }

                dst += dword_53D670;
                src += dword_53D660;
            }
        }
    }

    void Bitmap::drawResized(DrawableSurface & surface, int x, int y, int width, int height) const
    {
        auto var14 = (i0_width * 1000) / width;
        auto var20 = (i2_height * 1000) / height;

        auto varC = 0;
        auto var10 = 0;

        auto var24 = surface.i4_pitch - width;
        auto var28 = i12_data;

        auto var8 = surface.i6_surface + x + surface.i4_pitch * y;

        for (int i = 0; i < height; ++i, var8 += var24) {
            for (int j = 0; j < width; ++j, ++var8) {
                auto var4 = var28[varC / 1000];

                if (var4 != 0)
                    *var8 = var4;

                varC += var14;
            }

            varC = 0;

            var10 += var20;

            var28 = i12_data + (var10 / 1000) * i0_width;
        }
    }


    void Bitmap::draw(DrawableSurface & surface, int x, int y) const
    {
        drawRemapped(surface, x, y, nullptr);
    }

    void Bitmap::drawRemapped(DrawableSurface & surface, int x, int y, const unsigned char * table) const
    {
        x = x + i4;
        y = y + i8;

        auto var4 = x;
        auto var8 = y;

        auto word_53D5E8 = i0_width;
        auto word_53D618 = i2_height;

        if (unk12345(surface, x, y, word_53D5E8, word_53D618)) {
            var4 = var4 - x;
            var8 = var8 - y;

            auto dword_53D5D0 = surface.i4_pitch - word_53D5E8;
            auto dword_53D630 = i0_width - word_53D5E8;

            auto src = i12_data + abs(var4) + abs(var8) * i0_width;
            auto dst = surface.i6_surface + x + surface.i4_pitch * y;

            if (table != nullptr) {
                while (word_53D618--) {
                    short width = word_53D5E8;
                    while (width--) {
                        if (*src != 0)
                            *dst = *(table + *src);

                        src++;
                        dst++;
                    }

                    dst += dword_53D5D0;
                    src += dword_53D630;
                }
            }
            else {
                while (word_53D618--) {
                    short width = word_53D5E8;
                    while (width--) {
                        if (*src != 0)
                            *dst = *src;

                        dst++;
                        src++;
                    }

                    dst += dword_53D5D0;
                    src += dword_53D630;
                }
            }
        }
    }

    bool Bitmap::unk12345(const DrawableSurface & surface, int & x, int & y, short & width, short & height) const
    {
        const int right { x + width };
        const int bottom { y + height };

        if (x >= surface.i0_width || right <= 0 || y >= surface.i2_height || bottom <= 0)
            return false;

        if (x < 0) {
            width += x;
            x = 0;
        }

        if (right > surface.i0_width)
            width = surface.i0_width - x;

        if (y < 0) {
            height += y;
            y = 0;
        }

        if (bottom > surface.i2_height)
            height = surface.i2_height - y;

        return true;
    }
}
