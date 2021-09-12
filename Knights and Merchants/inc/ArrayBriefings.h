#ifndef KNIGHTS_AND_MERCHANTS_ARRAY_BRIEFINGS_H
#define KNIGHTS_AND_MERCHANTS_ARRAY_BRIEFINGS_H

#include "Array.h"

struct Briefing {
	int i0;
	void * i5;

	static bool isUsed(const Briefing & p0)
	{
		return p0.i5 != nullptr;
	}

	static void setUnused(Briefing & p0)
	{
		p0.i5 = nullptr;
	}

};

class ArrayBriefings : public Array<Briefing> {
public:
	static ArrayBriefings * instance;

	ArrayBriefings(int p0);
	~ArrayBriefings();

	void reset();

	int i32;
};

#endif