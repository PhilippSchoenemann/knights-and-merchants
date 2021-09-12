#ifndef KNIGHTS_AND_MERCHANTS_PLAYER_STATISTICS_H
#define KNIGHTS_AND_MERCHANTS_PLAYER_STATISTICS_H

#include <memory>
#include "Unit.h"
#include "House.h"

using std::unique_ptr;

class PlayerStatistic;

class PlayerStatistics {
public:
	PlayerStatistics(const int playerCount);
	~PlayerStatistics();

	void unk6(const int playerID, const House::Type houseType);
	void increaseHouseStat(const int playerID, const House::Type houseType);
	void decreaseHouseStat(const int playerID, const House::Type houseType);

	void unk4(const int playerID, const Unit::Type unitType);
	void unk3(const int playerID, const Unit::Type unitType);

	void releaseAllHouses(const int playerID);
private:
	void reset();
	void initialize();

	int i0;
	unique_ptr<PlayerStatistic[]> i1;
};

#endif