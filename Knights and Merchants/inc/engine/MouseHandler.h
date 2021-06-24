//
// Created by schoe on 05.10.2020.
//

#ifndef KNIGHTS_AND_MERCHANTS_MOUSEHANDLER_H
#define KNIGHTS_AND_MERCHANTS_MOUSEHANDLER_H

#include <dinput.h>
#include "utilities/Rect.h"

using knights_and_merchants::utilities::Rect;

namespace knights_and_merchants::engine {
    struct DrawableSurface;
    class Bitmap;

    class MouseHandler {
    public:
        MouseHandler(const Bitmap* cursor, const Rect& screenRect, HWND pHwnd, LPDIRECTINPUT8 pA);
        ~MouseHandler();

        void setI104(const short value) { i104 = value; }

        void setCursorHidden(const bool cursorHidden) { i80_isCursorHidden = cursorHidden; }

        void freezeCursor() { i84_isCursorFreezed = true; }

        void unfreezeCursor() { i84_isCursorFreezed = false; }

        bool setupMouseDevice(HWND pHwnd);

        void updateState();

        void setMouseArea(const Rect& area);

        void setMousePosition(const int x, const int y);

        void keepMouseInArea();

        void setCursor(const Bitmap* cursor);

        void unk60(const bool active);

        void overdrawPreviousCursor(DrawableSurface& surface);

        void unkCursor(const DrawableSurface& surface);

        void drawCursor(DrawableSurface& surface) const;

        POINT i0_position;
        POINT i8_previousPosition;
        Rect i16;
        Rect i32;
        int i48_deltaX;
        int i52_deltaY;
        const Bitmap* i56_cursor;
        Bitmap* i60_background;
        int i64_isLeftButtonDown;
        int i68_isRightButtonDown;
        int i72_isMiddleButtonDown;
        int i76;
        bool i80_isCursorHidden;
        bool i84_isCursorFreezed;
        bool i88_hasCursorChanged;
        LPDIRECTINPUTDEVICE8 i92_device;
        LPDIRECTINPUT8 i96_directInput;
        bool i100_isAcquired;
        short i104;

    };

}
#endif