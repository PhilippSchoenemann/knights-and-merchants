#ifndef KNIGHTS_AND_MERCHANTS_UNK_GAME_20_H
#define KNIGHTS_AND_MERCHANTS_UNK_GAME_20_H

namespace knights_and_merchants::graphics
{
    class Bitmap;
}

class UnkGame20
{
public:
	static UnkGame20 * instance;

	UnkGame20();
	~UnkGame20();
	
	bool unk6(const bool p0_isLeftButtonDown, const bool p4_isRightButtonDown, const bool p8_isMiddleButtonDown);
	void unk7();
	void unk8();
	void unk9();

	void unk3();
	void unk4();
	void unk5(const knights_and_merchants::graphics::Bitmap * p0);
	char i0;
	int i2_wasLeftButtonDown;
	int i6_wasRightButtonDown;
	int i10_wasMiddleButtonDown;
	int i14;
	int i18;
    const knights_and_merchants::graphics::Bitmap * i22_currentCursor;

	short i28_unitID;

	int i43;
	int i39;
};

#endif