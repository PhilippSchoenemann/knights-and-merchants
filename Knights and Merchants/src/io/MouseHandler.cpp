#include "io/MouseHandler.h"
#include "Windows.h"
#include "graphics/Bitmap.h"
#include "graphics/DrawableSurface.h"

namespace knights_and_merchants::io
{
    using graphics::Bitmap;
    using graphics::DrawableSurface;

    MouseHandler::MouseHandler(const Bitmap * cursor, const Rect & screenRect, HWND hWnd, LPDIRECTINPUT8 directInput)
        : i16 { }, i32 { }
    {
        i64_isLeftButtonDown = 0;
        i68_isRightButtonDown = 0;
        i72_isMiddleButtonDown = 0;
        i80_isCursorHidden = false;
        i84_isCursorFreezed = false;
        i100_isAcquired = false;
        i104 = 100;

        if (cursor == nullptr) {
            i56_cursor = nullptr;
            i60_background = nullptr;
        } else {
            i56_cursor = cursor;

            i60_background = new Bitmap(i56_cursor->i0_width, i56_cursor->i2_height, nullptr);
            i60_background->i4 = i56_cursor->i4;
            i60_background->i8 = i56_cursor->i8;
        }

        i0_position.x = screenRect.left + 1;
        i0_position.y = screenRect.top + 1;
        i8_previousPosition.x = i0_position.x;
        i8_previousPosition.y = i0_position.y;

        setMouseArea(screenRect);

        i96_directInput = directInput;

        if (setupMouseDevice(hWnd) && i92_device->Acquire() == DI_OK)
            i100_isAcquired = true;

        i88_hasCursorChanged = false;
    }

    MouseHandler::~MouseHandler()
    {
        if (i60_background != nullptr) {
            delete i60_background;
            i60_background = nullptr;
        }

        if (i92_device != nullptr) {
            if (i100_isAcquired) {
                i92_device->Unacquire();
            }

            i92_device->Release();
            i92_device = nullptr;
        }
    }

    void MouseHandler::setMouseArea(const Rect & area)
    {
        i32 = area;

        if (i56_cursor == nullptr) {
            i16 = area;
        } else {
            i16.left = area.left - i56_cursor->i4;
            i16.top = area.top - i56_cursor->i8;
            i16.right = area.right - (i56_cursor->i0_width / 3) - i56_cursor->i4;
            i16.bottom = area.bottom - (i56_cursor->i2_height / 3) - i56_cursor->i8;
        }

        keepMouseInArea();
    }

    void MouseHandler::keepMouseInArea()
    {
        if (!PtInRect(&i16, i0_position)) {
            if (i0_position.x > i16.right)
                i0_position.x = i16.right;

            if (i0_position.x < i16.left)
                i0_position.x = i16.left;

            if (i0_position.y > i16.bottom)
                i0_position.y = i16.bottom;

            if (i0_position.y < i16.top)
                i0_position.y = i16.top;
        }
    }

    void MouseHandler::drawCursor(DrawableSurface & surface) const
    {
        if (i56_cursor != nullptr && !i80_isCursorHidden)
            i56_cursor->draw(surface, i0_position.x, i0_position.y);
    }

    void MouseHandler::unkCursor(const DrawableSurface & surface)
    {
        if (i60_background != nullptr)
            i60_background->extractFromSurface(surface, i0_position.x + i60_background->i4,
                                               i0_position.y + i60_background->i8);

        i8_previousPosition.x = i0_position.x;
        i8_previousPosition.y = i0_position.y;
    }

    bool MouseHandler::setupMouseDevice(HWND pHwnd)
    {
        HRESULT result = i96_directInput->CreateDevice(GUID_SysMouse, &i92_device, nullptr);
        if (result != DI_OK)
            goto error;

        result = i92_device->SetDataFormat(&c_dfDIMouse);
        if (result != DI_OK)
            goto error;

        result = i92_device->SetCooperativeLevel(pHwnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND);
        if (result != DI_OK)
            goto error;

        return true;

    error:
        if (i92_device != nullptr)
            i92_device->Release();

        return false;
    }

    void MouseHandler::overdrawPreviousCursor(DrawableSurface & surface)
    {
        if (i60_background == nullptr)
            return;

        i60_background->draw(surface, i8_previousPosition.x, i8_previousPosition.y);

        if (i88_hasCursorChanged) {
            if (i60_background != nullptr)
                delete i60_background;

            i60_background = new Bitmap(i56_cursor->i0_width, i56_cursor->i2_height, nullptr);
            i60_background->i4 = i56_cursor->i4;
            i60_background->i8 = i56_cursor->i8;

            i88_hasCursorChanged = false;
        }
    }

    void MouseHandler::updateState()
    {
        if (i100_isAcquired) {
            DIMOUSESTATE mouseState;

            if (i92_device->GetDeviceState(sizeof(DIMOUSESTATE), &mouseState) == DI_OK) {
                i48_deltaX = (i104 * mouseState.lX) / 100;
                i52_deltaY = (i104 * mouseState.lY) / 100;

                if (!i84_isCursorFreezed) {
                    i0_position.x += i48_deltaX;
                    i0_position.y += i52_deltaY;
                }

                i64_isLeftButtonDown = mouseState.rgbButtons[0] & 0x80;
                i68_isRightButtonDown = mouseState.rgbButtons[1] & 0x80;
                i72_isMiddleButtonDown = mouseState.rgbButtons[2] & 0x80;
            }

            keepMouseInArea();
            i76 = 1;
        }
    }

    void MouseHandler::setMousePosition(const int x, const int y)
    {
        i0_position.x = x;
        i0_position.y = y;
        keepMouseInArea();
    }

    void MouseHandler::setCursor(const Bitmap * cursor)
    {
        if (cursor != nullptr) {
            if (i56_cursor == nullptr) {
                if (i60_background == nullptr) {
                    i60_background = new Bitmap(cursor->i0_width, cursor->i2_height, nullptr);
                    i60_background->i4 = cursor->i4;
                    i60_background->i8 = cursor->i8;
                }
            }
            else {
                i88_hasCursorChanged = true;
            }

            i56_cursor = cursor;
            setMouseArea(i32);
        }
    }

    void MouseHandler::unk60(const bool active)
    {
        if (active) {
            i100_isAcquired = i92_device->Acquire() == DI_OK;
        }
        else {
            i92_device->Unacquire();
            i100_isAcquired = false;
        }
    }
}
