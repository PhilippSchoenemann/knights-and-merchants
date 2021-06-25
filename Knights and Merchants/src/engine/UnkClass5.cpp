//
// Created by schoe on 06.10.2020.
//

#include "engine/UnkClass5.h"
#include <cstdlib>

namespace knights_and_merchants::engine
{
    UnkClass5::UnkClass5()
        : colors { }, i832 { }
    {
        reset();
    }

    UnkClass5::~UnkClass5()
    {
        reset();
    }

    void UnkClass5::reset()
    {
        for (auto & color : colors) {
            color.r = 0;
            color.g = 0;
            color.b = 0;
        }

        i832 = 0;
    }

    int UnkClass5::unk1(unsigned char p0, int p4, int p8)
    {
        unsigned char var18 = 0;
        int var8 = 0x7FFFFFFF;

        Color * ptr = &colors[1];
        for (int i = 1; i < 255; ++i, ++ptr) {
            if (unk2(i) == 0) {
                int mod_red = abs(p0 - ptr->r);
                mod_red = mod_red * mod_red;

                int mod_green = abs(p4 - ptr->g);
                mod_green = mod_green * mod_green;

                int mod_blue = abs(p8 - ptr->b);
                mod_blue = mod_blue * mod_blue;

                int res = mod_red + mod_green + mod_blue;
                if (res < var8) {
                    var8 = res;
                    var18 = i;
                }
            }
        }

        return var18;
    }

    void UnkClass5::unk4(unsigned char p0, const Color * p4)
    {
        colors[p0].r = p4->r;
        colors[p0].g = p4->g;
        colors[p0].b = p4->b;
    }

    short UnkClass5::unk3(short p0, short p4, short p8)
    {
        if (i832 >= 8)
            return -1;

        if ((p0 + p4) > 255)
            return -1;

        auto var4 = i768[i832];

        i832++;

        var4.i0 = p0;
        var4.i2 = p4;
        var4.i4 = p8;
        var4.i6 = p8;

        return i832 - 1;
    }

    bool UnkClass5::unk12()
    {
        auto result = false;

        for (int i = 0; i < i832; ++i) {
            if (i768[i].i6 != 0) {
                i768[i].i6 -= 1;
            }
            else {
                unk15(i);
                result = true;
                i768[i].i6 = i768[i].i4;
            }
        }

        return result;
    }

    void UnkClass5::unk15(short p0)
    {
        if (p0 < i832) {
            auto & var8 = i768[p0];
            auto & var4 = colors[var8.i0 + var8.i2 - 1];

            for (int i = var8.i2 - 1; i > 0; --i)
                colors[var8.i0 + i] = colors[var8.i0 + i - 1];

            colors[var8.i0] = var4;
        }
    }

    int UnkClass5::unk2(int p0)
    {
        if (i832 != 0) {
            for (int j = 0; j < i832; ++j) {
                if (p0 >= i768[j].i0) {
                    if (p0 <= (i768[j].i0 + i768[j].i2)) {
                        return 1;
                    }
                }
            }
        }

        return 0;
    }

    void UnkClass5::setColorAt(const unsigned char i, const uint8_t r, const uint8_t g, const uint8_t b)
    {
        colors[i].r = r;
        colors[i].g = g;
        colors[i].b = b;
    }

    const Color * UnkClass5::getColorPtr(const unsigned char i) const
    {
        return &colors[i];
    }
}
