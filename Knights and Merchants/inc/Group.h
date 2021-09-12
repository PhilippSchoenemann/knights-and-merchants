#ifndef KNIGHTS_AND_MERCHANTS_GROUP_H
#define KNIGHTS_AND_MERCHANTS_GROUP_H

class Group
{
public:

    static constexpr short MAX_UNIT_COUNT = 80;

    static bool isUsed(const Group & group);

    static void setUnused(Group & group);


    bool addUnit(const int unitID);

    bool removeUnit(const int unitID);

    void rotateLeft();

    void rotateRight();

    void giveOrderToMoveTo(const int x, const int y, const char direction);

    void giveOrderToAttack(const int x, const int y);

    void giveOrderToHalt();

    void giveOrderToRotateLeft();

    void giveOrderToRotateRight();

    void giveOrderToSeparate();

    void giveOrderToStormAttack();

    void giveOrderToEat();

    void giveOrder(const char p0, const int p4, const int p8, const int p12);

    void update();

    void unk11(const int groupID, const int unitID);

    void unk10();


    void unk21(const char direction, const int unitsPerRow);


    char i0_playerID;
    char i1_groupType;
    short i2_leaderUnitID;
    char i4_direction;
    char i5;
    short i6_unitsPerRow;
    short i8_unitCount;
    short i10_unitIDs[MAX_UNIT_COUNT];
    char i170;
    char i171_orderID;
    char i172_x;
    char i173_y;
    short i174;
    short i176;
    int i178_orderParam1;
    int i182_orderParam2;
    int i186_orderParam3;
    short i190_groupID;


private:
    void limitUnitsPerRow();

};

#endif