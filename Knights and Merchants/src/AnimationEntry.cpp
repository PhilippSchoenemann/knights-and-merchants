#include <algorithm>

#include "AnimationEntry.h"
#include "io/FileIo.h"

using std::fill_n;

AnimationEntry::AnimationEntry()
	: i60_frameCount { 0 }, i62 { 0 }, i66 { 0 }
{
	fill_n(i0_frames, 30, -1);
}

void AnimationEntry::read(knights_and_merchants::io::FileIo & fileIo)
{
	for (int i = 0; i < 30; ++i)
        fileIo.read(&i0_frames[i], 2);

    fileIo.read(&i60_frameCount, 2);
    fileIo.read(&i62, 4);
    fileIo.read(&i66, 4);
}
