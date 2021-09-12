#ifndef KNIGHTS_AND_MERCHANTS_UNK_GAME_5_H
#define KNIGHTS_AND_MERCHANTS_UNK_GAME_5_H

#include "utilities/Rect.h"

namespace knights_and_merchants::graphics
{
    class DrawableSurface;
}

class InGame;
class Tile;

struct someStruct {
	unsigned char * i0;
	int i4;
	int i8;
	int i12;
	int i16;
	int i20;
	int i24;
	int i28;
	int i32;
	int i36;
	int i40;
	int i44;
	int i48;
	int i52;
	int i56;
	int i60;
	int i64;
	int i68;
	int i72;
	unsigned char * i76_textureSet;
	unsigned char * i80;
	int * i84;
	int * i88;
	int i92;
	unsigned char * i96;
	int i100;
	int i104;
	int i108;
	int i112[14096]; // TODO: What is the intended array size?

};

class UnkGame5
{
public:
	static someStruct _someStruct;

	UnkGame5(const knights_and_merchants::utilities::Rect & rect, unsigned char ** p4, unsigned char * p8);
	~UnkGame5();

	void reset();

	bool drawTerrain(knights_and_merchants::graphics::DrawableSurface & p0, int p4, int p8, char & p12);

	void unk10(const knights_and_merchants::utilities::Rect & p0, int p4, int p8);

	void unk11(int p0, int p4, short & p8, short & p12);
	void unk12(int p0, int p4, int p8, int p12, short p16, short p20);
	void unk13(int p0, int p4, int p8, int p12);

	bool unk15(int p0, int p4, int p8, int p12, short p16, short p20);

	void unk16(knights_and_merchants::graphics::DrawableSurface & p0);
	void unk17(const Tile & p0);

	void unk20(bool p0, int p4);

	unsigned char * i0;
	unsigned char * i4_textureSets[4];
    knights_and_merchants::utilities::Rect i20;
    knights_and_merchants::utilities::Rect i36;
    knights_and_merchants::utilities::Rect i52;
	unsigned char * i68;
	unsigned char * i72;
	unsigned char * i76;
	int i80;
	int i84;
	int i88;
	int i92;
	int i96;
	short i100;
	short i102;
	int i104;

	int i109;
	bool i113;
	int i117;
	char i121[33];

private:

	static void sub_401910();
};

#endif