#include "GroupManager.h"
#include "RandomGenerator.h"
#include "Tile.h"
#include "UnitManager.h"
#include "ClassyTwo.h"
#include "InGame.h"

GroupManager::Hola GroupManager::unkTable[8] {
	{ 1, 0, 0, 1 },
	{ 1, 1, -1, 1 },
	{ 0, 1, -1, 0 },
	{ -1, 1, -1, -1 },
	{ -1, 0, 0, -1 },
	{ -1, -1, 1, -1 },
	{ 0, -1, 1, 0 },
	{ 1, -1, 1, 1 }
};

GroupManager::GroupManager(const int maxSlots)
	: Array<Group> { maxSlots }
{
	reset();
}

GroupManager::~GroupManager()
{
	reset();
}

int GroupManager::createGroupFromUnit(const int unitID)
{
	const int groupID { addSlot() };

	if (groupID != INVALID_ID) {
		Group & group = getElement(groupID);
		group.unk11(groupID, unitID);

		i32_groupCounts[group.i0_playerID]++;
	}

	return groupID;
}

int GroupManager::spawnGroup(Unit::Type unitType, int playerID, int x, int y, char direction, int unitsPerRow, int unitCount)
{
	if (direction >= 8)
		direction = 0;

	auto & edi = unkTable[direction];
	auto varC = unitsPerRow;
	auto var11 = Map::class666_instance->next(150) + 104;

	auto ebx = x - (unitsPerRow / 2) * edi.i0;
	auto esi = y - (unitsPerRow / 2) * edi.i4;

	auto var8 = esi;

	if (unitType < Unit::Militia || unitType > Unit::Ballista)
		return INVALID_ID;

	const Tile & t = Map::instance->getTile(ebx, esi);

	if ((t.i6 & 1) == 0 || t.i7_unitID != UnitManager::INVALID_ID)
		return INVALID_ID;

	int unitID = Map::unitManager->spawnUnit(unitType, playerID, ebx, esi);
	if (unitID == UnitManager::INVALID_ID)
		return INVALID_ID;

	Unit & unit = Map::unitManager->getElement(unitID);
	unit.i16_hunger = var11;
	unit.i10_direction = direction;
	Group & group = unit.getGroup();
	auto var4 = unit.i47_groupId;
	auto unk = 1;

	int var10;
	for (int unk = 1; unk < unitCount; ++unk) {
		auto esi = (unk / varC) * edi.i8 + (ebx + (edi.i0 * (unk % varC)));
		auto ebp = (unk % varC) * edi.i4 + (var8 + edi.i12 * (unk / varC));

		if (Map::instance->areCoordinatesValid(esi, ebp)) {
			Map::classyTwo_instance->setPosition(esi, ebp);

			Tile & t = Map::instance->getTile(Map::classyTwo_instance->i0_x, Map::classyTwo_instance->i1_y);
			if ((t.i6 & 1) == 1) {
				if (t.i7_unitID == UnitManager::INVALID_ID) {
					int unitID = Map::unitManager->spawnUnit(unitType, playerID, Map::classyTwo_instance->i0_x, Map::classyTwo_instance->i1_y);
					if (unitID != UnitManager::INVALID_ID) {
						Unit & unit = Map::unitManager->getElement(unitID);
						unit.i16_hunger = var11;
						unit.i10_direction = direction;
						var10 = unit.i47_groupId;

						if (group.addUnit(unitID)) {
							Map::groupManager->removeGroup(var10);
						}

						continue;
					}
				}
			}
		} 

		ebp = -1;

		while (true) {
			for (int esi = 0; esi < 8; ++esi) {
				if (Map::classyTwo_instance->move(esi)) {
					Tile & t = Map::instance->getTile(Map::classyTwo_instance->i0_x, Map::classyTwo_instance->i1_y);

					if ((t.i6 & 1) == 1 && t.i7_unitID == UnitManager::INVALID_ID) {
						int unitID = Map::unitManager->spawnUnit(unitType, playerID, Map::classyTwo_instance->i0_x, Map::classyTwo_instance->i1_y);

						if (unitID != UnitManager::INVALID_ID) {
							Unit & unit = Map::unitManager->getElement(unitID);

							unit.i16_hunger = var11;
							unit.i10_direction = direction;
							var10 = unit.i47_groupId;

							if (group.addUnit(unitID)) {
								Map::groupManager->removeGroup(var10);
							}

							goto outerEnd;
						} else {
							break; // I think so at least
						}

					} else {
						Map::classyTwo_instance->moveOpposite(esi);
					}
				}

			}

			for (int esi = 0; esi < 8; ++esi)
				if (Map::classyTwo_instance->move(esi))
					break;;
			
		}

	outerEnd:;
	}

	group.unk21(direction, unitsPerRow);
	group.giveOrderToHalt();
	return var4;
}

void GroupManager::removeGroup(int & groupID)
{
	Group & group = getElement(groupID);
	i32_groupCounts[group.i0_playerID]--;
	removeSlot(groupID);
	groupID = INVALID_ID;
}

void GroupManager::update()
{
	for (int i = 0; i < 8; ++i) {
		if (InGame::instance.i865[i].i0 != 0 && i32_groupCounts[i] != 0) {
			Group * group; 
			do {
				i48[i]++;

				if (i48[i] > i12)
					i48[i] = 0;

				group = &getElement(i48[i]);
			} while (group->i0_playerID != i || group->i1_groupType == -1);

			if (group->i2_leaderUnitID != UnitManager::INVALID_ID) {
				const Unit & leader = Map::unitManager->getElement(group->i2_leaderUnitID);

				if (leader.i0_type != Unit::None && leader.i3_player == i && leader.i0_type >= Unit::Militia && leader.i0_type <= Unit::Ballista)
					group->update();
				else
					removeGroup(i48[i]);
			} else {
				removeGroup(i48[i]);
			}
		}
	}
}

void GroupManager::reset() {
	for (int i = 0; i < 8; ++i) {
		i32_groupCounts[i] = 0;
		i48[i] = 0;
	}
}
