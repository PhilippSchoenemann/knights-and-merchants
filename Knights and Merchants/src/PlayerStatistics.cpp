#include "PlayerStatistics.h"
#include "PlayerStatistic.h"

using std::make_unique;

PlayerStatistics::PlayerStatistics(const int count)
	: i0 { count }, i1 { make_unique<PlayerStatistic[]>(count) }
{
	initialize();
}

PlayerStatistics::~PlayerStatistics()
{
	reset();
}

void PlayerStatistics::reset()
{
	i0 = 0;
	i1.reset();
}

void PlayerStatistics::initialize()
{
	if (i1) {
		for (int i = 0; i < i0; ++i) {
			i1[i].i116 = 0;
			i1[i].i118 = 0;
			i1[i].i202 = 0;

			for (int j = 0; j < 29; ++j) {
				i1[i].i0[j] = 0;
				i1[i].i204_housesUnlocked[j] = 0;
				i1[i].i274[j] = 0;
			}

			for (int j = 0; j < 41; ++j) {
				i1[i].i120[j] = 0;
				i1[i].i233[j] = 0;
			}
		}
	}
}


void PlayerStatistics::unk6(const int playerID, const House::Type houseType)
{
	i1[playerID].i0[houseType]--;
	i1[playerID].i116--;
}

void PlayerStatistics::increaseHouseStat(const int playerID, const House::Type houseType)
{
	i1[playerID].i118++;
	i1[playerID].i58[houseType]++;
}

void PlayerStatistics::decreaseHouseStat(const int playerID, const House::Type houseType)
{
	i1[playerID].i118--;
	i1[playerID].i58[houseType]--;
}

void PlayerStatistics::unk4(const int playerID, const Unit::Type unitType)
{
	i1[playerID].i120[unitType]++;
	i1[playerID].i202++;
}

void PlayerStatistics::unk3(const int playerID, const Unit::Type unitType)
{
	i1[playerID].i120[unitType]--;
	i1[playerID].i202--;
}

void PlayerStatistics::releaseAllHouses(const int playerID)
{
	for (int i = 0; i < 29; ++i)
		i1[playerID].i204_housesUnlocked[i] = 1;

	for (int i = 0; i < 41; ++i)
		i1[playerID].i233[i] = 1; // Unlock all units too?
}

