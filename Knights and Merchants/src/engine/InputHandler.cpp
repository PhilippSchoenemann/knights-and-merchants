#include "initguid.h"
#include "engine/InputHandler.h"
#include "engine/MouseHandler.h"
#include "engine/KeyboardHandler.h"
#include "utilities/Rect.h"

//using knights_and_merchants::utilities::Rect;

namespace knights_and_merchants::engine
{



    InputHandler* InputHandler::instance;

    InputHandler::InputHandler(HWND hWnd, HINSTANCE hInstance, const Rect& screenRect, Bitmap* const unk)
        : i0{ nullptr }, i4{ nullptr }, i8{ nullptr }
    {
        HRESULT result{ DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&i0, nullptr) };
        if (result == DI_OK) {
            i4 = new MouseHandler(unk, screenRect, hWnd, i0);
            i8 = new KeyboardHandler(hWnd, i0);
        }
    }

    InputHandler::~InputHandler()
    {
        if (i4 != nullptr)
            delete i4;

        if (i8 != nullptr)
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