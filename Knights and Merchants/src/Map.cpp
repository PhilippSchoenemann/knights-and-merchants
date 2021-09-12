#include "Map.h"
#include "Tile.h"
#include <cstdlib>
#include "io/FileIo.h"
#include <new>
#include <memory>
#include "ArrayUnkMap.h"
#include "utilities/Rect.h"
#include "Map.h"
#include "ClassyTwo.h"



using std::make_unique;
Map * Map::instance;
Selection * Map::classy0_instance;
UnitManager * Map::unitManager;
HouseManager * Map::houseManager;
 PlayerStatistics * Map::playerStatistics;
 HousesDat * Map::housesDat_instance;
 StoreHouseManager * Map::arrayStoreHouses_instance;
 UnitDat * Map::unitDat_instance;
 GroupManager * Map::groupManager;
 ClassyThree * Map::classyThree_instance;
 RandomGenerator * Map::class666_instance;
 ClassyTwo * Map::classyTwo_instance;
 ArrayUnk00 * Map::arrayUnk00_instance;

void Map::wellDontKnow(const knights_and_merchants::utilities::Rect & rect) {
}

Map::Map(const int width, const int height, const char p8)
	: i0_tiles { make_unique<Tile[]>(width * height) }, i4 { make_unique<ArrayUnkMap>(width + height) }, i8_width { width }, i12_height { height }, i16 { (int) sizeof(Tile) * width }
{	
	for (int i = 0; i < (i8_width * i12_height); ++i) {
		Tile & tile = i0_tiles[i];

		tile.i0 = 0;
		tile.i1 = 0;
		tile.i2_height = p8;
		tile.i3 = 0;
		tile.i4 = 20;
		tile.i5_objectID = 255;
		tile.i6 = 0;
		tile.i7_unitID = -1;
		tile.i9_houseID = -1;

		tile.i13_clearedFlags = 0;
		tile.i15 = 255;
		tile.i17 = 0;
		tile.i21 = 0;
		tile.i22 = 0;

		auto eax = rand() & (int) 0x80000003;
		if (eax < 0) {
			eax--;
			eax |= 0xFFFFFFFC;
			eax++;
		}

		tile.setDirection(eax);
	}
}

Map::Map(const string & mapFile)
{
	knights_and_merchants::io::FileIo fileIO { mapFile.c_str() };
	read(fileIO);
}

Map::~Map()
{
}

void Map::clearMap(int playerID)
{
	
	for (int i = 0; i < (i8_width * i12_height); ++i) {
		i0_tiles[i].i13_clearedFlags |= 1 << playerID;

		i0_tiles[i].i7_unitID = -1;
		i0_tiles[i].i15 = -1;
	}
	
}

void Map::flatMap()
{
	for (int i = 0; i < (i8_width * i12_height); ++i) {
		i0_tiles[i].i2_height = 0;
		i0_tiles[i].i3 = 0;
	}
	
}

bool Map::snapRectangleOnMap(knights_and_merchants::utilities::Rect & rect)
{
	if (rect.left < 0)
		rect.left = 0;
	else if (rect.left >= i8_width - 1)
		return false;

	if (rect.top < 0)
		rect.top = 0;
	else if (rect.top >= i12_height - 1)
		return false;

	if (rect.right >= i8_width - 1)
		rect.right = i8_width - 1;
	else if (rect.right <= 0)
		return false;

	if (rect.bottom >= i12_height - 1)
		rect.bottom = i12_height - 1;
	else if (rect.bottom <= 0)
		return false;

	return true;
}

void Map::unk5(knights_and_merchants::utilities::Rect & rect, const int p4)
{
	snapRectangleOnMap(rect);

	for (int y = rect.top; y < rect.bottom; ++y) {
		for (int x = rect.left; x < rect.right; ++x) {
			unk6(x, y);
			unk7(x, y);
		}
	}	
	
	Map::wellDontKnow(rect);
	snapRectangleOnMap(rect);
	unk8(rect, p4);
}

void Map::unk6(const int x, const int y)
{
	if (x != 0 && x < i8_width - 1 && y != 0 && y < i12_height - 1) {
		auto & ebp = getTile(x, y);

		auto ecx = ((ebp.i2_height - getTile(x, y + 1).i2_height) + (ebp.i2_height - getTile(x - 1, y).i2_height)) / 2;

		auto eax = abs(ecx);
		if (eax > 20) {
			ecx = 20 * (eax / ecx);
		}
	
		ebp.i1 = 16 + (int) (0.8 * ecx);
	}
}

void Map::unk7(const int x, const int y)
{
	auto & edi = getTile(x, y);
	edi.i4 = (abs((edi.i2_height - getTile(x, y + 1).i2_height + 40) / 2) + abs((getTile(x + 1, y).i2_height - getTile(x + 1, y + 1).i2_height + 40) / 2)) / 2 + (edi.i2_height - getTile(x + 1, y).i2_height) / 2;

}

void Map::unk8(knights_and_merchants::utilities::Rect rect, char p16)
{
	p16 = (p16 != -1) ? 0 << p16 : -1;

	auto edi = rect.getWidth();
	auto esi = rect.getHeight();

	auto * tile = &getTile(rect.left, rect.top);

	auto ecx = i8_width - edi;

	while (esi--) {
		auto w = edi;
		while (w--) {
			tile->i14 = p16;
			tile++;
		}

		tile += ecx;
	}
}

void Map::unk9(knights_and_merchants::utilities::Rect & rect)
{
	auto var18 = 0;
	auto var1C = 0;
	snapRectangleOnMap(rect);

	for (int ebx = rect.top; ebx < rect.bottom; ++ebx) {
		for (int edi = rect.left; edi < rect.right; ++edi) {
			var1C += getTile(edi, ebx).i2_height;
			var18++;
		}
	}
	
	if (var1C != 0) {
		var18 = var1C / var18;

		for (int i = rect.top; i < rect.bottom; ++i) {
			var1C = var18;
			for (int edi = rect.left; edi < rect.right; ++edi) {
				auto var14 = (getTile(edi, i).i2_height + var1C) / 2;
				getTile(edi, i).i2_height = var14;
			}
		}
	}

	rect.inflate(3, 3);
	snapRectangleOnMap(rect);
	unk5(rect, -1);
}

void Map::unk10(const int x, const int y, const int textureSet, const int textureID)
{
    knights_and_merchants::utilities::Rect rect { x - 1, y - 1, 3, 3 };

	Tile & tile = getTile(x, y);

	tile.setTextureSet(textureSet);
	tile.setTexture(textureID);

	unk5(rect, 255);
}

short Map::unk13(int p0, int p4)
{
	static char byte_4B9654[4][2];
	static char unk_4B95F0[4][2];

	byte_4B9654[0][0] = p0;
	byte_4B9654[0][1] = p4;

	auto var8 = byte_4B9654;
	auto varC = unk_4B95F0;
	auto var10 = 1;

	unk17();

	int edi;
	do {
		edi = 0;

		for (int i = 0; i < var10; ++i) {
			Map::classyTwo_instance->setPosition(var8[i][0], var8[i][1]);

			for (int ebp = 0; ebp < 4; ++ebp) {
				if (Map::classyTwo_instance->move(2 * ebp)) {
					Tile & tile = getTile(Map::classyTwo_instance->i0_x, Map::classyTwo_instance->i1_y);

					if (tile.i11 == 0) {
						if ((tile.i3 & 0x10) == 0x10) {
							if (tile.i9_houseID != -1) {
								return tile.i9_houseID;
							} else {
								varC[edi][0] = Map::classyTwo_instance->i0_x;
								varC[edi][1] = Map::classyTwo_instance->i1_y;
								edi++;
							}
						}

						tile.i11 = 1;
					}

					Map::classyTwo_instance->moveOpposite(2 * ebp);
				}
			}
		}

		auto eax = varC;
		varC = var8;
		var8 = eax;

		var10 = edi;
	} while (edi != 0);

	return -1;
}

void Map::unk15()
{
    knights_and_merchants::utilities::Rect rect { 1, 1, i8_width - 2, i12_height - 2 };
	unk5(rect, -1);
}

void Map::unk17()
{
	int tileCount { i8_width * i12_height };
	Tile * tile { &i0_tiles[0] };

	while (tileCount-- > 0) {
		tile->i11 = 0;
		tile++;
	}
}



void Map::unk18()
{
	for (int y = 1; y < i12_height - 1; ++y)
		for (int x = 1; x < i8_width - 1; ++x)
			unk6(x, y);

	for (int y = 0; y < i12_height; ++y) {
		getTile(     0, y).i1 = 0;
		getTile(i8_width - 1, y).i1 = 0;
	}

	for (int x = 0; x < i8_width; ++x) {
		getTile(x,       0).i1 = 0;
		getTile(x, i12_height - 1).i1 = 0;
	}
}

void Map::unk19()
{
	Tile * tile = &i0_tiles[0];

	int tileCount = i8_width * i12_height;
	while (tileCount--) {
		tile->i14 = 0;
		tile++;
	}
}

void Map::reset()
{
	i0_tiles = nullptr;
	i4 = nullptr;
	i8_width = 0;
	i12_height = 0;
}

bool Map::read(knights_and_merchants::io::FileIo & fileIO)
{
	int width;
	int height;

    fileIO.read(&width, 4); // TODO: bool changed to exception
    fileIO.read(&height, 4);
	//if (!fileIO.read(&width, 4) || !fileIO.read(&height, 4))
	//	return false;

	new (this) Map(width, height, 0);

	for (int i = 0; i < (i8_width * i12_height); ++i)
		i0_tiles[i].read(fileIO);

	i4->read(fileIO);
	return true;
}

bool Map::areCoordinatesValid(const int x, const int y) const
{
	return x >= 0
		&& y >= 0
		&& x <= (i8_width - 2)
		&& y <= (i12_height - 2);
}

Tile & Map::getTile(const int x, const int y)
{
	return i0_tiles[x + y * i8_width];
}

const Tile & Map::getTile(const int x, const int y) const
{
	return i0_tiles[x + y * i8_width];
}
