#ifndef KNIGHTS_AND_MERCHANTS_IO_KEYBOARD_HANDLER_H
#define KNIGHTS_AND_MERCHANTS_IO_KEYBOARD_HANDLER_H

#include <dinput.h>
#include <Windows.h>

namespace knights_and_merchants::io
{
    class KeyboardHandler
    {
    public:
        KeyboardHandler(HWND hWnd, LPDIRECTINPUT8 pA);

        KeyboardHandler(const KeyboardHandler &) = delete;
        KeyboardHandler(KeyboardHandler &&) = delete;

        KeyboardHandler & operator=(const KeyboardHandler &) = delete;
        KeyboardHandler & operator=(KeyboardHandler &&) = delete;

        ~KeyboardHandler();

        void updateState();
        unsigned char unk2();

        bool isKeyDown(unsigned char keyCode) const;

        bool unkHaha() const;
        bool unkHaha222() const;
        bool unkHaha444() const;

        void unk30(bool active);

        bool isMenuDown() const;
        bool isShiftDown() const;
        bool isControlDown() const;
    private:
        void reset();

        LPDIRECTINPUTDEVICE8 i0_device;
        LPDIRECTINPUT8 i4_directInput;
        bool i8_isAcquired;
        unsigned char i12[256];
        unsigned char i268;
        unsigned char i269;
        short i270;
        short i272;
    };
}

#endif
