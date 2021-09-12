#ifndef KNIGHTS_AND_MERCHANTS_HOUSE_MANAGER_H
#define KNIGHTS_AND_MERCHANTS_HOUSE_MANAGER_H

#include "Array.h"
#include "House.h"

class HouseManager : public Array<House> {
public:
	HouseManager(const int maxSlots);
	~HouseManager();

	int addSlot(int p0, int p4, House::Type p8, int p12);
	bool isHouseOwnedBy(short houseID, char playerID);



	int spawnHouse(int p0, int p4, House::Type p8, int p12);

};

#endif