#include "UnitManager.h"
#include "Map.h"
#include "Tile.h"
#include "PlayerStatistics.h"
#include "UnitDat.h"
#include "ClassyThree.h"
#include "HouseManager.h"
#include "GroupManager.h"

UnitManager::UnitManager(const int maxSlots)
	: Array<Unit> { maxSlots }
{

}


int UnitManager::spawnUnit(Unit::Type type, int player, int x, int y)
{
	int unitID { addSlot() };

	if (unitID == INVALID_ID)
		return INVALID_ID;

	Unit & unit = getElement(unitID);

	Tile & tile = Map::instance->getTile(x, y);

	if (tile.i7_unitID == INVALID_ID)
		tile.i7_unitID = unitID;

	unit.i0_type = type;
	unit.i8_x = x;
	unit.i9_y = y;
	unit.i10_direction = 5;

	if (type >= Unit::Wolf) {
		unit.unk3();
		unit.unk4();

		unit.i24 = 0;
		unit.i14 = 0;
		unit.i11 = -1;

		unit.unk7(1);
		unit.unk8(0);

		unit.i56 = -1;
		unit.i57 = -1;
		unit.i12 = -1;
		unit.i19 = -1;
		unit.i1 = 4;

		char x = unit.getDefines().i16;

		if (x < 2 || x > 3) {
			unit.i3_player = 7;
		} else {
			unit.i3_player = 6;
		}

		return unitID;
	} 

	unit.i3_player = player;
	unit.i24 = 0;
	unit.i11 = -1;
	unit.i4 = 0;
	unit.i12 = -1;
	unit.i20 = -1;
	unit.i16_hunger = 150;

	if (type == Unit::Catapult || type == Unit::Ballista)
		unit.i16_hunger = 250;

	unit.unk7(0);
	unit.unk8(0);

	unit.i56 = -1;
	unit.i57 = -1;
	unit.i19 = -1;

	unit.unk9();
	unit.unk3();
	unit.unk4();

	unit.i14 = 0;

	Map::playerStatistics->unk4(player, type);

	if (unit.i0_type >= Unit::Militia && unit.i0_type <= Unit::Ballista) {
		unit.i45 = 0;
		unit.i49_isGroupLeader = false;
		unit.i50 = 0;

		auto groupType = unit.getGroupType();
		if (Map::groupManager->createGroupFromUnit(unitID) == GroupManager::INVALID_ID) {

			short bp = Map::groupManager->i32_groupCounts[unit.i3_player];
			Group * group = &Map::groupManager->getElement(0);

			for (int i = 0; i <= Map::groupManager->i12; ++i) {
				
				if (group->i1_groupType != -1 && group->i0_playerID == unit.i3_player && group->i1_groupType == groupType) {
					if (bp == 0) {
						killUnit(unitID);
						return INVALID_ID;
					} else {
						if (group->addUnit(unitID))
							break;

						bp--;
					}
				}

				group++;
			}
		}
	}

	Map::classyThree_instance->clearUpUnit(unit);
	return unitID;
}

void UnitManager::killUnit(int & unitID)
{
	const Unit & unit = getElement(unitID);
	Tile & tile = Map::instance->getTile(unit.i8_x, unit.i9_y);

	if (tile.i7_unitID == unitID)
		tile.i7_unitID = INVALID_ID;

	if (unit.i0_type < Unit::Wolf)
		Map::playerStatistics->unk3(unit.i3_player, unit.i0_type);

	removeSlot(unitID);
	unitID = INVALID_ID;
}

void UnitManager::unk4()
{
	Unit * unit = &getElement(0);
	
	for (int i = 0; i < i12 + 1; ++i, ++unit) {
		if (unit->i0_type != Unit::None) {
			if (unit->i0_type < Unit::Wolf) {
			
				if (unit->i19 != -1)
					unit->unk15();

			} else {
				if (unit->i24 == 0) {
				
				} else {
					unit->unk14();
				}
			}
		
		}
	}
}


bool UnitManager::isBattleUnitOf(const int unitID, const int playerID) const
{
	const Unit & unit = getElement(unitID);

	if (unit.i0_type == Unit::None || unit.i3_player != playerID)
		return false;

	return unit.i0_type >= Unit::Militia && unit.i0_type <= Unit::Ballista;
}

void UnitManager::unk14(const int houseID, const int p4, const int p8)
{
	House & house = Map::houseManager->getElement(houseID);

	if (house.i10.done.i33 == p4) {
		house.i10.done.i33 = p8;
		return;
	}

	short nextID = house.i10.done.i33;

	Unit * unit;

	while (unit = &getElement(nextID), unit->i34 != -1) {
		if (unit->i34 == p4) {
			unit->i34 = p8;
			break;
		}

		nextID = unit->i34;
	}
}
