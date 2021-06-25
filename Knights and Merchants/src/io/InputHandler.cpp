#include "initguid.h"
#include "io/InputHandler.h"
#include "io/MouseHandler.h"
#include "io/KeyboardHandler.h"
#include "utilities/Rect.h"

namespace knights_and_merchants::io
{
    InputHandler * InputHandler::instance;

    InputHandler::InputHandler(HWND hWnd, HINSTANCE hInstance, const Rect & screenRect, Bitmap * const unk)
        : i0 { nullptr }, i4 { nullptr }, i8 { nullptr }
    {
        const HRESULT result {
            DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, reinterpret_cast<void **>(&i0), nullptr)
        };
        if (result == DI_OK) {
            i4 = new MouseHandler(unk, screenRect, hWnd, i0);
            i8 = new KeyboardHandler(hWnd, i0);
        }
    }

    InputHandler::~InputHandler()
    {
        delete i4;
        delete i8;

        i0->Release();
        reset();
    }

    void InputHandler::updateState()
    {
        i4->updateState();
        i8->updateState();
    }

    void InputHandler::reset()
    {
        i0 = nullptr;
        i4 = nullptr;
        i8 = nullptr;
    }
}
