#ifndef KNIGHTS_AND_MERCHANTS_UNK_GAME_2_H
#define KNIGHTS_AND_MERCHANTS_UNK_GAME_2_H

class UnkGame2 {
public:
	static UnkGame2 instance;

	UnkGame2();
	~UnkGame2();

	void reset();

	char i0;
	char i1;
	int i2;
};

#endif