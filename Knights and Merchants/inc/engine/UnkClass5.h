//
// Created by schoe on 06.10.2020.
//

#ifndef KNIGHTS_AND_MERCHANTS_UNKCLASS5_H
#define KNIGHTS_AND_MERCHANTS_UNKCLASS5_H

#include <cstdint>

struct Color {
	uint8_t r;
	uint8_t g;
	uint8_t b;
};

struct Unk {
	int16_t i0;
	int16_t i2;
	int16_t i4;
	int16_t i6;

};

class UnkClass5 {
public:
	UnkClass5();
	~UnkClass5();

	void setColorAt(unsigned char i, uint8_t r, uint8_t g, uint8_t b);

	const Color * getColorPtr(unsigned char i) const;

	void reset();
	int unk1(unsigned char p0, int p4, int p8);
	void unk4(unsigned char p0, const Color * p4);

	short unk3(short p0, short p4, short p8);

	bool unk12();
	void unk15(short p0);

	int16_t i832;
private:
	int unk2(int i);

	Color colors[256];
	Unk i768[8];
	

};


#endif //KNIGHTS_AND_MERCHANTS_UNKCLASS5_H
