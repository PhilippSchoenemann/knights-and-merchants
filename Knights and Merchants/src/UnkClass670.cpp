#include "UnkClass670.h"

#include "InGame.h"
#include "UnkGame111.h"
#include "graphics/Font.h"


UnkClass670::UnkClass670(const Rect & rect, const int p4)
	: UIElement { rect, 0, p4, -1 }
{
	reset();

	i21_flags |= 0x40;
    i25_keyboardKey = 0;
}

UnkClass670::~UnkClass670()
{
	reset();
}

void UnkClass670::vtable4_draw(DrawableSurface & p0)
{
	Rect rect { };
	calculateAbsolutePosition(rect);

	InGame::unkGame111_instance->vtable12(p0, rect);
	
	if (i32 != 0)
		unk1()->i0->drawString(p0, rect.left, rect.top, InGame::getTextLibString(i32).c_str());
}

void UnkClass670::reset()
{
	i32 = 0;
}

void UnkClass670::unknown1(short p0)
{
	if (i32 != p0) {
		i32 = p0;
		registerForDraw();
	}
}
