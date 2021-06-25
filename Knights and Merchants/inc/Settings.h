#ifndef KNIGHTS_AND_MERCHANTS_SETTINGS_H
#define KNIGHTS_AND_MERCHANTS_SETTINGS_H

#include "fmod.h"

namespace knights_and_merchants
{
    class Settings
    {
    public:
        static Settings instance;

        void fadeInMusic() const;
        void fadeOutMusic() const;
        static void playTrack(short trackNumber);


        void unk1() const;
        void unk2();
        void unk4();
        void unk5();
        void unk7();
        void unk9();
        void readSettings();

        char i0_palette = 1;
        char i1_musicType = 2;
        unsigned int i2_soundVolume = 65520;
        int i6_midiVolume = 49140;
        unsigned int i10_cd_volume = 26208;
        char i14_playerName[44];
        char i58_ng_playerName[200];
        short i258_mouseSpeed = 15;
        int i260_autosave = 0;
        int i264_scrolling = 0;
        char i268_resolution = 3; // normally 1
        int i269_language = 0;
        int i273_video1 = 0;
        int i277_video2 = 0;
        int i281_video3 = 0;
        int i285 = 0;
        short i289_trackNumber = 0;
        char i291_isMusicPlaying = 0;

    private:
        Settings() = default;

        static FSOUND_STREAM * instance_FSOUND_STREAM;

        static bool dword_53D58C;

        static signed char F_CALLBACKAPI callback(FSOUND_STREAM * stream, void * buffer, int length, void * userData);
    };
}

#endif
