#ifndef KNIGHTS_AND_MERCHANTS_GRAPHICS_PALETTE_H
#define KNIGHTS_AND_MERCHANTS_GRAPHICS_PALETTE_H

namespace knights_and_merchants::graphics
{
    /**
     * Represents a color in RGB format.
     */
    struct Color
    {
        unsigned char r;
        unsigned char g;
        unsigned char b;
    };

    /**
     * Represents a color cycle within a color palette.
     */
    struct ColorCycle
    {
        short i0_start;
        short i2_length;
        short i4_ticksToUpdate;
        short i6_ticksToNext;
    };

    /**
     * Represents a color palette.
     * \n
     * It supports 256 colors (8 bit) and color cycling.
     */
    class Palette
    {
    public:

        /**
         * Creates a new color palette.
         * \n
         * It contains only the color black and has no color cycles.
         */
        Palette() noexcept;

        /**
         * Gets a color.
         *
         * @param i The index of the color to be obtained.
         *
         * @return The i-th color.
         */
        [[nodiscard]]
        const Color * getColor(unsigned char i) const noexcept;

        /**
         * Sets a color.
         *
         * @param i The index of the color to be set.
         * @param color The new color value.
         */
        void setColor(unsigned char i, const Color * color) noexcept;

        /**
         * Sets a color.
         *
         * @param i The index of the color to be set.
         * @param r The new R value.
         * @param g The new G value.
         * @param b The new B value.
         */
        void setColor(unsigned char i, unsigned char r, unsigned char g, unsigned char b) noexcept;

        /**
         * Determines the index of the most similar color.
         * \n
         * Note that only colors that are not in a color cycle are taken into account and that the
         * color may differ significantly if the color palette contains entirely different colors.
         *
         * @param r The R value of the color to find.
         * @param g The G value of the color to find.
         * @param b The B value of the color to find.
         *
         * @return The index of the most similar color.
         */
        [[nodiscard]]
        int getMostSimilarColor(unsigned char r, unsigned char g, unsigned char b) const noexcept;

        /**
         * Adds a color cycle.
         *
         * @param start The index of the first color.
         * @param length The color count.
         * @param ticksToUpdate The tick count until the next color cycle.
         *
         * @return The index of the new color cycle.
         */
        int addColorCycle(short start, short length, short ticksToUpdate) noexcept;

        /**
         * Updates all color cycles.
         *
         * @return True if any color cycle got shifted, False otherwise.
         */
        bool update() noexcept;

    private:

        /**
         * Indicates whether the specified color is within a color cycle.
         *
         * @param i The index of the color to be checked.
         *
         * @return True if the specified color is within a color cycle, False otherwise.
         */
        [[nodiscard]]
        bool isColorCycled(int i) const noexcept;

        /**
         * Shifts a color cycle.
         *
         * @param index The index of the color cycle to be shifted.
         */
        void shiftCycle(int index) noexcept;

        Color i0_colors[256];
        ColorCycle i768_colorCycles[8];
    public:
        short i832_colorCycleCount;

    };
}

#endif
