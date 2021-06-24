#ifndef KNIGHTS_AND_MERCHANTS_INPUTHANDLER_H
#define KNIGHTS_AND_MERCHANTS_INPUTHANDLER_H

#include <dinput.h>
#include <Windows.h>


namespace knights_and_merchants::utilities
{
    class Rect;
}

namespace knights_and_merchants::engine {
    class MouseHandler;
    class KeyboardHandler;
    class Bitmap;

    class InputHandler {
    public:

        static InputHandler* instance;

        InputHandler(HWND hWnd, HINSTANCE hInstance, const knights_and_merchants::utilities::Rect& screenRect, Bitmap* unk);

        ~InputHandler();

        [[nodiscard]]
        MouseHandler* getMouseHandler() const
        {
            return i4;
        }

        [[nodiscard]]
        KeyboardHandler* getKeyboardHandler() const
        {
            return i8;
        }

        void updateState();
    private:

        void reset();

        LPDIRECTINPUT8 i0;
        MouseHandler* i4;
        KeyboardHandler* i8;
    };

}
#endif
