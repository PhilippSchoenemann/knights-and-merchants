//
// Created by schoe on 07.10.2020.
//
//#define _CRT_SECURE_NO_WARNINGS 1

#include <fmod.h>
#include "media/AVIClass.h"
#include "io/FileIo.h"
#include "engine/GraphicsHandler.h"
#include "engine/DrawableSurface.h"

using knights_and_merchants::io::FileIo;
using knights_and_merchants::engine::DrawableSurface;

namespace knights_and_merchants::media
{
    unsigned char byte_498FD0;

    void * avi_i312;

    short avi_i1150;

    short avi_i1154;

    short avi_i1158;

    short avi_i1162;

    void sub_402AF9(DrawableSurface & a)
    {
        unsigned char * destination = (unsigned char *) a.i6_surface + avi_i1154 * a.i4_pitch + avi_i1150;

        int var4 = a.i4_pitch;
        if (byte_498FD0 != 0) {
            var4 = 2 * var4;
        }

        auto var10 = avi_i1158 / 8;

        auto source = (unsigned char *)avi_i312;

        for (int i = 0; i < avi_i1162; ++i) {
            auto esi = source;
            auto edi = destination;
            auto ecx = var10;

            while (ecx--) {
                *((int *)edi) = *((int *)esi);
                *((int *)edi + 1) = *((int *)esi + 1);
                esi += 8;
                edi += 8;
            }

            destination += var4;
            source += avi_i1158;
        }
    }

    AVIClass::AVIClass(const char * const p0, const int p4, const int p8, const int pC)
    {
        LONG cbFormat {4000};
        byte_498FD0 = pC;

        reset();

        char cDir[500];
        GetCurrentDirectoryA(500, cDir);

        const FileIo fileIo { p0 };
        if (fileIo.getFileSize() > 0) {
            fileIo.~FileIo();

            i1150 = p4;
            i1154 = p8;

            AVIFileInit();
            HRESULT result { AVIFileOpenA(&i4, p0, OF_SHARE_DENY_WRITE, nullptr) };
            if (result == AVIERR_OK) {

                result = AVIFileGetStream(i4, &i8, streamtypeVIDEO, 0);
                if (result == AVIERR_OK) {

                    i1190 = AVIFileGetStream(i4, &i12, streamtypeAUDIO, 0) == AVIERR_OK;

                    AVIStreamInfoA(i8, &i16, sizeof(AVISTREAMINFOA));

                    i1158 = i16.rcFrame.right - i16.rcFrame.left;
                    i1162 = i16.rcFrame.bottom - i16.rcFrame.top;
                    i1166 = i16.dwLength;
                    i1170 = i16.dwSuggestedBufferSize;

                    i308 = malloc(i1170);

                    if (i308 != nullptr) {
                        i312 = malloc(i1162 * i1158);

                        if (i312 != nullptr) {
                            i1182 = static_cast<int>(static_cast<double>(i16.dwRate) / i16.dwScale);

                            AVIStreamReadFormat(i8, 0, nullptr, &cbFormat);

                            i296 = static_cast<LPBITMAPINFOHEADER>(malloc(cbFormat));
                            i300 = static_cast<LPBITMAPINFOHEADER>(malloc(cbFormat));
                            memset(i300, 0, cbFormat);

                            AVIStreamReadFormat(i8, 0, i296, &cbFormat);

                            if (i1190 != 0) {                         
                                AVIStreamInfoA(i12, &i156, sizeof(AVISTREAMINFOA));
                                cbFormat = sizeof(WAVEFORMATEX);

                                i1206 = i156.dwSuggestedBufferSize;

                                result = AVIStreamReadFormat(i12, 0, &i1218, &cbFormat);
                                if (result == AVIERR_OK) {

                                    i1198 = i1218.nBlockAlign;
                                    i1202 = i156.dwLength;

                                    int edi;
                                    if (i1218.wBitsPerSample == 8) {
                                        edi = FSOUND_8BITS;
                                    }
                                    else if (i1218.wBitsPerSample == 16) {
                                        edi = FSOUND_16BITS;
                                    }
                                    else {
                                        edi = FSOUND_8BITS | FSOUND_SIGNED;
                                    }

                                    if (i1218.nChannels != 1) {
                                        edi |= FSOUND_STEREO;
                                    }
                                    else {
                                        edi |= FSOUND_MONO;
                                    }

                                    void * buffer = malloc(i156.dwLength * i1218.nBlockAlign);

                                    LONG plBytes;
                                    LONG plSamples;

                                    AVIStreamRead(i12, 0, i156.dwLength, buffer, i1218.nBlockAlign * i156.dwLength,
                                                  &plBytes, &plSamples);

                                    i1236 = FSOUND_Sample_Alloc(
                                        FSOUND_FREE, plSamples, edi, i1218.nSamplesPerSec, 255, 0x80, 1);


                                    unsigned int var204;
                                    unsigned int var218;
                                    void * var214;
                                    void * var208;
                                    if (FSOUND_Sample_Lock(i1236, 0, plBytes, &var214, &var208, &var218, &var204) ==
                                        TRUE) {
                                        memcpy(var214, buffer, var218);
                                        FSOUND_Sample_Unlock(i1236, var214, nullptr, var218, 0);
                                    }

                                    FSOUND_SetVolume(0, 255);
                                    FSOUND_PlaySound(0, i1236);
                                    free(buffer);

                                }
                                else {
                                    i1190 = 0;
                                }


                            }

                            SetCurrentDirectoryA(cDir);
                        }
                        else {
                            unk1("Not enough memory to allocate dest.buffer.");
                        }
                    }
                    else {
                        unk1("Not enough memory to allocate buffer.");
                    }
                }
                else {
                    unk1("Cannot get avi stream");
                }
            }
            else {
                unk1("Cannot open avi file");
            }
        }
        else {
            unk1("Cannot open avi file");
        }
    }

    AVIClass::~AVIClass()
    {
        if (i8 != nullptr)
            AVIStreamRelease(i8);

        if (i12 != nullptr)
            AVIStreamRelease(i12);

        AVIFileExit();

        if (i4 != nullptr)
            AVIFileRelease(i4);

        if (i308 != nullptr)
            free(i308);

        if (i312 != nullptr)
            free(i312);

        if (i296 != nullptr)
            free(i296);

        if (i300 != nullptr)
            free(i300);

        if (i1236 != nullptr)
            FSOUND_Sample_Free(i1236);

        reset();
    }


    void AVIClass::reset()
    {
        i0 = nullptr;
        i4 = nullptr;
        i8 = nullptr;
        i12 = nullptr;

        i296 = nullptr;
        i300 = nullptr;
        i308 = nullptr;
        i312 = nullptr;

        i1178 = 1;
        i1190 = 0;
        i1236 = nullptr;
    }


    bool AVIClass::unk2(GraphicsHandler & graphicsHandler)
    {
        if (i1178 == 0)
            return false;

        i300->biSize = sizeof(BITMAPINFOHEADER); // TODO: should be 40
        i300->biWidth = i1158;
        i300->biHeight = -i1162;
        i300->biPlanes = 1;
        i300->biBitCount = 8;

        i304 = ICLocate(ICTYPE_VIDEO, i16.fccHandler, i296, i300, ICMODE_DECOMPRESS);
        if (i304 == nullptr) {
            // TODO: reverse
        }

        auto * color = (RGBQUAD *)((char *)i296 + i296->biSize);

        UnkClass5 unk;
        for (int i = 0; i < i296->biClrUsed; ++i) {
            unk.setColor(i, color->rgbRed, color->rgbGreen, color->rgbBlue);
            ++color;
        }

        unk.setColor(0, 255, 255, 255);
        unk.setColor(255, 0, 0, 0);

        graphicsHandler.setPalette(unk);
        Sleep(500);

        HRESULT result = AVIStreamBeginStreaming(i8, 0, i1166, 1000);
        if (result != AVIERR_OK) {
            // TODO: reverse
        }

        LRESULT res = ICDecompressExBegin(i304, 0, i296, i308, 0, 0, i1158, i1162, i300, i312, 0, 0, i1158, i1162);
        if (res != 0) {
            // TODO: reverse
        }

        i1214 = 0;
        i1174 = 0;


        bool isActive = true;

        i1186 = GetTickCount();
        if ((GetAsyncKeyState(VK_ESCAPE) & 0x80) == 0) {
            while (isActive) {
                isActive = unk3(graphicsHandler);
                if ((GetAsyncKeyState(VK_ESCAPE) & 0x80) == 0x80)
                    break;
            }
        }

        ICDecompressExEnd(i304);
        return true;
    }

    bool AVIClass::unk3(GraphicsHandler & handler)
    {
        int eax;
        do {
            eax = (int)((GetTickCount() - i1186) * i1182 * 0.001);
        }
        while (eax <= i1174);

        i1174 = eax;

        if (eax > i1166)
            return false;

        SetCursor(nullptr);

        LONG plBytes;
        AVIStreamRead(i8, i1174, 1, i308, i1170, &plBytes, nullptr);

        LRESULT res = ICDecompressEx(i304, ICDECOMPRESS_HURRYUP, i296, i308, 0, 0, i1158, i1162, i300, i312, 0, 0,
                                     i1158,
                                     i1162);
        if (res != 0) {
            // TODO: reverse
            return false;
        }

        avi_i312 = i312;
        avi_i1150 = (short)i1150;
        avi_i1154 = (short)i1154;
        avi_i1158 = (short)i1158;
        avi_i1162 = (short)i1162;

        handler.draw(sub_402AF9);
        return true;
    }

    void AVIClass::unk1(const char * const p0)
    {
        if (i0 != nullptr)
            free(i0);

        i0 = (char *)malloc(strlen(p0) + 1);

        if (i0 != nullptr)
            strcpy(i0, p0);

        i1178 = 0;
    }
}
