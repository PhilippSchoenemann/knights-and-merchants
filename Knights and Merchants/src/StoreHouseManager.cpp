#include "StoreHouseManager.h"



StoreHouseManager::StoreHouseManager(const int maxSlots)
	: Array<StoreHouse> { maxSlots }
{
}

StoreHouseManager::~StoreHouseManager()
{
}
