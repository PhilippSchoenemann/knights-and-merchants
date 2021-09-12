#include "Tile.h"
#include "io/FileIo.h"

int Tile::getObjectAnimationDelta()
{
	return (i3 >> 2) & 3;
}

int Tile::getTextureSet()
{
	return i0 >> 6;
}

int Tile::getTexture()
{
	return i0 & 0x3F;
}

void Tile::setTextureSet(const int textureSet)
{
	i0 = (textureSet << 6) | (i0 & 0x3F);
}

void Tile::setTexture(const int textureID)
{
	i0 = (i0 & 0xC0) | textureID;
}

void Tile::setDirection(const int direction)
{
	i3 = (i3 & 0xFC) | direction;
}

void Tile::read(knights_and_merchants::io::FileIo & fileIO)
{
	fileIO.read(&i0,  1);
	fileIO.read(&i1,  1);
	fileIO.read(&i2_height,  1);
	fileIO.read(&i3,  1);
	fileIO.read(&i4,  1);
	fileIO.read(&i5_objectID,  1);
	fileIO.read(&i6,  1);
	fileIO.read(&i7_unitID,  2);
	fileIO.read(&i9_houseID,  2);
	fileIO.read(&i11, 2);
	fileIO.read(&i13_clearedFlags, 1);
	fileIO.read(&i14, 1);
	fileIO.read(&i15, 1);
	fileIO.read(&i16, 1);
	fileIO.read(&i17, 4);
	fileIO.read(&i21, 1);
	fileIO.read(&i22, 1);
}

void Tile::unk2(const bool p0)
{
	if (p0)
		i3 |= 0x10;
	else
		i3 &= 0xEF;
}

void Tile::unk11(const char p0)
{
	i21 = (i21 & 0xF0) | p0;
}

void Tile::unk8(const char p0, const char p4)
{
	i22 = (p4 << 4) | p0;
}
