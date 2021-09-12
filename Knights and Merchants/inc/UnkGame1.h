#ifndef KNIGHTS_AND_MERCHANTS_UNK_GAME_1_H
#define KNIGHTS_AND_MERCHANTS_UNK_GAME_1_H

namespace knights_and_merchants::graphics
{
    class Palette;
}

class UnkGame1
{
public:
	// TODO: initialize the static variables with correct values!
	static UnkGame1 * instance;

	static int unk_498720[2];

	static unsigned char * getRemap(char i);

	UnkGame1(int p0);
	~UnkGame1();

	void reset();
	void loadPalette(int p0);

	void unkFunc1();

	void readTextDats();
	void readGourad();

	void unkMapColor();

	unsigned char * i0 ;
	unsigned char * i4[4];
	unsigned char * i20 ;
	unsigned char * i24 ;
	unsigned char * i28[8];
	unsigned char * i60[8][2];

	unsigned char * i124[5];


	knights_and_merchants::graphics::Palette * i144 ;
	short i148 ;
};

#endif