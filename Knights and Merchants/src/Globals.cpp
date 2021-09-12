#include "Globals.h"
#include "graphics/DrawableSurface.h"
#include "media/AVIClass.h"
#include "Settings.h"
#include "engine/GraphicsHandler.h"
#include "SoundManager.h"

using knights_and_merchants::utilities::Rect;
using knights_and_merchants::engine::GraphicsHandler;
using knights_and_merchants::graphics::Palette;
using knights_and_merchants::media::AVIClass;
using knights_and_merchants::Settings;
using knights_and_merchants::graphics::DrawableSurface;

unk screenConstants[4] {
        { 800,  600,  200, 0,  15, 15, 20, 0 },
        { 1024, 768,  224, 4,  20, 19, 17, -4 },
        { 1280, 960,  200, 0,  27, 24, 17, 0 },
        { 1280, 1024, 200, 12, 27, 25, 17, -12 }
};

anoUnk word_4982C0[4] {
        { 408, 550, 405, -1,  402 },
        { 409, 551, 406, 553, 403 },
        { 410, 552, 407, 554, 404 },
        { 410, 552, 407, 580, 404 }
};

// InGame globals

char soundFileNames[16][30] =
        {
                "militia",
                "axeman",
                "swordman",
                "bowman",
                "crossbow",
                "lanceman",
                "pikeman",
                "cavalry",
                "knights",
                "barbarian",
                "bowman",
                "lanceman",
                "barbarian",
                "cavalry",
                "nix",
                "nix"
        };

char actionNames[13][30] =
        {
                "SELECT",
                "SEND",
                "ATTACK",
                "HALT",
                "LEFT",
                "RIGHT",
                "EAT",
                "HALVE",
                "JOIN",
                "FORMAT",
                "DEATH",
                "STORM",
                "BATTLE"
        };


int dword_53D584;
int dword_53C57C;

HINSTANCE base_hInstance;

HWND base_hWnd;

knights_and_merchants::text::Lib * base_Lib_Setup = nullptr;

char globals_gameState;

void enterGameMode()
{
    Palette palette { };

    for (int i = 0; i < 256; ++i)
        palette.setColor(i, 0, 0, 0);

    Sleep(100);

    GraphicsHandler::instance->setDisplayMode(800, 600, 8);
    GraphicsHandler::instance->setPalette(palette);
    GraphicsHandler::instance->draw(clearScreen);

    SetCursor(nullptr);
}

void showVideo(const std::string & name)
{
    char filePath[256];
    sprintf(filePath, "Data/Gfx/Video/%s.avi", name.c_str());

    SoundManager::instance->freeSamples();
    enterVideoMode();
    Sleep(100);

    {
        AVIClass aviFile { filePath, 0, 80, 1 };

        if (aviFile.i1178 != 0)
            aviFile.unk2(*GraphicsHandler::instance);
    }

    enterGameMode();
    Sleep(100);
}

void clearScreen(DrawableSurface & surface)
{
    Rect rect { 0, 0, surface.i0_width, surface.i2_height };
    surface.fillRectangle(rect, 0);
}

void showIntro()
{
    enterVideoMode();

    Palette palette { };

    for (int i = 0; i < 256; ++i)
        palette.setColor(i, 0, 0, 0);

    GraphicsHandler::instance->setPalette(palette);
    GraphicsHandler::instance->draw(clearScreen);

    {
        AVIClass avi("data/gfx/Video/publish.avi",
                     Settings::instance.i273_video1,
                     Settings::instance.i277_video2,
                     Settings::instance.i281_video3 != 0);

        if (avi.i1178 != 0)
            avi.unk2(*GraphicsHandler::instance);
    }

    GraphicsHandler::instance->draw(clearScreen);

    {
        AVIClass avi("data/gfx/Video/KAMLOGO.avi", 0, 160, 0);

        if (avi.i1178 != 0)
            avi.unk2(*GraphicsHandler::instance);
    }

    GraphicsHandler::instance->draw(clearScreen);
}

void enterVideoMode()
{
    Palette palette { };

    for (int i = 0; i < 256; ++i)
        palette.setColor(i, 0, 0, 0);

    Sleep(500);

    GraphicsHandler::instance->setDisplayMode(640, 480, 8);
    GraphicsHandler::instance->setPalette(palette);
    GraphicsHandler::instance->draw(clearScreen);

    SetCursor(nullptr);
}

void enterInGameMode()
{
    Palette palette { };

    for (int i = 0; i < 256; ++i)
        palette.setColor(i, 0, 0, 0);

    Sleep(100);

    GraphicsHandler::instance->setDisplayMode(screenConstants[Settings::instance.i268_resolution].width, screenConstants[Settings::instance.i268_resolution].height, 8);
    GraphicsHandler::instance->setPalette(palette);
    GraphicsHandler::instance->draw(clearScreen);

    Sleep(100);
}