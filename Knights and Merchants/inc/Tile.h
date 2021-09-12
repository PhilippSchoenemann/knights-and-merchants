#ifndef KNIGHTS_AND_MERCHANTS_TILE_H
#define KNIGHTS_AND_MERCHANTS_TILE_H

namespace knights_and_merchants::io
{
    class FileIo;
}

class Tile
{
public:
    Tile() = default;

    ~Tile() = default;

    bool isCleared(const int playerID) const
    {
        return i13_clearedFlags & (1 << playerID);
    }

    void clearUp(const int playerID)
    {
        i13_clearedFlags |= 1 << playerID;
    }

    bool isI17(const int playerID) const
    {
        return i17 & (0xF << (4 * playerID));
    }

    int unk9(const int playerID) const
    {
        const int bits = 4 * playerID;
        return (i17 & (0xF << bits)) >> bits;
    }

    int getObjectAnimationDelta();

    int getTextureSet();

    int getTexture();


    void setTextureSet(const int textureSet);

    void setTexture(const int textureID);

    void setDirection(const int direction);

    void read(knights_and_merchants::io::FileIo & fileIO);

    void unk2(const bool p0);

    void unk11(const char p0);

    void unk8(const char p0, const char p4);

    unsigned char i0;
    char i1;
    unsigned char i2_height;
    unsigned char i3;
    char i4;
    unsigned char i5_objectID;
    char i6;
    short i7_unitID;
    short i9_houseID;
    short i11;
    char i13_clearedFlags;
    char i14;
    char i15;
    char i16;
    unsigned int i17;
    char i21;
    unsigned char i22;

};

#endif