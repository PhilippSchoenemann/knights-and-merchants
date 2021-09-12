#ifndef KNIGHTS_AND_MERCHANTS_STORE_HOUSE_MANAGER_H
#define KNIGHTS_AND_MERCHANTS_STORE_HOUSE_MANAGER_H

#include "Array.h"
#include "StoreHouse.h"

class StoreHouseManager : public Array<StoreHouse>
{
public:
    StoreHouseManager(const int maxSlots);

    ~StoreHouseManager();
};

#endif