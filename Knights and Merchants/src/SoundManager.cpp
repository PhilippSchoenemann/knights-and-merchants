#include "SoundManager.h"
#include "io/FileIo.h"
#include "fmod.h"

using std::make_unique;

SoundManager * SoundManager::instance;

SoundManager::SoundManager(const int p0, const short p4)
	: Array<Sound> { p0 }, i32 { static_cast<short>(p0) }, i34 { static_cast<short>(p4) }
{
	reset();

	i36_waveBuffers = make_unique<unsigned char *[]>(i34);
	i40 = make_unique<short[]>(i34);
	i44_waveSizes = make_unique<int[]>(i34);

	for (int i = 0; i < i34; ++i) {
		i36_waveBuffers[i] = nullptr;
		i40[i] = -1;
		i44_waveSizes[i] = 0;
	}
}

SoundManager::SoundManager(const char *const filePath) {
	knights_and_merchants::io::FileIo fileIO { filePath };
	read(fileIO);
	i48 = 1;
}

SoundManager::~SoundManager()
{
	for (int i = 0; i < i34; ++i)
		if (i36_waveBuffers[i] != nullptr)
			free(i36_waveBuffers[i]);
	
	reset();
}

void SoundManager::freeSamples()
{
	for (int i = 0; i < 12; ++i) {
		if (i52_samples[i] != nullptr) {
			FSOUND_Sample_Free(i52_samples[i]);
			i52_samples[i] = nullptr;
			i148_samplesLoaded--;
		}
	}
}

void SoundManager::freeFinishedSamples()
{
	for (int i = 0; i < 12; ++i) {
		if (i52_samples[i] != nullptr && !FSOUND_IsPlaying(i)) {
			FSOUND_Sample_Free(i52_samples[i]);
			i52_samples[i] = nullptr;
			i148_samplesLoaded--;
		}
	}
}

bool SoundManager::read(knights_and_merchants::io::FileIo & fileIO) {
	fileIO.read(&i32, 2);
	fileIO.read(&i34, 2);

	new (this) SoundManager(i32, i34);

	fileIO.read(i44_waveSizes.get(), 4 * i34);
	fileIO.read(i40.get(), 2 * i34);

	int buffer;

	for (int i = 0; i < i34; ++i) {
		fileIO.read(&buffer, 4);

		if (buffer != 0) {
			i36_waveBuffers[i] = (unsigned char *) malloc(i44_waveSizes[i]);
			fileIO.read(i36_waveBuffers[i], i44_waveSizes[i]);
		}
	}

	resetNRead(fileIO);

	i24 = Sound::isUsed;
	i28 = Sound::setUnused;
	return true;
}

bool SoundManager::playSoundAt(int soundID, int x, int y)
{
	if (i48 == 0)
		return false;

	if (i148_samplesLoaded > 10)
		return false;

	Sound & sound = getElement(soundID);

	if (sound.i24 == -1)
		return false;

	int res = sqrt(2) * (abs(x - i150_x) + abs(y - i154_y));
	if (res < i158_distance) {
		auto esi = sound.i4;

		if (sound.i12 != 0 && sound.i4 > sound.i18)
			esi += rand() % (3 * sound.i18) - sound.i18;

		auto ecx = 100 - ((i158_distance - res) * esi) / i158_distance;
		if (ecx < 100) {
			if (ecx < 0)
				ecx = 0;

			int channel;
			FSOUND_SAMPLE * sample = loadSample(i36_waveBuffers[sound.i24], i44_waveSizes[sound.i24], channel);
			if (sample == nullptr)
				return false;

			auto esi = 2 * (100 - ecx);
			auto eax = abs((100 * (i150_x - x)) / i158_distance + 128);

			if (esi > 255)
				esi = 255;
			else
				if (esi < 0)
					esi = 0;

			FSOUND_Sample_SetDefaults(sample, sound.i0_frequency, esi, eax, -1);
			FSOUND_PlaySound(channel, sample);
		}
		
	}

	return true;
}

bool SoundManager::playSound(int soundID)
{
	if (i48 == 0)
		return false;

	if (i148_samplesLoaded > 10)
		return false;

	Sound & sound = getElement(soundID);

	if (sound.i24 == -1)
		return false;

	int channel;
	FSOUND_SAMPLE * sample = loadSample(i36_waveBuffers[sound.i24], i44_waveSizes[sound.i24], channel);

	if (sample == nullptr)
		return false;

	FSOUND_Sample_SetDefaults(sample, sound.i0_frequency, sound.getVolume(), 0, -1);
	FSOUND_PlaySound(channel, sample);
	return true;
}

FSOUND_SAMPLE * SoundManager::loadSample(unsigned char * waveData, int waveLength, int & channel)
{
	if (waveData != nullptr) {
		for (int i = 0; i < 12; ++i) {
			if (i52_samples[i] == nullptr) {
				i52_samples[i] = FSOUND_Sample_Load(FSOUND_FREE, reinterpret_cast<char*>(waveData), FSOUND_LOADMEMORY | FSOUND_LOOP_OFF, 0, waveLength);
				i148_samplesLoaded++;

				channel = i;
				return i52_samples[i];
			}
		}
	}

	return nullptr;
}

void SoundManager::reset() {
	i36_waveBuffers = nullptr;
	i40 = nullptr;
	i44_waveSizes = nullptr;
	i48 = 0;

	for (int i = 0; i < 12; ++i)
		i52_samples[i] = nullptr;

	i148_samplesLoaded = 0;
	i150_x = 0;
	i154_y = 0;
	i158_distance = 1;
}