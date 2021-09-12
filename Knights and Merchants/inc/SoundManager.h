#ifndef KNIGHTS_AND_MERCHANTS_SOUND_MANAGER_H
#define KNIGHTS_AND_MERCHANTS_SOUND_MANAGER_H

#include <memory>

#include "Array.h"
#include "Sound.h"

namespace knights_and_merchants::io
{
    class FileIo;
}

struct FSOUND_SAMPLE;

using std::unique_ptr;

class SoundManager : public Array<Sound> {
public:
    static SoundManager * instance;

	SoundManager(const int p0, const short p4);
	SoundManager(const char *filePath);

	~SoundManager();

	bool read(knights_and_merchants::io::FileIo & fileIO);

	void freeSamples();
	void freeFinishedSamples();

	bool playSound(int soundID);
	bool playSoundAt(int soundID, int x, int y);

	void setX(int x) { i150_x = x; }

	void setY(int y) { i154_y = y; }

    [[nodiscard]]
    int getDistance() { return i158_distance; }

	void setDistance(int distance) { i158_distance = distance; }

private:

	FSOUND_SAMPLE * loadSample(unsigned char * waveData, int waveLength, int & channel);

	void reset();

	short i32;
	short i34;
	unique_ptr<unsigned char *[]> i36_waveBuffers;
	unique_ptr<short[]> i40;
	unique_ptr<int[]> i44_waveSizes;
	int i48;
	FSOUND_SAMPLE * i52_samples[12];


	short i148_samplesLoaded;
	int i150_x;
	int i154_y;
	int i158_distance;
};

#endif 