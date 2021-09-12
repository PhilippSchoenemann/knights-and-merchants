#ifndef KNIGHTS_AND_MERCHANTS_CLASSY_THREE_H
#define KNIGHTS_AND_MERCHANTS_CLASSY_THREE_H

class Unit;

class ClassyThree
{
public:

    static char unk493F2C[4][3];

    void clearUpUnit(const Unit & p0) const;

    void clearUpHouse(const int houseID, const int playerID) const;

    void clearUpCircle(const int p0, const int p4, const short p8, const int p12) const;

    void setStreet(const int x, const int y, const int playerID) const;

    void setField(const int playerID, const int p4, const int x, const int y) const;

    void unk15(const int x, const int y, const int playerID) const;

    void unk14(const int p0, const int x, const int y) const;
};

#endif