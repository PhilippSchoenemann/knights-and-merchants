#include "UnkClass1000.h"



UnkClass1000::UnkClass1000(int p0)
	: UIElement { { 10, 10, 176, 176 }, p0, 0, -1 }
{
	i21_flags |= 0x5000; // TODO: check if correct
}

UnkClass1000::~UnkClass1000()
{
}
