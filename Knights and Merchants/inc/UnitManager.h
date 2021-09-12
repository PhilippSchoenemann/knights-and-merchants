#ifndef KNIGHTS_AND_MERCHANTS_UNIT_MANAGER_H
#define KNIGHTS_AND_MERCHANTS_UNIT_MANAGER_H

#include "Array.h"
#include "Unit.h"

class UnitManager : public Array<Unit> {
public:
	UnitManager(const int maxSlots);

	int spawnUnit(Unit::Type type, int playerID, int x, int y);
	void killUnit(int & unitID);
	void unk4();

	bool isBattleUnitOf(const int unitID, const int playerID) const;

	void unk14(const int houseID, const int p4, const int p8);
};

#endif