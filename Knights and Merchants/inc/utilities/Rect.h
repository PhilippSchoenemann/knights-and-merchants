#ifndef KNIGHTS_AND_MERCHANTS_UTILITIES_RECT_H
#define KNIGHTS_AND_MERCHANTS_UTILITIES_RECT_H

#include <Windows.h>

namespace knights_and_merchants::utilities
{
    class Rect : public RECT {
    public:
        Rect() noexcept;
        Rect(int x, int y, int width, int height) noexcept;

        void move(int dx, int dy) noexcept;

        void setBounds(int x, int y, int width, int height) noexcept;

        void setSize(int width, int height) noexcept;

        void inflate(int p0, int p4) noexcept;

        [[nodiscard]]
        int getWidth() const noexcept
        {
            return abs(right - left);
        }

        [[nodiscard]]
        int getHeight() const noexcept
        {
            return abs(bottom - top);
        }

    };
}

#endif