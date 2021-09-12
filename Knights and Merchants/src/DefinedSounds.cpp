#include <algorithm>

#include "DefinedSounds.h"
#include "io/FileIo.h"

using std::fill_n;

DefinedSounds::DefinedSounds()
{
	fill_n(i0, 12, -1);
	fill_n(i12, 12, -1);
}

char DefinedSounds::getSound(short p0)
{
	if (p0 != -1) {
		for (int eax = 0; eax < 12; ++eax) {
			if (i12[eax] == -1)
				break;

			if (i12[eax] == p0)
				return i0[eax];
		}
	}
	return -1;
}

bool DefinedSounds::read(knights_and_merchants::io::FileIo & fileIO)
{
	fileIO.read(i0, 12);
	fileIO.read(i12, 24);
	return true;
}
