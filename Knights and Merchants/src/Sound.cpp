#include "Sound.h"
#include "io/FileIo.h"


void Sound::read(knights_and_merchants::io::FileIo & fileIO) {
	fileIO.read(&i0_frequency, 4);
	fileIO.read(&i4, 4);
	fileIO.read(&i8, 4);
	fileIO.read(&i12, 4);
	fileIO.read(&i16, 2);
	fileIO.read(&i18, 2);
	fileIO.read(&i20, 4);
	fileIO.read(&i24, 2);
}

bool Sound::isUsed(const Sound & p0)
{
	return p0.i24 != -1;
}

void Sound::setUnused(Sound & p0)
{
	p0.i24 = -1;
}

int Sound::getVolume()
{
	double var4 = 100 - i4 ;

	if (i4 == 0)
		i4 = 1;

	return (i4 != 100) ? static_cast<int>((var4 * var4) / -2.5) : 0;
}
