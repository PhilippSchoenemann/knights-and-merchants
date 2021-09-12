#include "House.h"
#include "Map.h"
#include "StoreHouseManager.h"

bool House::isUsed(const House & house)
{
	return house.i0_type != Type::None;
}

void House::setUnused(House & house)
{
	house.i0_type = Type::None;
}


StoreHouse & House::getStoreHouse()
{
	return Map::arrayStoreHouses_instance->getElement(i41_storeHouseID);
}

void House::unk31()
{
	switch (i0_type) {
	case 2: case 10: case 19: case 20: case 23:
		break;
	case 21:
		break;
	case 17:
		break;
	case 27:
		break;
	case 12:
		break;
	case 16:
		break;
	case 13:
		break;
	case 11:
		break;
	case 6: case 8: case 9: case 14: case 28:
		break;
	}

}

void House::unk32(char p0)
{
	i7 = p0;

	if (i7 > 1) {
	
		for (int i = 0; i < 4; ++i) {
			i10.done.i10[i] = 0;
			i10.done.i14[i] = 0;
		}

		for (int i = 0; i < 4; ++i) {
			i10.done.i18[i] = 0;
			i10.done.i22[i] = 0;
		}

		i10.done.i31 = 0;
		i10.done.i29 = 0;
		i10.done.i33 = -1;
		i10.done.i35_unitID = -1;
		i10.done.i40 = 0;

		if (i7 != 2) {
			i10.done.i37_isOccupied = 1;
			i10.done.i38 = 1;
			i10.done.i39 = 0;
		} else {
			i10.done.i37_isOccupied = 0;
			i10.done.i38 = 1;
			i10.done.i39 = 0;
		}
	}

}
