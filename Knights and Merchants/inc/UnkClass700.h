#ifndef KNIGHTS_AND_MERCHANTS_UNK_CLASS_700_H
#define KNIGHTS_AND_MERCHANTS_UNK_CLASS_700_H

#include "ui/controls/UIElement.h"

namespace knights_and_merchants::graphics
{
    class Bitmap;
}

class UnkClass700 : public knights_and_merchants::ui::controls::UIElement
{
public:
	UnkClass700(const Rect & p0, int p4, const knights_and_merchants::graphics::Bitmap * p8, int p12, int p16, char p20);
	virtual ~UnkClass700();

	virtual void vtable4_draw(DrawableSurface & p0) override;


	void reset();

	const knights_and_merchants::graphics::Bitmap * i32;
	short i36;
	short i38;
	unsigned char * i40;
};

#endif