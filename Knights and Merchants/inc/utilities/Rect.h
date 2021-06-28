#ifndef KNIGHTS_AND_MERCHANTS_UTILITIES_RECT_H
#define KNIGHTS_AND_MERCHANTS_UTILITIES_RECT_H

#include <Windows.h>

namespace knights_and_merchants::utilities
{
    /// <summary>
    /// Represents a rectangle.
    /// </summary>
    class Rect : public RECT
    {
    public:
        /// <summary>
        /// Creates a rectangle at the origin (0 | 0).
        /// </summary>
        Rect() noexcept
            : RECT { 0, 0, 0, 0 } { }

        /// <summary>
        /// Creates a rectangle at (x | y) with the specified size.
        /// </summary>
        /// <param name="x">The X-coordinate of the rectangle.</param>
        /// <param name="y">The Y-coordinate of the rectangle.</param>
        /// <param name="width">The width of the rectangle.</param>
        /// <param name="height">The height of the rectangle.</param>
        Rect(const int x, const int y, const int width, const int height) noexcept
            : RECT { x, y, x + width, y + height } { }

        Rect(const Rect & other) noexcept = default;
        Rect(Rect && other) noexcept = default;

        ~Rect() = default;

        Rect & operator=(const Rect & other) noexcept = default;
        Rect & operator=(Rect && other) noexcept = default;

        /// <summary>
        /// Moves the rectangle.
        /// </summary>
        /// <param name="dx">The units to move the rectangle on the X axis.</param>
        /// <param name="dy">The units to move the rectangle on the Y axis.</param>
        void move(int dx, int dy) noexcept;

        /// <summary>
        /// Sets the bounds of the rectangle.
        /// </summary>
        /// <param name="x">The new X-coordinate of the rectangle.</param>
        /// <param name="y">The new Y-coordinate of the rectangle.</param>
        /// <param name="width">The new width of the rectangle.</param>
        /// <param name="height">The new height of the rectangle.</param>
        void setBounds(int x, int y, int width, int height) noexcept;

        /// <summary>
        /// Sets the size of the rectangle.
        /// </summary>
        /// <param name="width">The new width of the rectangle.</param>
        /// <param name="height">The new height of the rectangle.</param>
        void setSize(int width, int height) noexcept;

        /// <summary>
        /// Inflates the rectangle.
        /// </summary>
        /// <param name="width">The units added on the left and right side.</param>
        /// <param name="height">The units added on the top and bottom side.</param>
        void inflate(int width, int height) noexcept;

        /// <summary>
        /// Gets the width of the rectangle.
        /// </summary>
        /// <returns>The width of the rectangle.</returns>
        [[nodiscard]]
        int getWidth() const noexcept
        {
            return abs(right - left);
        }

        /// <summary>
        /// Gets the height of the rectangle.
        /// </summary>
        /// <returns>The height of the rectangle.</returns>
        [[nodiscard]]
        int getHeight() const noexcept
        {
            return abs(bottom - top);
        }
    };
}

#endif
