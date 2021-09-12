#include "InGame.h"
#include "utilities/Rect.h"
#include "Globals.h"
#include "UnkGame1.h"
#include "Settings.h"
#include "text/Lib.h"
#include "graphics/RX.h"
#include "UnkGame2.h"
#include "UnkGame3.h"
#include "UnkGame5.h"
#include "UnkGame6.h"
#include "io/FileIo.h"
#include "io/InputHandler.h"
#include "io/MouseHandler.h"
#include "Settings.h"
#include "MiniMapMaybe.h"
#include "graphics/Font.h"
#include "UnkGame111.h"
#include "Map.h"
#include "graphics/Bitmap.h"
#include "UnkGame20.h"
#include "ArrayBriefings.h"
#include "SoundManager.h"
#include "Selection.h"
#include "UnitManager.h"
#include "HouseManager.h"
#include "HousesDat.h"
#include "PlayerStatistics.h"
#include "UnitDat.h"
#include "ClassyThree.h"
#include "RandomGenerator.h"
#include "ClassyTwo.h"
#include "GroupManager.h"
#include "ArrayUnk00.h"
#include "engine/GraphicsHandler.h"
#include "graphics/DrawableSurface.h"
#include "graphics/Palette.h"

using knights_and_merchants::engine::GraphicsHandler;
using knights_and_merchants::graphics::RX;
using knights_and_merchants::graphics::Bitmap;
using knights_and_merchants::graphics::DrawableSurface;
using knights_and_merchants::graphics::Font;
using knights_and_merchants::Settings;
using knights_and_merchants::io::FileIo;
using knights_and_merchants::io::InputHandler;
using knights_and_merchants::text::Lib;

bool testFlag = true; // TODO: Remove later
CRITICAL_SECTION criticalSection;

InGame InGame::instance;
knights_and_merchants::text::Lib * InGame::textLib;
RX * InGame::instance_guiRx;
UnkGame5 * InGame::unkGame5_instance;
UnkGame6 * InGame::unkGame6_instance;

 AnimationEntryEx InGame::mapelemDat[254];
 unsigned char InGame::patternDat[0x600];
const knights_and_merchants::graphics::Bitmap * InGame::someBitmaps[9];
 MiniMapMaybe * InGame::miniMapMaybe_instance;
 UnkGame111 * InGame::unkGame111_instance;
 UnkClass900 * InGame::unkClass900_instance;
 UnkClass1000 * InGame::unkClass1000_instance;
 UnkClass2000 * InGame::unkClass2000_instance;

 unsigned char IGUnk3::byte_493D60[8][3] = {
	{ 10, 2, 5 },
	{ 19, 2, 3 },
	{ 12, 9, 2 },
	{ 16, 9, 3 },
	{ 15, 5, 3 },
	{  2, 5, 4 },
	{ 10, 6, 4 },
	{ 19, 6, 2 }
 };

knights_and_merchants::graphics::Font * InGame::fontGame;
knights_and_merchants::graphics::Font * InGame::fontMini;
knights_and_merchants::graphics::Font * InGame::fontAntiqua;
knights_and_merchants::graphics::Font * InGame::fontOutline;
knights_and_merchants::graphics::Font * InGame::fontGrey;
knights_and_merchants::graphics::Font * InGame::fontMetal;
 int     dword_4AA664;
 int     dword_4AA660;
 int     dword_4AA650;
 int     dword_4AA648;
 int     dword_4AA674;
 int     dword_4AA680;
 int     dword_4AA66C;
 int     dword_4AA67C;
 int     dword_4AA670;
 int     dword_4AA678;
 int     dword_4AA65C;
 int     dword_4AA654;
 int     dword_4AA64C;
 int     dword_4AA658;
 int     dword_4AA668;

 void resetMap() {
	 dword_4AA664 = 0;
	 dword_4AA660 = 0;
	 dword_4AA650 = 0;
	 dword_4AA648 = 0;
	 dword_4AA674 = 0;
	 dword_4AA680 = 0;
	 dword_4AA66C = 0;
	 dword_4AA67C = 0;
	 dword_4AA670 = 0;
	 dword_4AA678 = 0;
	 dword_4AA65C = 0;
	 dword_4AA654 = 0;
	 dword_4AA64C = 0;
	 dword_4AA658 = 0;
	 dword_4AA668 = 0;
 }


 void test(DrawableSurface & p0) {
	 Bitmap(256, 256, UnkGame1::instance->i4[0]).draw(p0, 0, 0);
	 Bitmap(256, 256, UnkGame1::instance->i4[1]).draw(p0, 256, 0);
	 Bitmap(256, 256, UnkGame1::instance->i4[2]).draw(p0, 512, 0);
	 Bitmap(256, 256, UnkGame1::instance->i4[3]).draw(p0, 0, 256);


 
 }

 void sub_4023B5(DrawableSurface & surface) {
	if (InGame::instance.i28 != 0)
		InGame::instance.takeScreenshot(surface);

     knights_and_merchants::io::InputHandler::instance->getMouseHandler()->overdrawPreviousCursor(surface);

	if (Settings::instance.i268_resolution == 1 || Settings::instance.i268_resolution == 3) {
		Rect rect { 
			screenConstants[Settings::instance.i268_resolution].i8,
			0,
            screenConstants[Settings::instance.i268_resolution].width - screenConstants[Settings::instance.i268_resolution].i8,
            screenConstants[Settings::instance.i268_resolution].i12
		};

		surface.fillRectangle(rect, 3);
		rect.bottom = screenConstants[Settings::instance.i268_resolution].height;
		rect.top = screenConstants[Settings::instance.i268_resolution].height - screenConstants[Settings::instance.i268_resolution].i12;
		surface.fillRectangle(rect, 3);
	}

	if (InGame::instance.i33 != 0) {
		InGame::miniMapMaybe_instance->draw(surface);
		InGame::instance.i33 = 0;
	}

	if (InGame::instance.i32 != 0) {
		InGame::unkGame111_instance->vtable0(surface);
	}


	if (testFlag) {
		Map::instance->clearMap(0);
		Map::houseManager->spawnHouse(15, 13, House::WatchTower, 0);
		Map::houseManager->spawnHouse(10, 12, House::Storehouse, 0);

		Map::groupManager->spawnGroup(Unit::Pikeman, 0, 22, 22, 4, 3, 9);

		SoundManager::instance->playSoundAt(31, 15, 15);
		
		InGame::instance.i98[0] = 35;

		InGame::instance.i34[0][0] = 35;
		InGame::instance.i34[0][1] = 36;
		InGame::instance.i34[0][2] = 35;
		InGame::instance.i34[0][3] = 36;
		InGame::instance.i34[0][4] = 37;
		InGame::instance.i34[0][5] = 38;
		InGame::instance.i34[0][6] = 39;
		InGame::instance.i34[0][7] = 40;

		testFlag = false;
		UnkGame1::instance->unkFunc1();
		UnkGame1::instance->unkMapColor();

		Map::classyThree_instance->setField(0, 1, 20, 13);
		Map::classyThree_instance->setField(0, 1, 21, 13);
		Map::classyThree_instance->setField(0, 1, 22, 13);
		Map::classyThree_instance->setField(0, 1, 20, 14);
		Map::classyThree_instance->setField(0, 1, 21, 14);
		Map::classyThree_instance->setField(0, 1, 22, 14);

		Map::classyThree_instance->setStreet(12, 17, 0);

		Map::classyThree_instance->setStreet(13, 17, 0);
		Map::classyThree_instance->setStreet(14, 17, 0);
		Map::classyThree_instance->setStreet(14, 18, 0);

		Map::classyThree_instance->setStreet(15, 18, 0);
		Map::classyThree_instance->setStreet(15, 19, 0);

	}
	 
	if (InGame::unkGame5_instance->drawTerrain(surface, InGame::miniMapMaybe_instance->i46, InGame::miniMapMaybe_instance->i50, InGame::instance.i32)) {
		InGame::unkGame6_instance->draw(surface, InGame::miniMapMaybe_instance->i46, InGame::miniMapMaybe_instance->i50, InGame::instance.i137 == 0);
		InGame::unkGame111_instance->drawMenu(surface);
	}

	InputHandler::instance->getMouseHandler()->unkCursor(surface);
	InputHandler::instance->getMouseHandler()->drawCursor(surface);
 }

 void cleanupMap()
 {
 
 }

 void setupMapStuff()
 {
	 Map::classy0_instance = new Selection(1, 1);
	 Map::classy0_instance->setPosition(10, 10);

	 Map::classyTwo_instance = new ClassyTwo(Map::instance->i8_width, Map::instance->i12_height, 0, 0);
	 Map::class666_instance = new RandomGenerator(666);

	 Map::classyThree_instance = new ClassyThree();

	 Map::unitManager = new UnitManager(2000);

	 Map::houseManager = new HouseManager(500);

	 Map::playerStatistics = new PlayerStatistics(8);

	 Map::groupManager = new GroupManager(100);

	 Map::arrayUnk00_instance = new ArrayUnk00(3000);
 }

 void setupMap(const char * const filePath) {
	 resetMap();

	 Map::instance = (filePath != nullptr) ? new Map(filePath) : new Map(96, 96, 0);

	 setupMapStuff();

	 Map::housesDat_instance = new HousesDat("data/defines/houses.dat");
	 Map::unitDat_instance = new UnitDat("data/defines/unit.dat");

 }

void readMapelemDat(FileIo & fileIO) {
	for (int i = 0; i < 254; ++i)
		InGame::mapelemDat[i].read(fileIO);
}

void readPatternDat(FileIo & fileIO) {
	fileIO.read(InGame::patternDat, 0x600);
}

InGame::InGame()
{
}

InGame::~InGame()
{
}

bool InGame::initialize(int p0, int p4)
{
	Rect rect { };

	UnkGame2::instance.reset();

	reset();

	i130 = p0;
	i9068 = 0;
	i9072 = 0;

	if (p0 == 2) {
		i142 = (char) dword_53C57C + 1;
	} else if (p0 == 0) {
		i142 = p4;
	}

	i8 = 0;

	i141 = 0;
	i131 = 0;
	i132 = 14;

	UnkGame1::instance = new UnkGame1(Settings::instance.i0_palette);

	{
		FileIo fileIO { "data/defines/mapelem.dat" };
		readMapelemDat(fileIO);
	}

	UnkGame3::instance = new UnkGame3();

	{
		FileIo fileIO { "data/defines/pattern.dat" };
		readPatternDat(fileIO);
	}

	InGame::textLib = new Lib("data/misc/text.lib");
	InGame::instance_guiRx = new RX("data/gfx/res/gui.rx");

	for (int i = 0; i < 9; ++i)
		InGame::someBitmaps[i] = InGame::instance_guiRx->getBitmap(i);

	InputHandler::instance->getMouseHandler()->setCursor(InGame::someBitmaps[0]);

	rect.setBounds(0, 0, screenConstants[Settings::instance.i268_resolution].width, screenConstants[Settings::instance.i268_resolution].height);

	InputHandler::instance->getMouseHandler()->setMouseArea(rect);
	InputHandler::instance->getMouseHandler()->setMousePosition(400, 300);

	setupMap("data/mission/dmaps/save00.map");

	Map::instance->unk7(10, 14);
	Map::instance->unk7(11, 14);
	Map::instance->unk7(12, 14);
	Map::instance->unk7(13, 14);

	//setupMap(nullptr);

	rect.setBounds(12, 13, 128, 128);
	rect.setBounds(10, 10, 176, 176);

	InGame::miniMapMaybe_instance = new MiniMapMaybe(rect);
	InGame::miniMapMaybe_instance->unk2(
            screenConstants[Settings::instance.i268_resolution].i16,
            screenConstants[Settings::instance.i268_resolution].i20
	);

	rect.setBounds(
            screenConstants[Settings::instance.i268_resolution].i8,
            screenConstants[Settings::instance.i268_resolution].i12,
		InGame::miniMapMaybe_instance->i42,
		InGame::miniMapMaybe_instance->i44
	);


	InGame::unkGame5_instance = new UnkGame5(rect, UnkGame1::instance->i4, UnkGame1::instance->i0);
	InGame::unkGame6_instance = new UnkGame6(rect);

	for (int i = 0; i < 8; ++i)
		InGame::unkGame6_instance->i44[i] = UnkGame1::instance->i28[i];
	
	InGame::fontGame = new Font("data/gfx/fonts/game.fnt");
	InGame::fontMini = new Font("data/gfx/fonts/mini.fnt");
	InGame::fontAntiqua = new Font("data/gfx/fonts/antiqua.fnt");
	InGame::fontOutline = new Font("data/gfx/fonts/outline.fnt");
	InGame::fontGrey = new Font("data/gfx/fonts/grey.fnt");
	InGame::fontMetal = new Font("data/gfx/fonts/metal.fnt");

	rect.setBounds(
		0,
		0,
        screenConstants[Settings::instance.i268_resolution].width,
        screenConstants[Settings::instance.i268_resolution].height
	);

	InGame::unkGame111_instance = new UnkGame111(rect);

	UnkGame20::instance = new UnkGame20();

	ArrayBriefings::instance = new ArrayBriefings(50);

	GraphicsHandler::instance->setPalette(*UnkGame1::instance->i144);
	InputHandler::instance->updateState();

	InGame::unkGame111_instance->unk09();

	if (i130 == 2) {
		throw 0; // reverse
	}

	i120 = 0;
	i118 = 0;
	i116 = 0;
	i114 = 0;
	i112 = 0;
	i110 = 0;
	i108 = 0;
	i106 = 0;
	return true;
}

void InGame::reset()
{
	for (int i = 0; i < 9; ++i)
		InGame::someBitmaps[i] = nullptr;

	InGame::fontAntiqua = nullptr;
	InGame::fontOutline = nullptr;
	InGame::fontMetal = nullptr;
	InGame::fontGrey = nullptr;
	InGame::fontGame = nullptr;
	InGame::fontMini = nullptr;
	UnkGame3::instance = nullptr;
	InGame::unkGame111_instance = nullptr;
	UnkGame20::instance = nullptr;
	InGame::textLib = nullptr;

	i24 = 0;
	i20 = 0;
	i16 = 0;
	i4 = 0;
	i12 = 0;
	i0 = 0;
	i133 = 1;
	i28 = 0;
	i32 = 1;
	i33 = 1;
	i122_isTactic = 0;

	for (int i = 0; i < 8; ++i) {
		i865[i].i0 = 0;
		i865[i].i4 = 0;
		i865[i].i12 = 0;
		i865[i].i17 = 0;
		i865[i].i16 = 0;

		for (int j = 0; j < 8; ++j)
			i865[i].i18[j] = j == i;
		
		i865[i].i50.init();

		for (int j = 0; j < 10; ++j)
			i865[i].i862[j][0] = -1;
	}

	i143 = 0;
	i155 = 0;
	
	for (int i = 0; i < 12; ++i)
		i191[i].i13 = nullptr;

	for (int i = 0; i < 8; ++i)
		i34[i][0] = -1;

	for (int i = 0; i < 8; ++i)
		i98[i] = -1;
}

void InGame::cleanup()
{
	cleanupThread();
}

void InGame::cleanupThread()
{
	if (i155 == nullptr)
		return;

	DWORD exitCode;
	while (!GetExitCodeThread(i155, &exitCode));
	
	CloseHandle(i155);
	DeleteCriticalSection(&criticalSection);

	i155 = nullptr;
}

void InGame::takeScreenshot(DrawableSurface & p0)
{
}

bool InGame::setMap(const char * filePath)
{
	cleanupMap();
	setupMap(filePath);

	InGame::miniMapMaybe_instance->unk10();

	InGame::miniMapMaybe_instance->unk2(
            screenConstants[Settings::instance.i268_resolution].i16,
            screenConstants[Settings::instance.i268_resolution].i20
	);

	Map::classy0_instance->resetPosition();

	InGame::unkGame5_instance->i104 = 1;

	InGame::miniMapMaybe_instance->unk7();
	return true;
}

bool InGame::unk14()
{
	InputHandler::instance->updateState();

	i0 = GetTickCount();

	auto edi = (i0 + 50) >= (i20 + 100);

	if (i0 >= i16 + 100) {
		i32 = 1;
		i137 = edi;
		i4++;
		if (UnkGame1::instance->i144->update())
			GraphicsHandler::instance->setPalette(*UnkGame1::instance->i144);

		i16 = i0;
	}

	if (i0 > i24 + 50) {
		i33 = 1;
		i24 = i0;
	}

	if (edi) {
		i20 = i0 + 50;

		for (int i = 0; i < i133; ++i) {
			i8++;
			SoundManager::instance->freeFinishedSamples();
			Map::instance->unk19();
			Map::unitManager->unk4();
			Map::groupManager->update();

			if (i130 == 2) {
			
			} else {
			
			}

			switch (i8 % 10) {
			case 0:
				break;
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				break;
			case 6:
				break;
			case 7:
				break;
			case 8:
				break;
			}
		}
		
		edi = true;
		if (i133 > 1) {
			InGame::unkGame5_instance->i104 = 1;
		}
	} else {
		edi = true;
	}
	
	GraphicsHandler::instance->draw(sub_4023B5);
	if (!InGame::unkGame111_instance->handleInput()) {
	
		if (i130 != 2 || /*i143->i44 == 0 ||*/ i9072 != 0) {
			Settings::instance.fadeOutMusic();
			cleanup();
			return true;
		}

		i9068 = 1;
	}

	return false;
}

void InGame::unk8()
{
	i133 = (i133 == 1) ? 5 : 1;
}
