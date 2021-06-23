#include "utilities/Rect.h"

namespace knights_and_merchants::utilities {

    Rect::Rect() noexcept
        : RECT{ 0, 0, 0, 0 }
    {

    }

    Rect::Rect(const int x, const int y, const int width, const int height) noexcept
        : RECT{ x, y, x + width, y + height }
    {

    }

    void Rect::move(const int dx, const int dy) noexcept
    {
        left += dx;
        right += dx;

        top += dy;
        bottom += dy;
    }

    void Rect::setBounds(const int x, const int y, const int width, const int height) noexcept
    {
        left = x;
        right = x + width;

        top = y;
        bottom = y + height;
    }

    void Rect::setSize(const int width, const int height) noexcept {
        right = left + width;
        bottom = top + height;
    }

    void Rect::inflate(const int p0, const int p4) noexcept
    {
        left -= p0;
        right += p0;

        top -= p4;
        bottom += p4;
    }

}
