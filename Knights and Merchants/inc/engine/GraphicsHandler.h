#ifndef KNIGHTS_AND_MERCHANTS_ENGINE_GRAPHICS_HANDLER_H
#define KNIGHTS_AND_MERCHANTS_ENGINE_GRAPHICS_HANDLER_H

#include <cstdint>
#include <ddraw.h>

#include "graphics/Palette.h"
#include "engine/UnknownStruct.h"
#include "utilities/Rect.h"

using knights_and_merchants::utilities::Rect;

namespace knights_and_merchants::engine
{
    class DrawableSurface;

    class UnkGraphicsClass;

    using DrawProcedure = void (*)(DrawableSurface &);

    class GraphicsHandler
    {
    public:
        static GraphicsHandler * instance;

        GraphicsHandler(const Rect & screenRect, HWND hWnd, uint16_t someInt);

        GraphicsHandler(const GraphicsHandler &) = delete;

        GraphicsHandler(GraphicsHandler &&) = delete;

        GraphicsHandler & operator=(const GraphicsHandler &) = delete;

        GraphicsHandler & operator=(GraphicsHandler &&) = delete;

        ~GraphicsHandler();

        void draw(DrawProcedure drawProcedure);

        bool isResolutionAvailable(int width, int height);

        void restore();

        void setDisplayMode(int width, int height, int bitsPerPixel);

        void setPalette(const knights_and_merchants::graphics::Palette & p0);

        void showError(HRESULT result);

    private:
        LPCSTR getErrorMessage(HRESULT result);

        void reset();

        short i0;
        UnkGraphicsClass * i2;
        uint16_t i6;
        uint16_t i8;
        Rect i10;
        LPDIRECTDRAW i26;
        LPDIRECTDRAWSURFACE i30;
        LPDIRECTDRAWSURFACE i34;
        LPDIRECTDRAWPALETTE i38;
        UnknownStruct i42[6];
        HWND i96;
    };
}

#endif
