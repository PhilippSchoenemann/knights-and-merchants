#ifndef KNIGHTS_AND_MERCHANTS_PLAYER_STATISTIC_H
#define KNIGHTS_AND_MERCHANTS_PLAYER_STATISTIC_H

class PlayerStatistic
{
public:
    PlayerStatistic();

    ~PlayerStatistic();

    short i0[29]; // current built Houses
    short i58[29];
    short i116; // houses Lost
    short i118;
    short i120[41]; // current alive Units
    short i202;
    char i204_housesUnlocked[29];
    char i233[41]; // units Unlocked (at least in statistics)
    char i274[29];
};

#endif