#ifndef KNIGHTS_AND_MERCHANTS_GROUP_MANAGER_H
#define KNIGHTS_AND_MERCHANTS_GROUP_MANAGER_H

#include "Unit.h"
#include "Array.h"
#include "Group.h"

class GroupManager : public Array<Group>
{
public:

    struct Hola
    {
        int i0;
        int i4;
        int i8;
        int i12;
    } static unkTable[8];

    GroupManager(const int maxSlots);

    ~GroupManager();

    int createGroupFromUnit(const int unitID);

    int spawnGroup(Unit::Type unitType, int playerID, int x, int y, char direction, int unitsPerRow, int unitCount);

    void removeGroup(int & groupID);

    void update();

    void reset();

    short i32_groupCounts[8];
    int i48[8];
};

#endif