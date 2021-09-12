#include "ArrayBriefings.h"

ArrayBriefings * ArrayBriefings::instance;



ArrayBriefings::ArrayBriefings(int p0)
	: Array<Briefing> { p0, sizeof(Briefing), Briefing::isUsed, Briefing::setUnused }
{
	reset();
}

ArrayBriefings::~ArrayBriefings()
{
	
}

void ArrayBriefings::reset()
{
	i32 = 0;
}
