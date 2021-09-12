#include "StoreHouse.h"

bool StoreHouse::isUsed(const StoreHouse & storeHouse)
{
	return storeHouse.i0 != -1;;
}

void StoreHouse::setUnused(StoreHouse & storeHouse)
{
	storeHouse.i0 = -1;
}
