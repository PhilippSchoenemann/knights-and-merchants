#ifndef KNIGHTS_AND_MERCHANTS_UNKCLASS5_H
#define KNIGHTS_AND_MERCHANTS_UNKCLASS5_H

#include <cstdint>

namespace knights_and_merchants::engine
{
    struct Color
    {
        uint8_t r;
        uint8_t g;
        uint8_t b;
    };

    struct ColorCycle
    {
        int16_t i0_start;
        int16_t i2_length;
        int16_t i4_ticksToUpdate;
        int16_t i6_ticksToNext;
    };

    class Palette // UnkClass5
    {
    public:
        Palette() noexcept;

        Palette(const Palette & other) noexcept = default;
        Palette(Palette && other) noexcept = default;

        Palette & operator=(const Palette & other) noexcept = default;
        Palette & operator=(Palette && other) noexcept = default;

        ~Palette();

        [[nodiscard]]
        const Color * getColorPtr(unsigned char i) const noexcept;

        void setColor(unsigned char i, const Color * color) noexcept;

        void setColor(unsigned char i, unsigned char r, unsigned char g, unsigned char b) noexcept;

        int getMostSimilarColor(unsigned char r, unsigned char g, unsigned char b) const noexcept;

        int addColorCycle(short start, short length, short ticksToUpdate) noexcept;

        bool update() noexcept;
        
    private:
        bool isColorCycled(int i) const noexcept;

        void shiftCycle(int index) noexcept;

        void reset() noexcept;

        Color i0_colors[256];
        ColorCycle i768_colorCycles[8];
    public:
        int16_t i832_colorCycleCount;

    };
}

#endif
