#pragma once

#include "ui/UnkClass200.h"


namespace knights_and_merchants::engine
{
    class Bitmap;
    class Palette;
}

using knights_and_merchants::engine::Palette;

namespace knights_and_merchants::text
{
    class Lib;
}

using knights_and_merchants::text::Lib;


namespace knights_and_merchants::graphics
{
    class Font;
    class RX;
}

using knights_and_merchants::graphics::RX;

namespace knights_and_merchants::ui::controls
{
    class ImageBox;
    class TextBox;
    class Button;
    class UnkClass672;

}


class MasterClass : public UnkClass200
{
public:
	MasterClass(int p0);
	virtual ~MasterClass();

	virtual bool vtable4(short p0, int p4, int p8) override;
	virtual void vtable12(knights_and_merchants::engine::DrawableSurface & p0, Rect & p4) override;

	void reset() noexcept;
	void someLoop(int p0);

	void createMainMenu();
	void createLoadSavegameMenu();
	void createCreditsMenu();
	void createTSKMenu();
	void createPlaySingleMapMenu();
	void updatePlaySingleMapMenu();
	void unk10();
	void unk20();

	int update();
	void draw(knights_and_merchants::engine::DrawableSurface & p0);

	void readRemap(const char * fileName);


	void updateResolutionButton(knights_and_merchants::ui::controls::Button & p0);

	
	void react();


	void unkWndProc(bool p0);

	char i882;
	int i883;
	int i887;
	char i891;
	int i892;
	int i896;
	int i900;
	Palette *  i904;
	Font * i908;
	Font * i912;
	Font * i916;
	Font * i920;
	Font * i924;
	Font * i928[5];
	Lib * i948;
	RX * i952;
	char i956;
	int i957;
	int i961;
	char i965[120];

	int i1089;

	int i1094;
	int i1098;

	int i1114;
	int i1118;
	int i1122;
	int i1126;

    knights_and_merchants::ui::controls::Button * i1134;

	int i1142;

	int i1150[6];
	int i1174;
	int i1178;

	unsigned char * i1186[5];


	int i1206;
	int i1210;
	int i1214;
	int i1218;

	int i1266;
    knights_and_merchants::ui::controls::UnkClass672 * i1270;
	int i1274;
	int i1278;
	char i1282;


	void * i1382;
	Bitmap * i1386;
	void * i1390;
	int i1394;
	int i1398;
    knights_and_merchants::ui::controls::ImageBox * i1420;
    knights_and_merchants::ui::controls::TextBox * i1424;
    knights_and_merchants::ui::controls::Button * i1432;
    knights_and_merchants::ui::controls::Button * i1436;
	int i1440;

};

