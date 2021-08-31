#include "engine/Palette.h"
#include <cstdlib>

namespace knights_and_merchants::engine
{
    Palette::Palette() noexcept
        : i0_colors { }, i832_colorCycleCount { }
    {
        reset();
    }

    Palette::~Palette()
    {
        reset();
    }

    void Palette::reset() noexcept
    {
        for (auto & color : i0_colors) {
            color.r = 0;
            color.g = 0;
            color.b = 0;
        }

        i832_colorCycleCount = 0;
    }

    int Palette::getMostSimilarColor(const unsigned char r, const unsigned char g, const unsigned char b) const noexcept
    {
        unsigned char min = 0;
        int minDistance = 0x7FFFFFFF;

        const auto * color = &i0_colors[1];
        for (int i = 1; i < 255; ++i, ++color) {
            if (!isColorCycled(i)) {
                const int dr = abs(r - color->r);
                const int dg = abs(g - color->g);
                const int db = abs(b - color->b);
           
                if (const int distance = dr * dr + dg * dg + db * db; distance < minDistance) {
                    minDistance = distance;
                    min = static_cast<unsigned char>(i);
                }
            }
        }

        return min;
    }



    int Palette::addColorCycle(const short start, const short length, const short ticksToUpdate) noexcept
    {
        if (i832_colorCycleCount >= 8 || start + length > 255)
            return -1;

        auto & var4 = i768_colorCycles[i832_colorCycleCount++]; // TODO: is ref correct?
        var4.i0_start = start;
        var4.i2_length = length;
        var4.i4_ticksToUpdate = ticksToUpdate;
        var4.i6_ticksToNext = ticksToUpdate;

        return i832_colorCycleCount - 1;
    }

    bool Palette::update() noexcept
    {
        auto result = false;

        for (int i = 0; i < i832_colorCycleCount; ++i) {
            if (i768_colorCycles[i].i6_ticksToNext != 0) {
                i768_colorCycles[i].i6_ticksToNext--;
            } else {
                shiftCycle(i);
                result = true;
                i768_colorCycles[i].i6_ticksToNext = i768_colorCycles[i].i4_ticksToUpdate;
            }
        }

        return result;
    }

    void Palette::shiftCycle(const int index) noexcept
    {
        if (index < i832_colorCycleCount) {
            const auto & cycle = i768_colorCycles[index];
            const auto lastColor = i0_colors[cycle.i0_start + cycle.i2_length - 1];

            for (int i = cycle.i2_length - 1; i > 0; --i)
                i0_colors[cycle.i0_start + i] = i0_colors[cycle.i0_start + i - 1];

            i0_colors[cycle.i0_start] = lastColor;
        }
    }

    bool Palette::isColorCycled(const int i) const noexcept
    {     
        for (int j = 0; j < i832_colorCycleCount; ++j)
            if (i >= i768_colorCycles[j].i0_start && i <= i768_colorCycles[j].i0_start + i768_colorCycles[j].i2_length)            
                return true;             
            
        return false;
    }

    void Palette::setColor(const unsigned char i, const Color * color) noexcept
    {
        i0_colors[i].r = color->r;
        i0_colors[i].g = color->g;
        i0_colors[i].b = color->b;
    }

    void Palette::setColor(const unsigned char i, const unsigned char r, const unsigned char g, const unsigned char b) noexcept
    {
        i0_colors[i].r = r;
        i0_colors[i].g = g;
        i0_colors[i].b = b;
    }

    const Color * Palette::getColorPtr(const unsigned char i) const noexcept
    {
        return &i0_colors[i];
    }
}
