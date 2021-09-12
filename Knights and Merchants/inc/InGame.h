#ifndef KNIGHTS_AND_MERCHANTS_IN_GAME_H
#define KNIGHTS_AND_MERCHANTS_IN_GAME_H

#include "text/Lib.h"
#include "graphics/RX.h"
#include "AnimationEntryEx.h"

#include <Windows.h>

namespace knights_and_merchants::graphics
{
    class Bitmap;
    class DrawableSurface;
    class Font;
}

class UnkGame6;

class MiniMapMaybe;
class UnkGame5;
class UnkGame111;

class UnkClass900;
class UnkClass1000;
class UnkClass2000;



struct IGUnk3 {
	unsigned char i0[812];

	void init() {
		memset(i0, 0, sizeof(i0));

		for (int i = 0; i < 8; ++i)
			i0[byte_493D60[i][1] + 28 * byte_493D60[i][0]] = byte_493D60[i][2];	
	}

private:

	static unsigned char byte_493D60[8][3];
};



struct IGUnk1 { // sizeof = 56
	int i0;
	int i9;
	void * i13;
};

struct IGUnk2 { // sizeof = 1022
	int i0;
	int i4;

	int i12;
	char i16;
	char i17;
	int i18[8];
	IGUnk3 i50;

	char i862[10][16];
};

class InGame {
public:
	static const knights_and_merchants::graphics::Bitmap * someBitmaps[9];
	static knights_and_merchants::text::Lib * textLib;
	static MiniMapMaybe * miniMapMaybe_instance;
	static UnkGame5 * unkGame5_instance;
	static UnkGame6 * unkGame6_instance;
	static knights_and_merchants::graphics::Font * fontGame;
	static knights_and_merchants::graphics::Font * fontMini;
	static knights_and_merchants::graphics::Font * fontAntiqua;
	static knights_and_merchants::graphics::Font * fontOutline;
	static knights_and_merchants::graphics::Font * fontGrey;
	static knights_and_merchants::graphics::Font * fontMetal;
	static UnkGame111 * unkGame111_instance;
	static UnkClass900 * unkClass900_instance;
	static UnkClass1000 * unkClass1000_instance;
	static UnkClass2000 * unkClass2000_instance;

	static InGame instance;
	static knights_and_merchants::graphics::RX * instance_guiRx;

	static AnimationEntryEx mapelemDat[254];
	static unsigned char patternDat[0x600];

	static knights_and_merchants::graphics::Bitmap * guiRx_getBitmap(int i) {
		return instance_guiRx->i0_bitmaps[i];
	}

	static knights_and_merchants::graphics::Bitmap * guiRx_getHouseSign(int i) {
		return instance_guiRx->i0_bitmaps[250 + i];
	}

	static const std::string & getTextLibString(int i) {
		return textLib->getStringByIndex(i);
	}


	InGame();
	~InGame();

	bool initialize(int p0, int p4);

	void reset();
	void cleanup();
	void cleanupThread();

	void takeScreenshot(knights_and_merchants::graphics::DrawableSurface & p0);

	bool setMap(const char * map);
	bool unk14();

	void unk8();

	int i0;
	int i4;
	int i8;
	int i12;
	int i16;
	int i20;
	int i24;
	int i28;
	char i32;
	char i33;
	char i34[8][8];
	unsigned char i98[8];
	short i106;
	short i108;
	short i110;
	short i112;
	short i114;
	short i116;
	short i118;
	short i120;
	int i122_isTactic;

	char i128;
	char i129_humanPlayerID;
	char i130;
	char i131;
	char i132;
	int i133;
	int i137;
	char i141;
	char i142;
	int i143;

	int i151;
	HANDLE i155;

	int i163;
	int i167;
	int i171;
	int i175;
	int i179;
	int i183;

	IGUnk1 i191[12];
	short i863;
	IGUnk2 i865[8];

	int i9068;
	int i9072;
};

#endif