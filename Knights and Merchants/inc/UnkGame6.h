#ifndef KNIGHTS_AND_MERCHANTS_UNK_GAME_6_H
#define KNIGHTS_AND_MERCHANTS_UNK_GAME_6_H

#include "utilities/Rect.h"

namespace knights_and_merchants::graphics
{
    class DrawableSurface;
    class RX;
}

class Tile;
class Unit;

class UnkGame6 {
public:

	static char drawUnitUnkArray[8];

	static short unkTable[64];

	static void calculateUnkTable();

	UnkGame6(const knights_and_merchants::utilities::Rect & rect);
	~UnkGame6();

	void reset();
	void draw(knights_and_merchants::graphics::DrawableSurface & p0, int p4, int p8, bool p12);

	void drawUnit(knights_and_merchants::graphics::DrawableSurface & p0, int p4, int p8, Unit & p12, bool p16);

	void drawHouse(knights_and_merchants::graphics::DrawableSurface & p0, int p4, int p8, short p12);

	void drawObject(knights_and_merchants::graphics::DrawableSurface & p0, int p4, int p8, Tile & p12);

    knights_and_merchants::utilities::Rect i0;
	int i16;
	int i20;
	int i24;
	int i28;
	int i32;
	int i36;
	unsigned char * i40;
	unsigned char * i44[8];
    knights_and_merchants::graphics::RX * i76;
    knights_and_merchants::graphics::RX * i80;
    knights_and_merchants::graphics::RX * i84;
	char i88;
	short i89;
	int i91;
};

#endif