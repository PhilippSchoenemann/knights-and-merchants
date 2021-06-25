#include "io/KeyboardHandler.h"
#include <dinput.h>

namespace knights_and_merchants::io {

    static const unsigned char keyCodeList[] = {
        0x01, 0x02, 0x03, 0x04,
        0x05, 0x06, 0x07, 0x08,
        0x09, 0x0A, 0x0B, 0x0C,
        0x0D, 0x0E, 0x0F, 0x10,
        0x11, 0x12, 0x13, 0x14,
        0x15, 0x16, 0x17, 0x18,
        0x19, 0x1A, 0x1B, 0x1C,
        0x1D, 0x1E, 0x1F, 0x20,
        0x21, 0x22, 0x23, 0x24,
        0x25, 0x26, 0x27, 0x28,
        0x29, 0x2B, 0x2C, 0x2D,
        0x2E, 0x2F, 0x30, 0x31,
        0x32, 0x33, 0x34, 0x35,
        0x37, 0x39, 0x3A, 0x3B,
        0x3C, 0x3D, 0x3E, 0x3F,
        0x40, 0x41, 0x42, 0x43,
        0x44, 0x45, 0x46, 0x47,
        0x48, 0x49, 0x4A, 0x4B,
        0x4C, 0x4D, 0x4E, 0x4F,
        0x50, 0x51, 0x52, 0x53,
        0x57, 0x58, 0x9C, 0xB5,
        0xB7, 0xC7, 0xC9, 0xCF,
        0xD1, 0xD2, 0xD1, 0xC9,
        0xD3, 0xCB, 0xCD, 0xC8,
        0xD0, 0x00
    };

    KeyboardHandler::KeyboardHandler(HWND hWnd, LPDIRECTINPUT8 pA) {
        reset();

        i4_directInput = pA;
        HRESULT result = i4_directInput->CreateDevice(GUID_SysKeyboard, &i0_device, nullptr);
        if (result != DI_OK)
            goto error;

        result = i0_device->SetDataFormat(&c_dfDIKeyboard);
        if (result != DI_OK)
            goto error;

        result = i0_device->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
        if (result != DI_OK)
            goto error;

        if (i0_device->Acquire() == DI_OK)
            i8_isAcquired = true;

        updateState();
        return;

    error:
        if (i0_device != nullptr)
            i0_device->Release();

    }

    void KeyboardHandler::reset() {
        i0_device = nullptr;
        i8_isAcquired = false;

        i268 = 0;
        i269 = 0;

        for (int i = 0; i < 0x100; ++i) {
            i12[i] = 0;
        }

        i270 = 0;
    }

    void KeyboardHandler::updateState() {
        if (i8_isAcquired) {
            HRESULT result = i0_device->GetDeviceState(256, i12);
            if (result == DI_OK) {
                i270 = 0;

                if ((i12[DIK_LSHIFT] & 0x80) == 0x80 || (i12[DIK_RSHIFT] & 0x80) == 0x80) {
                    i270 = i270 | 2;
                }

                if ((i12[DIK_LMENU] & 0x80) == 0x80 || (i12[DIK_RMENU] & 0x80) == 0x80) {
                    i270 = i270 | 1;
                }

                if ((i12[DIK_LCONTROL] & 0x80) == 0x80 || (i12[DIK_RCONTROL] & 0x80) == 0x80) {
                    i270 = i270 | 4;
                }

                if (i268 != 0 && (i12[i268] & 0x80) == 0) {
                    i269 = i268;
                    i268 = 0;
                }

                if (i268 == 0) {
                    const unsigned char* ptr = keyCodeList;

                    while (*ptr != 0) {
                        if ((i12[*ptr] & 0x80) == 0x80) {
                            i268 = *ptr;
                            i272 = i270;
                            break;
                        }

                        ++ptr;
                    }
                }
            }
            else {
                if (result == DIERR_INPUTLOST) {
                    i8_isAcquired = false;
                    if (i0_device->Acquire() == DI_OK)
                        i8_isAcquired = true;
                }
            }

        }
    }

    unsigned char KeyboardHandler::unk2() {
        if (i8_isAcquired) {
            unsigned char a = i269;
            i269 = 0;
            return a;
        }
        else {
            return 0;
        }
    }

    bool KeyboardHandler::isKeyDown(unsigned char keyCode) const
    {
        return i8_isAcquired ? ((i12[keyCode] & 0x80) == 0x80) : false;
    }

    bool KeyboardHandler::unkHaha() const
    {
        return (i272 & 1) == 1;
    }

    bool KeyboardHandler::unkHaha222() const
    {
        return (i272 & 2) == 2;
    }

    bool KeyboardHandler::unkHaha444() const
    {
        return (i272 & 4) == 4;
    }

    void KeyboardHandler::unk30(bool active)
    {
        if (active) {
            i8_isAcquired = i0_device->Acquire() == DI_OK;
            i268 = 0;
            i269 = 0;

            for (int i = 0; i < 256; ++i) {
                i12[i] = 0;
            }
        }
        else {
            i0_device->Unacquire();
            i8_isAcquired = false;
        }
    }

    bool KeyboardHandler::isMenuDown() const
    {
        return i8_isAcquired ? (i270 & 1) == 1 : false;
    }

    bool KeyboardHandler::isShiftDown() const
    {
        return i8_isAcquired ? (i270 & 2) == 2 : false;
    }

    bool KeyboardHandler::isControlDown() const
    {
        return i8_isAcquired ? (i270 & 4) == 4 : false;
    }

    KeyboardHandler::~KeyboardHandler() {
        if (i0_device != nullptr) {
            if (i8_isAcquired) {
                i0_device->Unacquire();
                i8_isAcquired = false;
            }

            i0_device->Release();
        }

        reset();
    }
}