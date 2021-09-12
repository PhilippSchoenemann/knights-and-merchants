#ifndef KNIGHTS_AND_MERCHANTS_ANIMATION_ENTRY_H
#define KNIGHTS_AND_MERCHANTS_ANIMATION_ENTRY_H

namespace knights_and_merchants::io
{
    class FileIo;
}

class AnimationEntry {
public:
	AnimationEntry();

	void read(knights_and_merchants::io::FileIo & fileIo);

	short i0_frames[30];
	short i60_frameCount;
	int i62;
	int i66;
};

#endif