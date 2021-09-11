#include "MasterClass.h"
#include <Windows.h>
#include "InterchangeFileFormat.h"
#include "engine/GraphicsHandler.h"
#include "engine/DrawableSurface.h"
#include "graphics/Font.h"
#include "engine/Bitmap.h"
#include "io/FileIo.h"
#include <cstdio>
#include "graphics/RX.h"
#include "graphics/Palette.h"
#include "io/InputHandler.h"
#include "ui/controls/ImageBox.h"
#include "ui/controls/TextBox.h"
#include "ui/controls/Button.h"
#include "text/Lib.h"
#include "Settings.h"
#include "Globals.h"
#include "ui/controls/UnkClass672.h"
#include "ui/controls/UnkClass674.h"
#include "ui/UnkClass203.h"
#include "ui/controls/UIElement.h"
#include "io/MouseHandler.h"
#include "io/KeyboardHandler.h"

using knights_and_merchants::io::MouseHandler;
using knights_and_merchants::io::KeyboardHandler;
using knights_and_merchants::ui::controls::UIElement;

using knights_and_merchants::Settings;
using knights_and_merchants::engine::GraphicsHandler;
using knights_and_merchants::engine::DrawableSurface;
//using knights_and_merchants::graphics::Palette;
using knights_and_merchants::graphics::Color;
using knights_and_merchants::engine::Bitmap;
using knights_and_merchants::text::Lib;
using knights_and_merchants::graphics::Font;
using knights_and_merchants::graphics::RX;
using knights_and_merchants::io::FileIo;
using knights_and_merchants::io::InputHandler;

using namespace knights_and_merchants::ui::controls;


LRESULT windowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

MasterClass * instance_MasterClass;

MasterClass * instance_MasterClass2;

MasterClass::MasterClass(int p0) 
	: UnkClass200 { { 0, 0, 800, 600 } }
{
	instance_MasterClass = this;

	reset();

	GraphicsHandler::instance->draw(clearScreen);

	i904 = new Palette();
	i948 = base_Lib_Setup;
	i908 = new Font("data/gfx/fonts/maina.fnt");

	for (int i = 0; i < 256; ++i) {
		if (auto va = i908->i8[i]; va != nullptr) {
			auto len = va->i0_width * va->i2_height;
			auto * buffer = va->i12_data;
		
			while (len-- > 0) {					
				switch (*buffer) {
				case 53:
					*buffer = 0xE8;
					break;
				case 208:
					*buffer = 0xE7;
					break;
				case 233:
					*buffer = 0xE9;
					break;
				case 239:
					*buffer = 0xEA;
					break;
				}		
				++buffer;
			}
		}
	}
	
	i1390 = malloc(56160);
	i1382 = malloc(65535);

	{
		FileIo fileIo { "data/gfx/h2lremap.dat" };
		fileIo.read(i1382, 65535);
	}

	i1386 = new Bitmap(468, 60, nullptr);

	i912 = new Font("data/gfx/fonts/mainb.fnt");
	i916 = new Font("data/gfx/fonts/won.fnt");
	i920 = new Font("data/gfx/fonts/briefing.fnt");
	i924 = new Font("data/gfx/fonts/mainmapgold.fnt");

	for (int i = 0; i < 5; ++i) {
		char filePath[512];
		sprintf(filePath, "data/gfx/fonts/kmlobby%d.fnt", i);

		i928[i] = new Font(filePath);
		i928[i]->i2_height = 12;
	}

	i952 = new RX("data/gfx/res/guimain.rx");

	for (int i = 0; i < 5; ++i) {
		i1186[i] = static_cast<unsigned char*>(malloc(256));
	}

	instance_MasterClass2 = this;

	globals_gameState = 0;
	i882 = 0;
	i896 = 1;
	i900 = 1;

	readLBM("data/gfx/setup.lbm", i904);

	i904->setColor(0, 0, 0, 0);
	i904->setColor(255, 0, 0, 0);

	UnkClass201 uc201;
	uc201.i0 = i908;
	uc201.i4 = 1;
	uc201.i8 = i904->getMostSimilarColor(170, 120, 30);
	uc201.i10 = i904->getMostSimilarColor(80, 80, 140);
	uc201.i12 = i904->getMostSimilarColor(30, 30, 0);
	uc201.i14 = i904->getMostSimilarColor(20, 20, 20);
	uc201.i16 = i904->getMostSimilarColor(200, 200, 210);
	uc201.i18 = i904->getMostSimilarColor(180, 140, 10);
	uc201.i20 = i904->getMostSimilarColor(250, 250, 250);
	uc201.i22 = i904->getMostSimilarColor(180, 180, 180);
	uc201.i24 = i952->i0_bitmaps[2];
	
	setEntryI4(0, uc201);

	// TODO: From here on check for error.

	uc201.i0 = i912;
	uc201.i4 = 0;

	setEntryI4(1, uc201);

	UnkClass202 uc202;
	uc202.i4 = uc201.i10;
	uc202.i8 = uc201.i8;

	setEntryI564(0, uc202);

	uc201.i16 = i904->getMostSimilarColor(140, 140, 80);
	setEntryI4(2, uc201);

	uc201.i16 = i904->getMostSimilarColor(200, 200, 200);
	uc201.i18 = i904->getMostSimilarColor(50, 50, 50);
	uc201.i8 = i904->getMostSimilarColor(0, 0, 0);

	setEntryI4(3, uc201);

	uc201.i0 = i920;
	uc201.i4 = 1;
	uc201.i8 = 0xDF;
	uc201.i16 = 0xDF;

	setEntryI4(4, uc201);

	uc201.i0 = i928[0];
	uc201.i4 = 1;

	setEntryI4(5, uc201);

	uc201.i0 = i924;
	uc201.i4 = 1;
	uc201.i16 = 0xE9;
	uc201.i18 = 0xE9;

	setEntryI4(6, uc201);

	uc201.i0 = i928[0];

	setEntryI4(7, uc201);

	int res;
	if (p0 == 1)
		res = 10;
	else if (p0 == 2)
		res = 9;
	else
		res = 0;

	someLoop(res);

	i848->i65 |= 1;

	InputHandler::instance->updateState();
}


MasterClass::~MasterClass()
{
	// TODO: reverse Bink instance ...

	globals_gameState = 2;

    delete i904;
    delete i952;
    delete i908;
    delete i912;

	if (i1382 != nullptr)
		free(i1382);

	if (i1390 != nullptr)
		free(i1390);

    delete i1386;

	for (auto font : i928)
        delete font;

    delete i924;
    delete i916;
    delete i920;
	delete i961;
 
	// TODO: reverse this later ...................
	//if (i891 != 2)
	//	sub_4015BE();

	for (int i = 0; i < 5; ++i)
		free(i1186[i]);

	reset();
}

void MasterClass::reset() noexcept
{
	i1398 = -1;
	i1394 = 0;
	i1390 = nullptr;
	i1386 = nullptr;
	i1382 = nullptr;
	i904 = nullptr;
	i948 = nullptr;
	i952 = nullptr;
	i908 = nullptr;
	i916 = nullptr;
	i912 = nullptr;
	i920 = nullptr;
	i961 = nullptr;
	i956 = 0;
	i957 = 0;
	i1089 = 0;
	i1266 = 0;
	i1282 = 0;

	i928[0] = nullptr;
	i928[1] = nullptr;
	i928[2] = nullptr;
	i928[3] = nullptr;
	i928[4] = nullptr;
	
	i1186[0] = nullptr;
	i1186[1] = nullptr;
	i1186[2] = nullptr;
	i1186[3] = nullptr;
	i1186[4] = nullptr;
}

void MasterClass::someLoop(int p0)
{
	Rect rectangle { };

	int var4E0 = 0;
	int var4E8 = 0;

	unk10();
	unk20();

	i1214 = i1210;
	i1218 = i1210;

	i883 = p0;
	i887 = p0;

	const Bitmap * var4F0 = i952->getBitmap(0);
	const char * var4F8 = "data/gfx/setup.lbm";
	const char * var4E4 = "data/gfx/remap.dat";
	int var500 = 1;
	int var4FC = 1;

	Font * var4F4 = i908;
	Bitmap * var4EC = i952->i0_bitmaps[2];
	int var4DC = 1;
	
	switch (i883) {
	case 0:
		createMainMenu();
		var4DC = 0;
		break;
	case 1:
		break;
	case 3:
		createPlaySingleMapMenu();
		break;
	case 4:
		createLoadSavegameMenu();
		break;
	case 8:
		createCreditsMenu();
		var4E0 = 100;
		var4FC = 0;
		break;
	case 11:
		Settings::instance.fadeOutMusic();

		if (i892 == 1) {
			// showVideo("Intro"); ---------------------------
			Sleep(100);
		}

		var500 = 0;
		var4FC = 0;

		if (i892 < 100) {
			var4F8 = "data/gfx/map.bbm";
			var4F0 = i952->getBitmap(12);
			var4F4 = i920;
			var4EC = i952->i0_bitmaps[13];
		} else {
			var4F8 = "data/gfx/mapgold.lbm";
			var4F0 = i952->getBitmap(21);
			var4F4 = i924;
		}

		createTSKMenu();
		break;
	case 15:
		break;
	}

	getEntryI4(0)->i24 = var4EC;
	getEntryI4(0)->i0 = var4F4;

	readRemap(var4E4);

	if (InputHandler::instance->getMouseHandler()->i56_cursor != var4F0) {
		InputHandler::instance->getMouseHandler()->setCursor(var4F0);

		if (var4E8 != 0) {
			rectangle.setBounds(0, 0, 800, 600);

			InputHandler::instance->getMouseHandler()->setMouseArea(rectangle);
			InputHandler::instance->getMouseHandler()->setMousePosition(400, 300);
		}

		GraphicsHandler::instance->draw(clearScreen);
	}

	readLBM(var4F8, i904);

	// TODO: Is strcmp correct and the palette code?
	
	if (strcmp("data/gfx/setup.lbm", var4F8) == 0) {
		HDC handle = GetWindowDC(base_hWnd);

		PALETTEENTRY entries1[10];
		GetSystemPaletteEntries(handle, 0, 10, entries1);

		PALETTEENTRY entries2[10];
		GetSystemPaletteEntries(handle, 246, 10, entries2);

		for (int i = 0; i < 10; ++i)
			i904->setColor(i, entries1[i].peRed, entries1[i].peGreen, entries1[i].peBlue);
		
		for (int i = 246; i < 256; ++i)
			i904->setColor(i, entries2[i].peRed, entries2[i].peGreen, entries2[i].peBlue);
		
		Color colors[] = {
			{ 0xFA, 0x2F, 0x2F },
			{ 0x20, 0x20, 0xFA },
			{ 0x23, 0xFA, 0x23 },
			{ 0xFA, 0x16, 0xFA },
			{ 0xFA, 0xFA, 0x16 },
			{ 0x00, 0x00, 0x00 }
		};

		Color * c = colors;
		for (int i = 0; i < 6; ++i, ++c)
			i904->setColor((unsigned char) (i - 36), c);
		
		ReleaseDC(base_hWnd, handle);
	}
	

	GraphicsHandler::instance->setPalette(*i904);

	i904->setColor(0, 0, 0, 0);
	i904->setColor(255, 0, 0, 0);

	if (var500 != 0) {
		if (var4DC != 0) {
			rectangle.setBounds(10, 160 - var4E0, i952->i0_bitmaps[4]->i0_width, i952->i0_bitmaps[4]->i2_height);

			addControl( new ImageBox(rectangle, i952->i0_bitmaps[4]) );

			rectangle.setBounds(570, 160 - var4E0, i952->i0_bitmaps[5]->i0_width, i952->i0_bitmaps[5]->i2_height);

		} else {
			rectangle.setBounds(540, 160 - var4E0, i952->i0_bitmaps[5]->i0_width, i952->i0_bitmaps[5]->i2_height);
		}

		addControl( new ImageBox(rectangle, i952->i0_bitmaps[5]) );
	}

	if (i883 >= 23) {
		// TODO: reverse
	}

	if (var4FC != 0) {
		rectangle.setBounds(705, 6, 140, 20);

		char rel[500];
		sprintf(rel, "V%s ", "1.471 REL");

		addControl( new TextBox(rectangle, rel, 2, 0, 1) );
	}
}

void MasterClass::createMainMenu()
{
	Rect rectangle { 56, 245, 380, 28 };
	addControl(new Button(rectangle, 2, 3, 0, 0));

	rectangle.move(0, abs(rectangle.bottom - rectangle.top) + 5);
	addControl(new Button(rectangle, 0, 1, 0, 0));

	rectangle.move(0, abs(rectangle.bottom - rectangle.top) + 5);
	addControl(new Button(rectangle, 1, 2, 0, 0));

	rectangle.move(0, abs(rectangle.bottom - rectangle.top) + 5);
	addControl(new Button(rectangle, 3, 4, 0, 0));

	rectangle.move(0, abs(rectangle.bottom - rectangle.top) + 5);
	addControl(new Button(rectangle, 8, 10, 0, 0));

	rectangle.move(0, abs(rectangle.bottom - rectangle.top) + 5);
	addControl(new Button(rectangle, 9, 11, 0, 0));

	rectangle.move(0, abs(rectangle.bottom - rectangle.top) + 5);
	addControl(new Button(rectangle, 11, 13, 0, 0));

	rectangle.move(0, abs(rectangle.bottom - rectangle.top) + 40);
	addControl(new Button(rectangle, 12, 14, 0, 16));

	rectangle.setBounds(38, 48, i952->i0_bitmaps[3]->i0_width, i952->i0_bitmaps[3]->i2_height);
	addControl(new ImageBox(rectangle, i952->i0_bitmaps[3]));

	rectangle.setBounds(0, 574, 800, 22);
	addControl(new TextBox(rectangle, "Copyright by JOYMANIA-Entertainment 1997-2001", 2, 0, 2));

	rectangle.setBounds(540, 491, 200, 22);
	addControl(new TextBox(rectangle, i948->getStringByIndex(20).c_str(), 0, 0, 2));

	rectangle.setBounds(rectangle.left, rectangle.bottom + 5, 200, 28);
	i1134 = new Button(rectangle, 68, "", 0, 0); // TODO: normally here is passed a global byte

	addControl(i1134);
	updateResolutionButton(*i1134);
}

void MasterClass::createLoadSavegameMenu()
{

	FileIo fileIO { "data/save/saves.dat" };

	Rect rect{ 280, 100, 240, 26 };
	addControl(new TextBox(rect, i948->getStringByIndex(16).c_str(), 0, 0, 2));

	rect.move(0, abs(rect.bottom - rect.top) );

	char buffer[10][120];
	char var84[120];

	if (fileIO.getFileSize() <= 0) {
		for (int i = 0; i < 10; ++i)
			strncpy(buffer[i], i948->getStringByIndex(15).c_str(), 119);
		
		strncpy(var84, i948->getStringByIndex(110).c_str(), 119);
	} else {
		fileIO.read(buffer, 1200);
	}

	for (int i = 0; i < 10; ++i) {
		addControl(new Button(rect, 16 + i, buffer[i], 0, 0));
		rect.move(0, abs(rect.bottom - rect.top) + 4);
	}

	rect.setBounds(rect.left, rect.bottom + 20, 240, 33);
	addControl(new Button(rect, 26, 75, 0, 1));
}

void MasterClass::createCreditsMenu()
{
	Rect rect { 250, 20, 300, 565 };

	i1270 = new UnkClass672(rect, 0, (char *) i948->getStringByIndex(300).c_str());
	addControl(i1270);

	rect.setBounds(15, 546, 180, 34);
	addControl(new Button(rect, 67, i948->getStringByIndex(19).c_str(), 0, 0));
}

void MasterClass::createTSKMenu()
{
	static POINT points[20] = {
		{+178, +683},
		{ +171, +468},
		{+331, +613}, 
		{+453, +639},
		{+408, +538}, 
		{+360, +433},
		{ +108, +360}, 
		{+153, +205},
		{+319, +306}, 
		{+395, +283},
		{+489, +303}, 
		{+561, +534},
		{ +748, +523}, 
		{+896, +564},
		{ +592, +302}, 
		{+834, +190},
		{ +711, +160}, 
		{+607, +54},
		{ +733, +92}, 
		{+834, +63}
	};

	Rect rect { };

	if (i892 < 100) {
		auto varF0 = 0;
		
		for (int i = 0; i < 20; ++i) {
			rect.setBounds(800 * points[i].x / 1024, 600 * points[i].y / 768, 30, 30);
			addControl(new UnkClass674(rect, i952->i0_bitmaps[i892 <= i ? 9 : 10], 0, 0x80));
		}

		// TODO: reverse loop for connection points

		rect.setBounds(0, 0, 360, 400);
		addControl(new UnkClass674(rect, i952->i0_bitmaps[14], 0, 0x80));

		rect.setBounds(20, 63, 320, 300);
		addControl(new TextBox(rect, i948->getStringByIndex(249 + i892).c_str(), 4, 0, 1));
	} else {
		// TODO: reverse
	}
}

void MasterClass::createPlaySingleMapMenu()
{
	i1440 = 0;

	Rect rect { 280, 34, 240, 26 };
	addControl(new TextBox(rect, i948->getStringByIndex(5).c_str(), 0, 0, 2));

	rect.setBounds(240, rect.bottom + 5, 320, 320);
	i1420 = new ImageBox(rect, nullptr);
	addControl(i1420);

	rect.setBounds(240, rect.bottom + 10, 320, 100);
	i1424 = new TextBox(rect, i948->getStringByIndex(30).c_str(), 0, 1, 3);
	addControl(i1424);

	i1424->i47 = i1186[0];
	rect.setBounds(10, rect.bottom + 40, 220, 30);
	addControl(new Button(rect, 67, i948->getStringByIndex(9).c_str(), 0, 0));

	rect.setBounds(255, rect.top, 140, 30);
	i1436 = new Button(rect, 4, i948->getStringByIndex(6).c_str(), 0, 0);
	addControl(i1436);

	rect.move(abs(rect.right - rect.left) + 10, 0);
	i1432 = new Button(rect, 5, i948->getStringByIndex(7).c_str(), 0, 0);
	addControl(i1432);

	rect.setBounds(570, rect.top, 220, 30);
	addControl(new Button(rect, 6, i948->getStringByIndex(8).c_str(), 0, 0));

	updatePlaySingleMapMenu();
}

void MasterClass::updatePlaySingleMapMenu()
{
	i1420->setImage(i952->i0_bitmaps[30 + i1440]);

	i1436->setEnabled(i1440 > 0);
	i1432->setEnabled(i1440 < 6);

	i1424->setText(i948->getStringByIndex(180 + i1440).c_str());
}



void MasterClass::updateResolutionButton(Button & p0)
{
	int width = screenConstants[Settings::instance.i268_resolution].width;
	int height = screenConstants[Settings::instance.i268_resolution].height;

	char buffer[300];
	if (GraphicsHandler::instance->isResolutionAvailable(width, height))
		sprintf(buffer, "%d x %d Pixel", width, height);	
	else
		strcpy(buffer, i948->getStringByIndex(21).c_str());
	
	p0.setText(buffer);
}

void MasterClass::vtable12(DrawableSurface & p0, Rect & p4)
{
	DrawableSurface ds { abs(p4.right - p4.left), abs(p4.bottom - p4.top), p0.i4_pitch, p0.i6_surface + p0.i4_pitch * p4.top + p4.left };

	switch (i883) {
	case 9:
	case 10:
		i952->i0_bitmaps[6]->draw(ds, -p4.left, -p4.top);
		break;
	case 11:
		if (i892 < 100) {
			i952->i0_bitmaps[11]->draw(ds, -p4.left, -p4.top);
			i952->i0_bitmaps[14]->draw(ds, i1274 - p4.left, i1278 - p4.top);
		} else {
			i952->i0_bitmaps[19]->draw(ds, -p4.left, -p4.top);
		}
		break;
	case 13:
	case 14:
		break;
	default:
		i952->i0_bitmaps[1]->draw(ds, -p4.left, -p4.top);
	}
}

bool MasterClass::vtable4(short p0, int p4, int p8)
{


	switch(p0) {
	case 0:
		i891 = 0;
		i887 = 11;
		i892 = 1;
		return true;
	case 1:
		i892 = 101;
		i887 = 11;
		return true;
	case 2:
		Settings::instance.fadeOutMusic();
		i891 = 0;
		i892 = 0;
		i896 = 0;
		return true;
	case 3:
		i887 = 3;
		return true;
	case 4:
		if (i1440 > 0) {
			i1440--;
			updatePlaySingleMapMenu();
		}
		return true;
	case 5:
		if (i1440 < 6) {
			i1440++;
			updatePlaySingleMapMenu();
		}
		return true;
	case 6:
		Settings::instance.fadeOutMusic();
		i891 = 0;
		i892 = i1440 + 50;
		i896 = 0;
		return true;
	case 8:
		i887 = 4;
		return true;
	case 9:
		i887 = 15;
		return true;
	case 11:
		i887 = 8;
		return true;
	case 12:
		// TODO: Save settings
		i891 = 3;
		i896 = 0;
		return true;
	case 16:
	case 17:
	case 18:
	case 19:
	case 20:
	case 21:
	case 22:
	case 23:
	case 24:
	case 25:
		{
			char fileName[2000];
			sprintf(fileName, "data/save/game%3.3d.sav", p0 - 16);

			FileIo fileIO { fileName };
			if (fileIO.getFileSize() > 0) {
				i891 = 1;
				i892 = p0 - 16;
				i896 = 0;
			}

			return true;
		}
	case 26:
	case 67:
		i887 = 0;
		return 1;
	case 68: // change resolution
		if (Settings::instance.i268_resolution != 3)
			Settings::instance.i268_resolution++;
		else
			Settings::instance.i268_resolution = 0;

		updateResolutionButton(*i1134);
		return true;
	}

	return true;
}

void MasterClass::react()
{
	auto tickCount = GetTickCount();

	i1206 = tickCount - i1210;

	if (i883 != i887) {
		someLoop(i887);
		return;
	}

	switch (i883) {
	case 8: // credits
		if (!i1270->updateScroll())
			i887 = 0;
	}

	// TODO: reverse this part later, because it seems related to multiplayer.
}

void MasterClass::unkWndProc(bool p0)
{
	if (p0) {
		i900 = 1;
		vtable8();
	}

}




void MasterClass::unk10()
{
	i848->destroyContainers();
	i848->destroyControls();

	i1098 = 0;
	i1094 = 0;
	i1178 = 0;
	i1126 = 0;
	i1122 = 0;
	i1118 = 0;
	i1114 = 0;
	i1142 = 0;
	i1174 = 0;

	for (int i = 0; i < 6; ++i)
		i1150[i] = 0;

	i900 = 1;
}

void MasterClass::unk20()
{
	i1210 = GetTickCount();
	i1206 = 0;
}




void MasterClass::drawFunction(DrawableSurface & p0) {

	instance_MasterClass->draw(p0);

	if (instance_MasterClass->i1266 != 0) {
		int i = 0;

        // TODO: Code screenshot
        do {
            char fileName[64];

            wsprintfA(fileName, "shot%.3d.pcx", i);

            FileIo fileIo { fileName };
            

            if (const auto fileSize = fileIo.getFileSize(); fileSize > 0)
                i++;
            else
                break;
        } while (true);
	}
}


int MasterClass::update()
{
	GraphicsHandler::instance->draw(MasterClass::drawFunction);

	handleEvents(InputHandler::instance->getMouseHandler(), InputHandler::instance->getKeyboardHandler());
	react();

	InputHandler::instance->updateState();

	if (InputHandler::instance->getKeyboardHandler()->unk2() == DIK_F12)
		i1266 = 1;

	if (i896 == 0)
		GraphicsHandler::instance->draw(clearScreen);

	return i896;
}

void MasterClass::draw(DrawableSurface & surface)
{
	InputHandler::instance->getMouseHandler()->overdrawPreviousCursor(surface);

	if (i900 != 0) {
		switch (i883) {
		case 9:
		case 10:
			i952->i0_bitmaps[6]->draw(surface, 0, 0);
			break;
		case 11:
			if (i892 < 0x64) {
				i952->i0_bitmaps[11]->draw(surface, 0, 0);
				i952->i0_bitmaps[14]->draw(surface, i1274, i1278);
			} else {
				i952->i0_bitmaps[19]->draw(surface, 0, 0);
			}
			break;
		case 13:
		case 14:
			break;
		default:
			i952->i0_bitmaps[1]->draw(surface, 0, 0);
		}

		i900 = 0;
	}

	vtable0(surface);

	InputHandler::instance->getMouseHandler()->unkCursor(surface);
	InputHandler::instance->getMouseHandler()->drawCursor(surface);
}

void MasterClass::readRemap(const char * fileName)
{
	FileIo fileIO{ fileName };
	
	for (int i = 0; i < 5; ++i) {
		fileIO.read(i1186[i], 0x100);
	}
}




