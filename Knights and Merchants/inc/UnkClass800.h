#ifndef KNIGHTS_AND_MERCHANTS_UNK_CLASS_800_H
#define KNIGHTS_AND_MERCHANTS_UNK_CLASS_800_H

#include "ui/controls/UIElement.h"

class UnkClass800 : public knights_and_merchants::ui::controls::UIElement
{
public:
	UnkClass800(const knights_and_merchants::utilities::Rect & p0, const char * p4, const char p8, const char p12);
	virtual ~UnkClass800();

	virtual void vtable4_draw(DrawableSurface & p0) override;

	void reset();
	void setText(const char * p0);
	 char * i32;
	 char i36;
};

#endif