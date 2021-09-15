#ifndef KNIGHTS_AND_MERCHANTS_UNK_CLASS_2000_H
#define KNIGHTS_AND_MERCHANTS_UNK_CLASS_2000_H

#include "ui/controls/UIElement.h"

namespace knights_and_merchants::io
{
    class MouseHandler;
}

class UnkClass2000 : public knights_and_merchants::ui::controls::UIElement
{
public:

	UnkClass2000(int p0);
	~UnkClass2000();

	virtual void vtable4_draw(DrawableSurface & surface) override;

	void unk111(knights_and_merchants::io::MouseHandler * p0);

	bool unk2(POINT & point, int & p4, int & p8, int p12_playerID);

	bool unk3(const int p0_mouseX, const int p4_mouseY, int & p8_outX, int & p12_outY);

	short unk4(POINT & p0, int p4_playerID);

	Rect i32;
	int i48;
};

#endif