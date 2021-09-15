#ifndef KNIGHTS_AND_MERCHANTS_UNK_GAME_111_H
#define KNIGHTS_AND_MERCHANTS_UNK_GAME_111_H

#include "ui/UnkClass200.h"

class UnkClass670;
class UnkClass671;

class UnkGame111 : public UnkClass200 {
public:
	UnkGame111(const knights_and_merchants::utilities::Rect & rect);
	virtual ~UnkGame111();

	virtual void vtable0(knights_and_merchants::graphics::DrawableSurface & surface) override;
	virtual bool vtable4(unsigned short p0, int p4, int p8) override;
	virtual void vtable8() override;
	virtual void vtable12(knights_and_merchants::graphics::DrawableSurface & p0, knights_and_merchants::utilities::Rect & p4) override;

	bool handleInput();

	void unk09();

	void reset();

	void drawMenu(knights_and_merchants::graphics::DrawableSurface & p0);
	void drawWhat(knights_and_merchants::graphics::DrawableSurface & p0);

private:
	static UnkClass201 uc201[8];
	static UnkClass202 uc202[6];


	int i882;
	int i886;
	int i890;

	UnkClass670 * i898;
	short i902;
	int i904;
	int i908;
	UnkClass671 * i912[12];
	int i960;

};

#endif