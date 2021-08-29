#include "initguid.h"
#include "engine/GraphicsHandler.h"
#include "engine/DrawableSurface.h"
#include "engine/UnkGraphicsClass.h"

extern HINSTANCE base_hInstance;
extern HWND base_hWnd;

namespace knights_and_merchants::engine
{
    GraphicsHandler * GraphicsHandler::instance = nullptr;

    HRESULT CALLBACK enumCallback(const LPDDSURFACEDESC surfaceDesc, const LPVOID context)
    {
        static DWORD resolutions[4][2] = {
            { 800, 600 },
            { 1024, 768 },
            { 1280, 960 },
            { 1280, 1024 }
        };

        if ((surfaceDesc->dwFlags & DDSD_WIDTH) == 0 || (surfaceDesc->dwFlags & DDSD_HEIGHT) == 0 || (surfaceDesc->dwFlags & DDSD_PIXELFORMAT) == 0)
            return DDENUMRET_OK;

        for (auto & resolution : resolutions) {
            if (resolution[0] == surfaceDesc->dwWidth && resolution[1] == surfaceDesc->dwHeight && (surfaceDesc->ddpfPixelFormat.dwFlags & DDPF_PALETTEINDEXED8) == DDPF_PALETTEINDEXED8) {
                auto ptr = static_cast<UnknownStruct *>(context);

                for (int j = 0; j < 6; ++j, ++ptr) {
                    if (ptr->i0 == 0) {
                        ptr->i1 = surfaceDesc->dwWidth;
                        ptr->i5 = surfaceDesc->dwHeight;
                        ptr->i0 = 1;
                        return DDENUMRET_OK;
                    }
                }
            }
        }

        return DDENUMRET_OK;
    }

    GraphicsHandler::GraphicsHandler(const Rect & screenRect, HWND hWnd, const uint16_t someInt)
        : i10 { }, i38 { nullptr }, i42 { }, i96 { nullptr }
    {
        reset();

        int rectWidth = screenRect.getWidth();
        i6 = static_cast<uint16_t>(rectWidth);

        int rectHeight = screenRect.getHeight();
        i8 = static_cast<uint16_t>(rectHeight);

        i0 = someInt;
        i10 = screenRect;

        if ((i0 & 4) == 4) {
            i2 = new UnkGraphicsClass(hWnd, screenRect);
        } else {

            HRESULT result { DirectDrawCreate(nullptr, &i26, nullptr) };
            if (result != DD_OK) {
                showError(result);
                return;
            }

            DWORD flags = (i0 & 1) == 0 ? DDSCL_NORMAL : DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN;
            result = i26->SetCooperativeLevel(hWnd, flags);

            if (result != DD_OK) {
                showError(result);
                i26->Release();
                return;
            }

            if ((i0 & 1) == 1) {
                DWORD bitsPerPixel = (i0 & 2) == 0 ? 8 : 16;
                result = i26->SetDisplayMode(rectWidth, rectHeight, bitsPerPixel);
            }

            if (result != DD_OK) {
                showError(result);
                i26->Release();
                return;
            }

            DDSURFACEDESC surfaceDesc { };
            surfaceDesc.dwSize = sizeof(DDSURFACEDESC);

            if ((i0 & 1) == 0) {
                surfaceDesc.dwFlags = DDSD_CAPS;
                surfaceDesc.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
            }
            else {
                surfaceDesc.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
                surfaceDesc.dwBackBufferCount = 1;
                surfaceDesc.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_COMPLEX | DDSCAPS_FLIP;
            }

            LPDIRECTDRAWSURFACE directDrawSurface;

            result = i26->CreateSurface(&surfaceDesc, &directDrawSurface, nullptr);
            if (result != DD_OK) {
                showError(result);
                i26->Release();
                return;
            }

            result = directDrawSurface->QueryInterface(IID_IDirectDrawSurface3, reinterpret_cast<void **>(&i30));
            directDrawSurface->Release();

            if (result != DD_OK) {
                showError(result);
                i26->Release();
                return;
            }

            if ((i0 & 1) == 1) {
                DDSCAPS caps { 4 };

                result = i30->GetAttachedSurface(&caps, &i34);
                if (result != DD_OK) {
                    showError(result);
                    delete i30;
                    i26->Release();
                    return;
                }
            }

            PALETTEENTRY colorTable[256];

            for (int i = 0; i < 256; ++i)
                colorTable[i] = PALETTEENTRY { static_cast<BYTE>(i), static_cast<BYTE>(i), static_cast<BYTE>(i), 0 };

            i26->CreatePalette(DDPCAPS_8BIT, colorTable, &i38, nullptr);
            i30->SetPalette(i38);

            if ((i0 & 1) == 1)
                i34->SetPalette(i38);

            i26->EnumDisplayModes(0, nullptr, &i42, enumCallback);
        }

        i96 = hWnd;
    }

    GraphicsHandler::~GraphicsHandler()
    {
        if ((i0 & 4) == 4) {
            delete i2;
        } else {
            if (i26 != nullptr)
                i26->Release();
        }

        reset();
    }

    void GraphicsHandler::reset()
    {
        i2 = nullptr;
        i26 = nullptr;
        i30 = nullptr;
        i34 = nullptr;

        for (auto & i : i42)
            i.i0 = 0;
    }

    void GraphicsHandler::restore()
    {
        if ((i0 & 4) == 0)
            i30->Restore();
    }

    LPCSTR GraphicsHandler::getErrorMessage(HRESULT result)
    {
        // TODO: Hardcoded message atm... Reverse later.
        return "DirectDraw failed to initialize.";
    }

    void GraphicsHandler::showError(HRESULT result)
    {
        MessageBoxA(i96, getErrorMessage(result), "ERROR", 0);
    }


    void GraphicsHandler::setPalette(const UnkClass5 & p0)
    {
        if ((i0 & 4) == 0) {
            const Color * color = p0.getColorPtr(0);

            PALETTEENTRY entries[256];
            for (auto & entry : entries) {
                entry.peRed = color->r;
                entry.peGreen = color->g;
                entry.peBlue = color->b;
                entry.peFlags = 0;

                ++color;
            }

            i26->WaitForVerticalBlank(DDWAITVB_BLOCKBEGIN, nullptr);
            i38->SetEntries(0, 0, 256, entries);
        }
        else {
            i2->setPalette(p0);
        }
    }

    void GraphicsHandler::draw(DrawProcedure drawProcedure)
    {
        if ((i0 & 4) == 0) {

            DDSURFACEDESC desc { };
            desc.dwSize = sizeof(DDSURFACEDESC);

            HRESULT result;
            LPDIRECTDRAWSURFACE surface = ((i0 & 1) == 0) ? i30 : i34;

            do
                result = surface->Lock(nullptr, &desc, DDLOCK_SURFACEMEMORYPTR, nullptr);
            while (result == DDERR_WASSTILLDRAWING);

            if (result == DD_OK) {
                DrawableSurface param {
                    (short)desc.dwWidth,
                    (short)desc.dwHeight,
                    (short)desc.lPitch,
                    (unsigned char *)desc.lpSurface
                };

                drawProcedure(param);

                surface->Unlock(nullptr);
            }

            if ((i0 & 1) != 0)
                i30->BltFast(0, 0, i34, &i10, DDBLTFAST_NOCOLORKEY);

        }
        else {
            DrawableSurface var78 { i6, i8, i6, static_cast<unsigned char*>(i2->i64) };

            drawProcedure(var78);
            i2->draw();
        }
    }

    bool GraphicsHandler::isResolutionAvailable(int width, int height)
    {
        if ((i0 & 1) == 0)
            return true;

        for (int i = 0; i < 6; ++i) {
            if (i42[i].i0 != 0 && i42[i].i1 == width && i42[i].i5 == height)
                return true;
        }

        return false;
    }

    void GraphicsHandler::setDisplayMode(int width, int height, int bitsPerPixel)
    {
        HRESULT result;

        if ((i0 & 4) == 0) {
            result = i26->SetDisplayMode(width, height, bitsPerPixel);
            if (result != DD_OK) {
                throw 0;
            }
        } else {
            i2->setDisplayMode(width, height);
        }

        i10.setBounds(0, 0, width, height);
        i6 = width;
        i8 = height;

        if ((i0 & 4) == 0) {
            i30->Release();

            DDSURFACEDESC surfaceDesc { };
            surfaceDesc.dwSize = sizeof(DDSURFACEDESC);
            surfaceDesc.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
            surfaceDesc.dwBackBufferCount = 1;
            surfaceDesc.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_COMPLEX | DDSCAPS_FLIP;

            LPDIRECTDRAWSURFACE surface;
            result = i26->CreateSurface(&surfaceDesc, &surface, nullptr);

            if (result != DD_OK) {
                throw 0;
            }

            result = surface->QueryInterface(IID_IDirectDrawSurface3, (void **)&i30);
            surface->Release();

            if (result != DD_OK) {
                throw 0;
            }

            DDSCAPS ddsCaps { };
            ddsCaps.dwCaps = 4;

            result = i30->GetAttachedSurface(&ddsCaps, &i34);
            if (result != DD_OK) {
                throw 0;
            }

            PALETTEENTRY entries[256];
            for (int i = 0; i < 256; ++i) {
                entries[i].peRed = i;
                entries[i].peGreen = i;
                entries[i].peBlue = i;
                entries[i].peFlags = 0;
            }

            i26->CreatePalette(DDPCAPS_8BIT, entries, &i38, nullptr);
            i30->SetPalette(i38);
            i34->SetPalette(i38);
        }
    }
}
