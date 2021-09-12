#include "Unit.h"
#include "Map.h"
#include "UnitDat.h"
#include "GroupManager.h"

bool Unit::isUsed(const Unit & unit)
{
	return unit.i0_type != Unit::None;
}

void Unit::setUnused(Unit & unit)
{
	unit.i0_type = Unit::None;
}

Unit::Unit()
{
}


Unit::~Unit()
{
}

void Unit::unk3()
{
	switch (i54) {
	case 0:
		i34 = 0;
		i35 = 0;
		break;
	case 1:
		i36 = -1;
		i34 = 0;
		i35 = 0;
		i38 = 0;
		break;
	case 10:
		i34 = -1;
		i35 = -1;
		i36 = -1;
		break;
	case 11:
		i38 = 0;
		i39 = 0;
		i34 = -1;
		i35 = -1;
		i36 = -1;
		break;
	}
}

void Unit::unk7(char p0)
{
	i54 = p0;
}

void Unit::unk8(char p0)
{
	i55 = p0;
}

void Unit::unk9()
{
	i1 = Map::unitDat_instance->i15680[(int) i0_type].i0;
}

void Unit::unk4()
{
	if (i0_type == Unit::Serf) {
		
	}
}

void Unit::unk14()
{
	i24 = (i22 <= i24) ? i24 - i22 : 0;
	i14++;
}

void Unit::unk15()
{
	if (i17 <= 0)
		i19 = -1;
	else
		i17--;
}

char Unit::getGroupType()
{
	switch (i0_type) {
	case Militia:
	case AxeFighter:
	case SwordFighter:
	case Barbarian:
	case Warrior:
		return 0;
	case Bowman:
	case Crossbowman:
	case Rogue:
	case Catapult:
	case Ballista:
		return 2;
	case LanceCarrier:
	case Pikeman:
	case Rebel:
		return 1;
	case Scout:
	case Knight:
	case Vagabond:
		return 3;
	}

	return -1;
}

Group & Unit::getGroup() { return Map::groupManager->getElement(i47_groupId); };
