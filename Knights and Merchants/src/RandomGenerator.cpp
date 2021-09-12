#include "RandomGenerator.h"

RandomGenerator::RandomGenerator(const unsigned int seed)
	: i0 { 0 }, i2 { static_cast<unsigned short>(seed) }, i4 { 0 }, i6 { static_cast<unsigned short>(seed) }, i8 { 0 }, i10 { 0xFEDC }
{

}

unsigned short RandomGenerator::next(const unsigned short maximum)
{
	return i0 = calculateNext() % maximum;
}

unsigned short RandomGenerator::calculateNext()
{
	unsigned short x = i4 ^ i6;

	i8 = i4;
	i6 = i8;
	i4 = (x >> 1) | (i10 & 0x8000);

	i10 += i10;
	i10 >>= 1;

	if ((x & 1) == 1)
		i10 |= 0x8000;

	return i6;
}