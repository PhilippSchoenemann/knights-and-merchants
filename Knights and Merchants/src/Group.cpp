#include "Group.h"
#include "Map.h"
#include "UnitManager.h"


bool Group::isUsed(const Group & group)
{
	return group.i1_groupType != -1;
}

void Group::setUnused(Group & group)
{
	group.i1_groupType = -1;
}

void Group::giveOrderToMoveTo(const int x, const int y, const char direction)
{
	giveOrder(0, x, y, direction);
}

bool Group::addUnit(const int unitID)
{
	if (i8_unitCount >= MAX_UNIT_COUNT)
		return false;

	i8_unitCount++;

	for (int i = 0; i < MAX_UNIT_COUNT; ++i) {
		if (i10_unitIDs[i] == -1) {
			i10_unitIDs[i] = unitID;
			break;
		}
	}

	Unit & unit { Map::unitManager->getElement(unitID) };
	unit.i47_groupId = i190_groupID;

	return true;
}

void Group::rotateLeft()
{
	i4_direction = (i4_direction + 7) % 8;
}

void Group::rotateRight()
{
	i4_direction = (i4_direction + 1) % 8;
}

void Group::update()
{
	switch (i170) {
	case 8:
		break;
	case 10:
		break;
	default:
		break;
	}
}

void Group::unk11(const int groupID, const int unitID)
{
	Unit & unit { Map::unitManager->getElement(unitID) };

	i190_groupID = groupID;
	i0_playerID = unit.i3_player;

	i1_groupType = unit.getGroupType();
	i6_unitsPerRow = 1;
	i8_unitCount = 0;
	i4_direction = unit.i10_direction;

	std::fill_n(i10_unitIDs, MAX_UNIT_COUNT, -1); // TODO: check if int goes well with short

	addUnit(unitID);
	unk10();

	i174 = 0;

	i171_orderID = 13;
	i170 = 13;

	i5 = -1;
}

void Group::unk10()
{
	for (int i = 0; i < MAX_UNIT_COUNT; ++i) {
		if (i10_unitIDs[i] == UnitManager::INVALID_ID)
			break;

		Map::unitManager->getElement(i10_unitIDs[i]).i49_isGroupLeader = false;
	}

	for (int i = 0; i < i8_unitCount; ++i) {
		if (i10_unitIDs[i] == UnitManager::INVALID_ID)
			break;

		if (i == i6_unitsPerRow / 2) {
			i2_leaderUnitID = i10_unitIDs[i];

			Unit & leader = Map::unitManager->getElement(i10_unitIDs[i]);
			leader.i49_isGroupLeader = true;

			i172_x = leader.i8_x;
			i173_y = leader.i9_y;

			if (i171_orderID == 13 && i170 == 13)
				giveOrderToHalt();

			break;
		}
	}
}

void Group::giveOrderToAttack(const int x, const int y)
{
	giveOrder(1, x, y, 0);
}

void Group::giveOrderToHalt()
{
	giveOrder(4, 0, 0, 0);
}

void Group::giveOrderToRotateLeft()
{
	giveOrder(6, 0, 0, 0);
}

void Group::giveOrderToRotateRight()
{
	giveOrder(5, 0, 0, 0);
}

void Group::giveOrderToSeparate()
{
	giveOrder(9, 0, 0, 0);
}

void Group::giveOrderToStormAttack()
{
	giveOrder(10, 0, 0, 0);
}

void Group::giveOrderToEat()
{
	giveOrder(12, 0, 0, 0);
}

void Group::giveOrder(const char p0, const int p4, const int p8, const int p12)
{
	i171_orderID = p0;
	i178_orderParam1 = p4;
	i182_orderParam2 = p8;
	i186_orderParam3 = p12;
}

void Group::unk21(const char direction, const int unitsPerRow)
{
	i6_unitsPerRow = unitsPerRow;
	i4_direction = direction;

	limitUnitsPerRow();
	unk10();
}

bool Group::removeUnit(const int unitID)
{
	for (int i = 0; i < MAX_UNIT_COUNT; ++i) {
		if (i10_unitIDs[i] == unitID) {
			i8_unitCount--;

			while (i < MAX_UNIT_COUNT - 1) {
				i10_unitIDs[i] = i10_unitIDs[i + 1];

				if (i10_unitIDs[i + 1] == UnitManager::INVALID_ID)
					break;

				i++;
			}

			return true;
		}
	}

	return false;
}

void Group::limitUnitsPerRow()
{
	if (i6_unitsPerRow > i8_unitCount)
		i6_unitsPerRow = i8_unitCount;

	if (i6_unitsPerRow == 0)
		i6_unitsPerRow = 1;
}
