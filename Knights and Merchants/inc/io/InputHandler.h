#ifndef KNIGHTS_AND_MERCHANTS_IO_INPUT_HANDLER_H
#define KNIGHTS_AND_MERCHANTS_IO_INPUT_HANDLER_H

#include <dinput.h>
#include <Windows.h>

namespace knights_and_merchants
{
    namespace graphics
    {
        class Bitmap;
    }

    namespace utilities
    {
        class Rect;
    }

    namespace io
    {
        class MouseHandler;
        class KeyboardHandler;

        class InputHandler
        {
        public:
            static InputHandler * instance;

            InputHandler(HWND hWnd, HINSTANCE hInstance, const utilities::Rect & screenRect, graphics::Bitmap * unk);
            InputHandler(const InputHandler &) = delete;
            InputHandler(InputHandler &&) = delete;

            InputHandler & operator=(const InputHandler &) = delete;
            InputHandler & operator=(InputHandler &&) = delete;

            ~InputHandler();

            [[nodiscard]]
            MouseHandler * getMouseHandler() const
            {
                return i4;
            }

            [[nodiscard]]
            KeyboardHandler * getKeyboardHandler() const
            {
                return i8;
            }

            void updateState();
        private:
            void reset();

            LPDIRECTINPUT8 i0;
            MouseHandler * i4;
            KeyboardHandler * i8;
        };
    }
}

#endif
