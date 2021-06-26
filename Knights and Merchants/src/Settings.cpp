#include "Settings.h"
#include "fmod.h"
#include "Windows.h"
#include <cstdio>
#include "io/FileIo.h"

namespace knights_and_merchants
{
    using io::FileIo;

    Settings Settings::instance { };

    FSOUND_STREAM * Settings::instance_FSOUND_STREAM;

    bool Settings::isMusicStopped;

    signed char F_CALLBACKAPI Settings::callback(FSOUND_STREAM * stream, void * buffer, int length, void * userData)
    {
        if (!isMusicStopped)
            Settings::instance.i291_isTrackFinished = true;

        return 1;
    }


    void Settings::stopMusic()
    {
        isMusicStopped = true;

        if (instance_FSOUND_STREAM != nullptr) {
            fadeOutMusic();
            FSOUND_StopSound(12);
            FSOUND_Stream_Close(instance_FSOUND_STREAM);
            instance_FSOUND_STREAM = nullptr;
        }

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

    void Settings::playNextTrack()
    {
        if (i1_musicType != 0) {
            isMusicStopped = true;
            FSOUND_StopSound(12);

            i289_trackNumber++;
            if (i289_trackNumber >= 15)
                i289_trackNumber = 0;

            playTrack(i289_trackNumber);
            isMusicStopped = false;
        }
    }

    void Settings::update()
    {
        if (i291_isTrackFinished)
            playNextTrack();

        i291_isTrackFinished = false;
    }

    void Settings::startMusic()
    {
        unk4();

        if (i1_musicType != 0) {
            i289_trackNumber = 0;
            FSOUND_SetVolumeAbsolute(12, 0);
            FSOUND_StopSound(12);
            Sleep(100);
            playTrack(i289_trackNumber);
        }

        updateVolumes();
        FSOUND_SetVolumeAbsolute(12, 0);
    }

    void Settings::readSettings()
    {
        const FileIo fileIo { "setup.cfg" };

        const DWORD fileSize {fileIo.getFileSize()};
        char * ebx;

        if (fileSize > 0 && (ebx = static_cast<char *>(malloc(fileSize))) != nullptr) {
            fileIo.read(ebx, fileSize);

        }
    }

    void Settings::writeSettings()
    {
        FileIo fileIo { "setup.cfg" };
        fileIo.overwrite();

        char buffer[1024];

        wsprintfA(buffer, "!%s %d \r\n", "MOUSE_SPEED", i258_mouseSpeed);
        fileIo.write(buffer, strlen(buffer));

        wsprintfA(buffer, "!%s %d \r\n", "SOUND_VOLUME", i2_soundVolume);
        fileIo.write(buffer, strlen(buffer));

        wsprintfA(buffer, "!%s %d \r\n", "MIDI_VOLUME", i6_midiVolume);
        fileIo.write(buffer, strlen(buffer));

        wsprintfA(buffer, "!%s %d \r\n", "CD_VOLUME", i10_cd_volume);
        fileIo.write(buffer, strlen(buffer));

        wsprintfA(buffer, "!%s %d \r\n", "MUSIC_TYPE", i1_musicType);
        fileIo.write(buffer, strlen(buffer));

        wsprintfA(buffer, "!%s %d \r\n", "PALETTE", i0_palette);
        fileIo.write(buffer, strlen(buffer));

        wsprintfA(buffer, "!%s %d \r\n", "AUTOSAVE", i260_autosave);
        fileIo.write(buffer, strlen(buffer));

        wsprintfA(buffer, "!%s %d \r\n", "SCROLLING", i264_scrolling);
        fileIo.write(buffer, strlen(buffer));

        wsprintfA(buffer, "!%s %d \r\n", "RESOLUTION", i268_resolution);
        fileIo.write(buffer, strlen(buffer));

        wsprintfA(buffer, "!%s %d \r\n", "LANGUAGE", i269_language);
        fileIo.write(buffer, strlen(buffer));

        wsprintfA(buffer, "!%s %d %d %d \r\n", "VIDEO", i273_video1, i277_video2, i281_video3);
        fileIo.write(buffer, strlen(buffer));

        if (i14_playerName[0] != '\0') {
            wsprintfA(buffer, "!%s %s\r\n", "PLAYER_NAME", i14_playerName);
            fileIo.write(buffer, strlen(buffer));
        }

        if (i58_ng_playerName[0] != '\0') {
            wsprintfA(buffer, "!%s %s\r\n", "NG_PLAYER_NAME", i58_ng_playerName);
            fileIo.write(buffer, strlen(buffer));
        }
    }

    void Settings::unk4()
    {
        i285 = nullptr;
        i289_trackNumber = 0;
    }

    void Settings::updateVolumes() const
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
