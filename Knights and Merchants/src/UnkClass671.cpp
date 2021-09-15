#include "UnkClass671.h"


UnkClass671::UnkClass671(const Rect & rect, int p4, int p8)
	: UIElement { rect, p4, p8, -1 }
{
	reset();
    i25_keyboardKey = 0;
	setEnabled(false);
}

UnkClass671::~UnkClass671()
{
	reset();
}

void UnkClass671::vtable4_draw(DrawableSurface & p0)
{
	Rect rect { };

	//throw 0; // reverse
}

void UnkClass671::reset()
{
	i32 = -1;
}

void UnkClass671::setBriefingID(short id)
{
	if (i32 != id)
	{
		i32 = id;
		registerForDraw();
	}

	setEnabled(i32 != -1);
}
