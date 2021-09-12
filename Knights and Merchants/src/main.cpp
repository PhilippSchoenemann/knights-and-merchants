#include <Windows.h>
#include "Globals.h"
#include "Settings.h"
#include "engine/GraphicsHandler.h"
#include "io/InputHandler.h"
#include "io/MouseHandler.h"
#include "io/KeyboardHandler.h"
#include "text/Lib.h"
#include "utilities/Rect.h"
#include "fmod.h"
#include "graphics/Palette.h"
#include "graphics/DrawableSurface.h"
#include "media/AVIClass.h"
#include "SoundManager.h"
#include <io.h>
#include "UnkClass900.h"
#include "UnkClass1000.h"
#include "UnkClass2000.h"
#include "UnkClass3000.h"
#include "UnkGame111.h"
#include "MasterClass.h"
#include "InGame.h"
#include "Map.h"
#include "MiniMapMaybe.h"
#include "UnkGame5.h"
#include "Globals.h"

using knights_and_merchants::text::Lib;
using knights_and_merchants::utilities::Rect;
using knights_and_merchants::engine::GraphicsHandler;
using knights_and_merchants::io::InputHandler;
using knights_and_merchants::io::KeyboardHandler;
using knights_and_merchants::Settings;
using knights_and_merchants::media::AVIClass;


char soundFileCounts[16][13];

using knights_and_merchants::graphics::Palette;
using knights_and_merchants::graphics::DrawableSurface;







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

    GraphicsHandler::instance = new GraphicsHandler(screenBounds, base_hWnd, 4);

    InputHandler::instance = new InputHandler(base_hWnd, base_hInstance, screenBounds, nullptr);
    InputHandler::instance->getMouseHandler()->setI104(static_cast<short>(Settings::instance.i258_mouseSpeed * 10 + 5));

    FSOUND_SetDriver(0);
    FSOUND_SetMixer(FSOUND_MIXER_QUALITY_AUTODETECT);

    if (FSOUND_Init(21050, 13, FSOUND_INIT_USEDEFAULTMIDISYNTH) == TRUE) {
        FSOUND_SetOutput(FSOUND_OUTPUT_DSOUND);

        SoundManager::instance = new SoundManager("data/sfx/sounds.dat");
        SoundManager::instance->setDistance(10 * Settings::instance.i268_resolution + 35);

        Settings::instance.startMusic();
        Settings::instance.i291_isTrackFinished = false;

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
        if (const auto isActive = wParam != WA_INACTIVE; isActive && InputHandler::instance != nullptr) {
            InputHandler::instance->getMouseHandler()->unk60(isActive);
            InputHandler::instance->getKeyboardHandler()->unk30(isActive);
        }
        break;
    }
    case WM_ERASEBKGND:
    {
        return 1;
    }
    case WM_ACTIVATEAPP:
    {
        if (InputHandler::instance != nullptr && GraphicsHandler::instance != nullptr && wParam == TRUE)
            GraphicsHandler::instance->restore();

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
            Settings::instance.playNextTrack();

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





void cleanupBase() {
    GraphicsHandler::instance->draw(clearScreen);
    Settings::instance.stopMusic();

    delete GraphicsHandler::instance;
    GraphicsHandler::instance = nullptr;

    delete InputHandler::instance;
    InputHandler::instance = nullptr;

    // TODO: Make sound work
    // delete instance_SoundsData;
    // instance_SoundsData = nullptr;

    delete base_Lib_Setup;
    base_Lib_Setup = nullptr;
}



bool sub_401352(int p0, int p4) {
    Rect rect { };
    enterInGameMode();

    if (!InGame::instance.initialize(p0, p4))
        return false;

    static POINT menuPositions[4] = {
            { 0, 200 },
            { 0, 368 },
            { 0, 560 },
            { 0, 624 }
    };

    short dword_53D4FC = 18;
    short dword_53D568 = 18;

    rect.setBounds(
            menuPositions[Settings::instance.i268_resolution].x,
            menuPositions[Settings::instance.i268_resolution].y,
            screenConstants[Settings::instance.i268_resolution].i8,
            448
    );

    InGame::unkClass900_instance = new UnkClass900(rect, 0);
    InGame::unkGame111_instance->addContainer(InGame::unkClass900_instance);

    InGame::unkClass1000_instance = new UnkClass1000(1);
    InGame::unkGame111_instance->addControl(InGame::unkClass1000_instance);

    InGame::unkClass2000_instance = new UnkClass2000(2);
    InGame::unkGame111_instance->addControl(InGame::unkClass2000_instance);




    rect.setBounds(0, 0, 0, 0);
    InGame::unkGame111_instance->addControl(new UnkClass3000(rect, 6, 57));

    Map::instance->unk18();
    InGame::miniMapMaybe_instance->unk7();
    InGame::unkGame5_instance->i104 = 1;

    auto & x = screenConstants[Settings::instance.i268_resolution];

    rect.setBounds(0, 1, 1, x.height - dword_53D568 - 1);
    UnkClass3000 * esi = new UnkClass3000(rect, 19, 0);
    InGame::unkGame111_instance->addControl(esi);
    esi->i21_flags |= 0x200;

    rect.setBounds(x.width - dword_53D4FC, 1, dword_53D4FC - 1, x.height - dword_53D568 - 2);
    esi = new UnkClass3000(rect, 20, 0);
    InGame::unkGame111_instance->addControl(esi);
    esi->i21_flags |= 0x200;

    rect.setBounds(1, 0, x.width - dword_53D4FC - 1, 1);
    esi = new UnkClass3000(rect, 21, 0);
    InGame::unkGame111_instance->addControl(esi);
    esi->i21_flags |= 0x200;

    rect.setBounds(1, x.height - dword_53D568, x.width - dword_53D4FC - 1, dword_53D568 - 1);
    esi = new UnkClass3000(rect, 22, 0);
    InGame::unkGame111_instance->addControl(esi);
    esi->i21_flags |= 0x200;

    rect.setBounds(0, 0, 1, 1);
    esi = new UnkClass3000(rect, 23, 0);
    InGame::unkGame111_instance->addControl(esi);
    esi->i21_flags |= 0x200;

    rect.setBounds(x.width - dword_53D4FC, 0, dword_53D4FC, 1);
    esi = new UnkClass3000(rect, 24, 0);
    InGame::unkGame111_instance->addControl(esi);
    esi->i21_flags |= 0x200;

    rect.setBounds(0, x.height - dword_53D568, 1, dword_53D568);
    esi = new UnkClass3000(rect, 25, 0);
    InGame::unkGame111_instance->addControl(esi);
    esi->i21_flags |= 0x200;

    rect.setBounds(x.width - dword_53D4FC, x.height - dword_53D568, dword_53D4FC, dword_53D568);
    esi = new UnkClass3000(rect, 26, 0);
    InGame::unkGame111_instance->addControl(esi);
    esi->i21_flags |= 0x200;

    rect.setBounds(1, 1, x.width - dword_53D4FC - 1, x.height - dword_53D568 - 1);
    esi = new UnkClass3000(rect, 18, 0);
    InGame::unkGame111_instance->addControl(esi);
    esi->i21_flags |= 0x200;
    // TODO: reverse further

    switch (p0) {

    }


    Settings::instance.fadeInMusic();
    return true;
}

bool sub_4018E3()
{
    if (dword_53D584) {

        throw 0; // Reverse here

        InputHandler::instance->updateState();

        if (InputHandler::instance->getKeyboardHandler()->unk2() == DIK_F12) {
            dword_53D584 = false;
            InGame::unkGame111_instance->vtable8();
        }

        return false;
    } else {
        return InGame::instance.unk14();
    }
}

INT WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
    unsigned char var20 = 6;

    if (!createWindow(hInstance))
        return 1;

    base_Lib_Setup = new Lib("data/misc/setup.lib");

    if (!initializeBase())
        return -1;

    showIntro();

    MasterClass * mc;
    do {
        enterGameMode();
        mc = new MasterClass(var20);
        Settings::instance.fadeInMusic();

        MSG message;
        do {
            if (PeekMessage(&message, nullptr, 0, 0, PM_NOREMOVE)) {
                if (!GetMessage(&message, nullptr, 0, 0))
                    return message.wParam;

                TranslateMessage(&message);
                DispatchMessage(&message);
            } else {
                Settings::instance.update();
                if (mc->update() == 0)
                    break;
            }
        } while(true);

        nShowCmd = mc->i891;
        auto edi = mc->i892;

        delete mc;
        mc = nullptr;

        if (nShowCmd == 3) {
            cleanupBase();
            return 0;
        }

        if (nShowCmd != 0) {
            Settings::instance.fadeOutMusic();    
        }

        globals_gameState = 1;

        if (!sub_401352(nShowCmd, edi)) {
            cleanupBase();
            DestroyWindow(base_hWnd);
            return 1;
        }

        do {
            if (!PeekMessage(&message, nullptr, 0, 0, PM_NOREMOVE)) {
                var20 = sub_4018E3();
                if (var20 != 0)
                    break;

                Settings::instance.update();
            } else {
                if (GetMessage(&message, nullptr, 0, 0) == 0) {
                    return message.wParam;
                } else {
                    TranslateMessage(&message);
                    DispatchMessage(&message);
                }
            }
        } while (true);

        if (knights_and_merchants::io::InputHandler::instance->getMouseHandler()->i84_isCursorFreezed)
            knights_and_merchants::io::InputHandler::instance->getMouseHandler()->i84_isCursorFreezed = false;

        switch (var20) {
            case 1:
                showVideo("lost");
                break;
            default:
                // TODO: show hard coded videos ...
                break;
        }

        globals_gameState = 0;
    } while (true);
}
