#include "Settings.h"
#include "fmod.h"
#include "Windows.h"
#include <cstdio>
#include "io/FileIo.h"

namespace knights_and_merchants
{
    Settings Settings::instance { };

    FSOUND_STREAM * Settings::instance_FSOUND_STREAM;

    bool Settings::dword_53D58C;

    signed char F_CALLBACKAPI Settings::callback(FSOUND_STREAM * stream, void * buffer, int length, void * userData)
    {
        if (!dword_53D58C)
            Settings::instance.i291_isMusicPlaying = 1;

        return 1;
    }


    void Settings::unk2()
    {
        dword_53D58C = true;

        if (instance_FSOUND_STREAM != nullptr) {
            fadeOutMusic();
            FSOUND_StopSound(12);
            FSOUND_Stream_Close(instance_FSOUND_STREAM);
        }

        instance_FSOUND_STREAM = nullptr;
        unk4();
    }

    void Settings::fadeOutMusic() const
    {
        int volume = static_cast<int>(i10_cd_volume / 256);

        while (volume > 0) {
            FSOUND_SetVolumeAbsolute(12, volume);
            Sleep(3);
            --volume;
        }
    }

    void Settings::fadeInMusic() const
    {
        int volume = 0;
        do {
            FSOUND_SetVolumeAbsolute(12, volume);
            Sleep(3);
            ++volume;
        }
        while (volume <= static_cast<int>(i10_cd_volume / 256));
    }

    void Settings::unk7()
    {
        if (i1_musicType != 0) {
            dword_53D58C = true;
            FSOUND_StopSound(12);

            i289_trackNumber++;
            if (i289_trackNumber >= 15)
                i289_trackNumber = 0;

            playTrack(i289_trackNumber);
            dword_53D58C = false;
        }
    }

    void Settings::unk9()
    {
        if (i291_isMusicPlaying != 0)
            unk7();

        i291_isMusicPlaying = 0;
    }

    void Settings::unk5()
    {
        unk4();
        if (i1_musicType != 0) {
            i289_trackNumber = 0;
            FSOUND_SetVolumeAbsolute(12, 0);
            FSOUND_StopSound(12);
            Sleep(100);
            playTrack(i289_trackNumber);
        }

        unk1();
        FSOUND_SetVolumeAbsolute(12, 0);
    }

    void Settings::readSettings()
    {
        knights_and_merchants::io::FileIo fileIO { "setup.cfg" };

        DWORD fileSize = fileIO.getFileSize();
        char * ebx;

        if (fileSize > 0 && (ebx = (char *)malloc(fileSize)) != nullptr) {
            fileIO.read(ebx, fileSize);

        }
    }

    void Settings::unk4()
    {
        i285 = 0;
        i289_trackNumber = 0;
    }

    void Settings::unk1() const
    {
        FSOUND_SetVolumeAbsolute(12, static_cast<int>(i10_cd_volume / 256));

        for (int channel = 0; channel < 12; ++channel)
            FSOUND_SetVolumeAbsolute(channel, static_cast<int>(i2_soundVolume / 256));
    }

    void Settings::playTrack(const short trackNumber)
    {
        char songFilePath[400];
        sprintf(songFilePath, "data/sfx/songs/track_%2.2d.sng", trackNumber);

        if (instance_FSOUND_STREAM != nullptr)
            FSOUND_Stream_Close(instance_FSOUND_STREAM);

        instance_FSOUND_STREAM = FSOUND_Stream_Open(songFilePath, FSOUND_LOOP_OFF | FSOUND_8BITS | FSOUND_MONO, 0, 0);
        FSOUND_Stream_SetEndCallback(instance_FSOUND_STREAM, callback, nullptr);
        FSOUND_Stream_Play(12, instance_FSOUND_STREAM);
        FSOUND_SetPan(12, FSOUND_STEREOPAN);
    }
}
