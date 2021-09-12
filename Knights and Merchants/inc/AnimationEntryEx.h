#ifndef KNIGHTS_AND_MERCHANTS_ANIMATION_ENTRY_EX_H
#define KNIGHTS_AND_MERCHANTS_ANIMATION_ENTRY_EX_H

#include "AnimationEntry.h"

class AnimationEntryEx : public AnimationEntry {
public:
	void read(knights_and_merchants::io::FileIo & fileIo);

	int i70;
	int i74;
	int i78;
	int i82;
	int i86;
	int i90;
	char i94;
	int i95;
};

#endif
