#ifndef KNIGHTS_AND_MERCHANTS_UNK_CLASS_671_H
#define KNIGHTS_AND_MERCHANTS_UNK_CLASS_671_H

#include "ui/controls/UIElement.h"

class UnkClass671 : public knights_and_merchants::ui::controls::UIElement
{
public:
	UnkClass671(const Rect & rect, int p4, int p8);
	virtual ~UnkClass671();

	virtual void vtable4_draw(DrawableSurface & p0) override;

	void reset();
	void setBriefingID(short id);

	short i32;
};

#endif