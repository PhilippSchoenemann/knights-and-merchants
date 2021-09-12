#ifndef KNIGHTS_AND_MERCHANTS_HOUSE_H
#define KNIGHTS_AND_MERCHANTS_HOUSE_H

#include "Map.h"
#include "HousesDat.h"

namespace knights_and_merchants::graphics
{
    class Bitmap;
}

class StoreHouse;
class HouseDefineData;

class House {
public:

	enum Type : char {
		None = -1,
		Sawmill = 0,
		IronSmithy = 1,
		WeaponSmithy = 2,
		CoalMine = 3,
		IronMine = 4,
		GoldMine = 5,
		FishermansHut = 6,
		Bakery = 7,
		Farm = 8,
		Woodcutters = 9,
		ArmorSmithy = 10,
		Storehouse = 11,
		Stables = 12,
		SchoolHouse = 13,
		Quarry = 14,
		Metallurgists = 15,
		SwineFarm = 16,
		WatchTower = 17,
		TownHall = 18,
		WeaponsWorkshop = 19,
		ArmoryWorkshop = 20,
		Barracks = 21,
		Mill = 22,
		VehiclesWorkshop = 23,
		Butchers = 24,
		Tannery = 25,
		Inn = 27,
		Vineyard = 28
	};

	static bool isUsed(const House & house);

	static void setUnused(House & house);

	const HouseDefineData & getDefines() const 
	{
		return Map::housesDat_instance->i2100[i0_type];
	}

	StoreHouse & getStoreHouse();

	void unk31();
	void unk32(char p0);

	Type i0_type;
	char i1_playerID;
	char i2_x;
	char i3_y;
	short i4_currentCondition;
	char i6_visibleFlames;
	char i7; // 0 = construction site? 1 = currently built? 2 = done 3 = occupied 4 = ? 5 = ?
	short i8_houseID;
	union {
		struct {
			char i10[4];
			char i14[4];
			char i18[4];
			char i22[4];
			short i26;
			char i28;
			short i29;
			short i31;
			short i33;
			short i35_unitID;
			char i37_isOccupied;
			char i38;
			char i39;
			char i40;
		} done;
		struct {
			short i10;
			short i12;
            knights_and_merchants::graphics::Bitmap * i14;
			char i18;
			char i19[2];
			char i21[2];
			char i23[2];
			char i25[26];

		} construction;
	} i10;

	short i35_unitID;

	short i41_storeHouseID;
};

#endif