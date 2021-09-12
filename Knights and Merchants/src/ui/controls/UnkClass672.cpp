#include "ui/controls/UnkClass672.h"
#include "ui/UnkClass203.h"
#include "ui/UnkClass201.h"
#include "graphics/Font.h"
#include "engine/GraphicsHandler.h"
#include "graphics/DrawableSurface.h"
#include "ui/UnkClass200.h"

using knights_and_merchants::graphics::DrawableSurface;

namespace knights_and_merchants::ui::controls
{
UnkClass672::UnkClass672(const Rect & p0, int p4,  char * p8)
	: UIElement(p0, 0, 0, 0xffff)
{
	reset();

	i21_flags |= 0x40;
	i32 = p8;
	i36 = p8;
	i40 = GetTickCount();
	i44 = 1;
}

UnkClass672::~UnkClass672()
{
}

void UnkClass672::vtable4(DrawableSurface & p0)
{
	Rect rect { };

	int ebx = 0;
	auto var34 = UIElement::unk1();
	calculateAbsolutePosition(rect);

	i28->getBase()->vtable12(p0, rect);

	DrawableSurface var2C;
	calculateSurface(var2C, p0);

	auto var30 = var34->i0->unk1();

	auto eax = abs(rect.bottom - rect.top);
	auto edi = eax - i44;
	auto esi = i36;

	if (edi < eax) {
		do {
			char * ptr = esi;

			if (*esi != '|')
				while (*esi != '\0' && *(++esi) != '|');
			
			if (*ptr != '\0' && *ptr != '|' && edi > -20) {
				char temp = *esi;
				*esi = '\0';
				var34->i0->drawString(var2C, (abs(rect.right - rect.left) - var34->i0->calculateTextWidth(ptr, 0, 0)) / 2, edi, ptr);
				*esi = temp;
				ebx = 1;
			}

		} while (*esi != '\0' && (esi++, edi += var30, edi < abs(rect.bottom - rect.top)));
	}
	
	if (ebx == 0)
		i40 = -1;
	

	i44++;
}

void UnkClass672::reset()
{
	i32 = nullptr;
	i36 = nullptr;
	i40 = 0;
	i44 = 0;
}

bool UnkClass672::updateScroll()
{
	if (i40 == -1)
		return false;

	auto tickCount = GetTickCount();
	if (tickCount > i40) {
		i40 = tickCount + 30;
		registerForDraw();
	}

	return true;
}
}