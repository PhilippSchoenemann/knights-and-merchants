#ifndef KNIGHTS_AND_MERCHANTS_STORE_HOUSE_H
#define KNIGHTS_AND_MERCHANTS_STORE_HOUSE_H

class StoreHouse
{
public:

    static bool isUsed(const StoreHouse & storeHouse);

    static void setUnused(StoreHouse & storeHouse);


    short i0;
};

#endif