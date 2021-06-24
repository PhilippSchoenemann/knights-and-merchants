#include <Windows.h>
#include "Globals.h"
#include "Settings.h"
#include "engine/GraphicsHandler.h"
#include "engine/InputHandler.h"
#include "engine/MouseHandler.h"
#include "text/Lib.h"
#include "utilities/Rect.h"
#include "fmod.h"

#include <io.h>

using knights_and_merchants::text::Lib;
using knights_and_merchants::utilities::Rect;
using knights_and_merchants::engine::GraphicsHandler;
using knights_and_merchants::engine::InputHandler;

HINSTANCE base_hInstance;

HWND base_hWnd;

char soundFileCounts[16][13];

void sub_401B7C()
{
    auto var508 = &soundFileCounts[0];
    for (auto & soundFileName : soundFileNames) {
        auto soundCount = 0;

        for (auto & actionName : actionNames) {
            for (int ebx = 0; ebx < 9; ++ebx) {
                char fileName[1000];
                _finddata64i32_t var500;

                wsprintfA(fileName, "Data/Sfx/Speech/%s/%s%d.snd", soundFileName, actionName, ebx);
                auto eax = _findfirst(fileName, &var500);

                if (eax == -1) {
                    (*var508)[soundCount] = ebx;
                    break;
                    
                }

                _findclose(eax);
            }

            soundCount++;
        }

        var508++;
    }

}

bool initializeBase() {
    const Rect screenBounds{ 0, 0, 800, 600 };

    sub_401B7C();
    Settings::instance.readSettings();

    GraphicsHandler::instance = new GraphicsHandler(screenBounds, base_hWnd, 1);

    InputHandler::instance = new InputHandler(base_hWnd, base_hInstance, screenBounds, nullptr);
    InputHandler::instance->getMouseHandler()->setI104(Settings::instance.i258_mouseSpeed * 10 + 5);

    FSOUND_SetDriver(0);
    FSOUND_SetMixer(FSOUND_MIXER_QUALITY_AUTODETECT);

    if (FSOUND_Init(21050, 13, FSOUND_INIT_USEDEFAULTMIDISYNTH) == TRUE) {
        FSOUND_SetOutput(FSOUND_OUTPUT_DSOUND);

        //instance_SoundsData = new SoundManager("data/sfx/sounds.dat");
        //instance_SoundsData->setDistance(10 * Settings::instance.i268_resolution + 35);
        //instance_SoundsData->i158 = 10 * Settings::instance.i268_resolution + 35;

        Settings::instance.unk5();
        Settings::instance.i291_isMusicPlaying = 0;

        if (InputHandler::instance != nullptr && GraphicsHandler::instance != nullptr)
            return true;
    }

    return false;
}

LRESULT CALLBACK windowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_DESTROY:
    {
        //  if (globals_gameState == 1)
        //      InGame::instance.cleanup();

        //  cleanupBase();
        PostQuitMessage(0);
        break;
    }
    case WM_ACTIVATE:
    {
        bool isActive = wParam != WA_INACTIVE;
        // if (isActive && InputHandler::instance != nullptr) {
        //     InputHandler::instance->getMouseHandler()->unk60(isActive);
        //     InputHandler::instance->getKeyboardHandler()->unk30(isActive);
        // }
        break;
    }
    case WM_ERASEBKGND:
    {
        return 1;
    }
    case WM_ACTIVATEAPP:
    {
        // if (InputHandler::instance != nullptr && GraphicsHandler::instance != nullptr && wParam == TRUE)
        //     GraphicsHandler::instance->restore();

        // if (globals_gameState == 0) {
        //     if (wParam == TRUE && instance_MasterClass != nullptr)
        //         instance_MasterClass->unkWndProc(true);
        // }
        // else if (globals_gameState == 1) {
        if (wParam == TRUE) {
            //        if (InGame::unkGame111_instance != nullptr)
            //            InGame::unkGame111_instance->vtable8();

             //       if (dword_53D584) {
             //           InGame::instance.i33 = 1;
             //           InGame::instance.i32 = 1;
             //       }
        }
        //  }

        break;
    }
    case WM_SETCURSOR:
    {
        SetCursor(nullptr);
        return 1;
    }
    case MM_MCINOTIFY:
    {
        if (wParam == MCI_NOTIFY_SUCCESSFUL)
            Settings::instance.unk7();

        break;
    }
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

bool createWindow(const HINSTANCE hInstance) {
    const auto className = "JOYMANIA";

    WNDCLASS windowClass{
        CS_DBLCLKS,
        windowProcedure,
        0,
        0,
        hInstance,
        LoadIcon(hInstance, MAKEINTRESOURCE(102)),
        LoadCursor(nullptr, IDC_ARROW),
        nullptr,
        nullptr,
        className
    };

    if (!RegisterClass(&windowClass))
        return false;

    base_hInstance = hInstance;

    base_hWnd = CreateWindowEx(
        WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR,
        className,
        "Knights&Merchants TPR",
        WS_VISIBLE | WS_POPUP,
        0,
        0,
        screenConstants[Settings::instance.i268_resolution].width,
        screenConstants[Settings::instance.i268_resolution].height,
        nullptr,
        nullptr,
        hInstance,
        nullptr
    );

    if (base_hWnd == nullptr)
        return false;

    UpdateWindow(base_hWnd);
    return true;
}

Lib* base_Lib_setup;

INT WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
    unsigned char var20 = 6;

    if (!createWindow(hInstance))
        return 1;

    //base_Lib_setup = new Lib("data/misc/setup.lib");

    if (!initializeBase())
        return -1;

    return 0;
}
