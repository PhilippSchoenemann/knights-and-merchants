#ifndef KNIGHTS_AND_MERCHANTS_HOUSES_DAT_H
#define KNIGHTS_AND_MERCHANTS_HOUSES_DAT_H

#include "AnimationEntry.h"
#include "DefinedSounds.h"

namespace knights_and_merchants::io
{
    class FileIo;
}

class HouseDefineData {
public:

	void read(knights_and_merchants::io::FileIo & fileIO);

	short i0_graphic1;
	short i2_graphic2;
	short i4_graphic3;
	short i6_graphic4;
	short i8_inputWareGraphics[4][5];
	short i48_outputWareGraphics[4][5];
	AnimationEntry i88[4];
	AnimationEntry i368;
	AnimationEntry i438;
	AnimationEntry i508;
	AnimationEntry i578_occupiedAnimation;
	AnimationEntry i648_flagAnimations[3];
	AnimationEntry i858_flameAnimations[8];
	short i1418[2];
	short i1422;
	char i1424;
	char i1425;
	char i1426;
	char i1427;
	char i1428[10][10];
	unsigned char i1528[2];

	short i1634;
	short i1636;
	char i1638[4];
	char i1642[4];
	char i1646;
	short i1647_maxCondition;
	short i1649_clearUpRange;
	char i1651;
	DefinedSounds i1652;
};

class HousesDat {
public:
	HousesDat(const char * filePath);
	~HousesDat();

	AnimationEntry i0[30];
	HouseDefineData i2100[29];
};

#endif