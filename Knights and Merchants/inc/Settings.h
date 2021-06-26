#ifndef KNIGHTS_AND_MERCHANTS_SETTINGS_H
#define KNIGHTS_AND_MERCHANTS_SETTINGS_H

#include "fmod.h"

namespace knights_and_merchants
{
    class Settings
    {
    public:
        static Settings instance;

        Settings(const Settings&) = delete;
        Settings(Settings&&) = delete;

        Settings& operator=(const Settings&) = delete;
        Settings& operator=(Settings&&) = delete;

        void fadeInMusic() const;
        void fadeOutMusic() const;
        static void playTrack(short trackNumber);

        void updateVolumes() const;
        void stopMusic();
        void unk4();
        void startMusic();
        void playNextTrack();
        void update();
        void readSettings();

        char i0_palette = 1;
        char i1_musicType = 2; // 0 = Off, 1 = via MIDI, 2 = On TODO: Enum?
        unsigned int i2_soundVolume = 65520;
        unsigned int i6_midiVolume = 49140;
        unsigned int i10_cd_volume = 26208;
        char i14_playerName[44] = "NoName";
        char i58_ng_playerName[200] = "Unknown";
        short i258_mouseSpeed = 15;
        int i260_autosave = 0;
        int i264_scrolling = 0;
        char i268_resolution = 3; // usually 1
        int i269_language = 0;
        int i273_video1 = 0;
        int i277_video2 = 0;
        int i281_video3 = 0;
        void * i285 = nullptr; // Most likely class pointer for MIDI stuff
        short i289_trackNumber = 0;
        bool i291_isTrackFinished = false;

    private:
        Settings() = default;


        static FSOUND_STREAM * instance_FSOUND_STREAM;

        static bool isMusicStopped;

        static signed char F_CALLBACKAPI callback(FSOUND_STREAM * stream, void * buffer, int length, void * userData);
    };
}

#endif
