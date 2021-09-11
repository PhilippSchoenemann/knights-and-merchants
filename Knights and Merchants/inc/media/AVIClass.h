#ifndef KNIGHTS_AND_MERCHANTS_MEDIA_AVI_CLASS_H
#define KNIGHTS_AND_MERCHANTS_MEDIA_AVI_CLASS_H

#include <Windows.h>
#include <mmsystem.h>
#include <mmreg.h>
#include <Vfw.h>
#include "graphics/Palette.h"

struct FSOUND_SAMPLE;

namespace knights_and_merchants
{
    namespace engine
    {
        class GraphicsHandler;
    }

    namespace media
    {
        using knights_and_merchants::engine::GraphicsHandler;

        class AVIClass
        {
        public:
            AVIClass(const char * p0, int p4, int p8, int pC);
            ~AVIClass();

            bool unk2(GraphicsHandler & graphicsHandler);

            int i1178;

        private:
            void reset();

            bool unk3(GraphicsHandler & handler);
            void unk1(const char * p0);

            char * i0;
            PAVIFILE i4;
            PAVISTREAM i8;
            PAVISTREAM i12;
            AVISTREAMINFOA i16;
            AVISTREAMINFOA i156;
            LPBITMAPINFOHEADER i296;
            LPBITMAPINFOHEADER i300;
            HIC i304;
            void * i308;
            void * i312;
            graphics::Palette i316;
            int i1150;
            int i1154;
            int i1158;
            int i1162;
            int i1166;
            int i1170;
            int i1174;

            int i1182;
            int i1186;
            int i1190;

            int i1198;
            int i1202;
            int i1206;

            int i1214;
            WAVEFORMATEX i1218;
            FSOUND_SAMPLE * i1236;
        };
    }
}

#endif
