#include "HouseManager.h"
#include "Map.h"
#include "Tile.h"
#include "PlayerStatistics.h"
#include "utilities/Rect.h"
#include "HousesDat.h"
#include "graphics/Bitmap.h"
#include "ClassyThree.h"
#include "ArrayUnk00.h"
HouseManager::HouseManager(const int maxSlots)
	: Array<House> { maxSlots }
{

}

HouseManager::~HouseManager()
{
	House * house { &getElement(0) };

	auto esi { i12 + 1 };

	while (esi--) {
		if (house->i0_type != House::None && house->i7 == 1 && house->i10.construction.i14 != nullptr)
			delete house->i10.construction.i14;

		++house;
	}
}

int HouseManager::spawnHouse(int p0, int p4, House::Type p8, int p12)
{
	knights_and_merchants::utilities::Rect rect { };
	rect.setBounds(p0 - 5, p4 - 5, 10, 10);

	for (int y = rect.top; y < rect.bottom; ++y)
		for (int x = rect.left; x < rect.right; ++x)
			if ((Map::housesDat_instance->i2100[p8].i1428[y - rect.top][x - rect.left] & 1) == 1 && Map::instance->getTile(x, y).i7_unitID != -1)
				return -1;
		
	const int houseID { addSlot(p0, p4, p8, p12) };

	if (houseID != -1) {
		House & house { getElement(houseID) };
		house.i4_currentCondition = Map::housesDat_instance->i2100[p8].i1647_maxCondition;
		rect.setBounds(house.i2_x - 5, house.i3_y - 5, 10, 10);

		for (int y = rect.top; y < rect.bottom; ++y)
			for (int x = rect.left; x < rect.right; ++x)
				if ((Map::housesDat_instance->i2100[p8].i1428[y - rect.top][x - rect.left] & 1) == 1) {
					Tile & tile = Map::instance->getTile(x, y);
					tile.unk2(true);
					tile.i15 = p12;
					tile.i5_objectID = 0xFF;
				}
			
		house.unk31();
		Map::classyThree_instance->clearUpHouse(houseID, p12);

		int param;

		if (house.getDefines().i1651 == -1) {
			param = 3;
		} else {
			Map::arrayUnk00_instance->unk1(houseID, house.getDefines().i1651);
			param = (p8 != 21) ? 2 : 3;
		}

		house.unk32(param);

		rect.inflate(2, 2);

		Map::instance->unk5(rect, p12);

		// TODO

		Map::classyThree_instance->setStreet(house.getDefines().i1424 + p0, house.getDefines().i1425 + p4, p12);
	}

	return houseID;
}

int HouseManager::addSlot(int p0_x, int p4_y, House::Type p8_houseType, int p12_playerID)
{
	const int houseID { Array<House>::addSlot() };

	if (houseID != INVALID_ID) {
		House & house { getElement(houseID) };

		house.i0_type = p8_houseType;
		house.i1_playerID = p12_playerID;
		house.i2_x = p0_x;
		house.i3_y = p4_y;
		house.i4_currentCondition = 0;
		house.i6_visibleFlames = 0;
		house.i7 = 0;
		house.i8_houseID = houseID;

		Map::instance->getTile(p0_x, p4_y).i9_houseID = houseID;
		Map::playerStatistics->increaseHouseStat(p12_playerID, p8_houseType);
	}

	return houseID;
}

bool HouseManager::isHouseOwnedBy(short houseID, char playerID)
{
	const House & house { getElement(houseID) };
	return (house.i1_playerID == playerID) ? house.i0_type != -1 : false;
}
