#include "ui/controls/Button.h"
#include "MasterClass.h"
#include "text/Lib.h"
#include "graphics/Font.h"
#include "graphics/Bitmap.h"
#include "ui/UnkClass203.h"
#include "engine/GraphicsHandler.h"
#include "graphics/DrawableSurface.h"

using knights_and_merchants::graphics::DrawableSurface;

extern MasterClass * instance_MasterClass;

namespace knights_and_merchants::ui::controls
{
Button::Button(const Rect & p0, short p4, const char * p8, char p12, int p16)
	: UIElement { p0, p4, p12, 0 }
{
	reset();
	i25 = p16;

	setText(p8);
}

Button::Button(const Rect & p0, short p4, int p8, char p12, int p16)
	: Button { p0, p4, instance_MasterClass->i948->getStringByIndex(p8).c_str(), p12, p16 }
{

}

Button::~Button()
{
	if (i32 != nullptr)
		free(i32);

	reset();
}

void Button::reset()
{
	i32 = nullptr;
	i36 = -1;
	i38 = -1;
}

void Button::setText(const char * p0)
{
	if (i32 != nullptr)
		free(i32);
	
	i32 = (char *) malloc(strlen(p0) + 1);
	if (i32 != nullptr)
		strcpy(i32, p0);
	
	registerForDraw();
}


void Button::vtable4(DrawableSurface & p0)
{
	Rect rectangle1 { };
	Rect rectangle2 { };

	bool var44 = false;

	UnkClass201 * var40 = UIElement::unk1();

	if (i36 == -1) {
		i36 = (long long) rand() % 30;
		i38 = (long long) rand() % 300;
	}

	auto textWidth = var40->i0->calculateTextWidth(i32, 0, 0);
	auto var4C = (textWidth < i5_position.getWidth()) ? (i5_position.getWidth() - textWidth) / 2 : 0;

	auto var48 = (i5_position.getHeight() - var40->i0->i2_height) / 2;

	DrawableSurface var3C;
	calculateSurface(var3C, p0);

	calculateAbsolutePosition(rectangle1);

	int esi = 0;
	int edi = 0;
	if ((i21_flags & 0x18) != 0) {
		var4C += 3;
		var48 += 3;
		esi = 3;
		edi = 3;
		var44 = true;
	}

	i28->vtable8(p0, i5_position);

	if (var44) {
		var3C.i0_width -= esi;
		var3C.i2_height -= esi;
		var3C.i6_surface += var3C.i4_pitch * edi + esi;

		var40->i24->draw(var3C, -i36, -i38);

		var3C.i0_width += esi;
		var3C.i2_height += esi;
		var3C.i6_surface -= var3C.i4_pitch * edi + esi;

		rectangle2.setBounds(rectangle1.left, rectangle1.top, rectangle1.getWidth(), rectangle1.getHeight());

		rectangle2.setSize(rectangle2.getWidth(), edi);

		p0.remapRectangle(rectangle2, instance_MasterClass->i1186[1]);

		rectangle2.setBounds(rectangle2.left, rectangle2.top + edi, esi, rectangle1.getHeight() - edi);

		p0.remapRectangle(rectangle2, instance_MasterClass->i1186[1]);
	} else {
		var40->i24->draw(var3C, -i36, -i38);
	}

	for (int i = 0; i < 3; ++i)
		p0.remapRow(i + rectangle1.left + esi, rectangle1.right - i, i + rectangle1.top + edi, instance_MasterClass->i1186[2]);
	
	for (int i = 0; i < 3; ++i)
		p0.remapColumn(i + rectangle1.top + edi, rectangle1.bottom, i + rectangle1.left + esi, instance_MasterClass->i1186[2]);

	if (!var44) {
		for (int i = 0; i < 3; ++i)
			p0.remapRow( i + rectangle1.left + esi, rectangle1.right - i, rectangle1.bottom - i - 1, instance_MasterClass->i1186[1]);

		for (int i = 0; i < 3; ++i)
			p0.remapColumn(i + rectangle1.top + edi, rectangle1.bottom, rectangle1.right - i - 1, instance_MasterClass->i1186[1]);
	}

	if ((~i21_flags & 4) == 4 && (i21_flags & 0x1A) != 0) {
		rectangle2.setBounds(esi + rectangle1.left + 3 , rectangle1.top + edi + 3, rectangle1.getWidth() - 6, rectangle1.getHeight() - 6);
		p0.remapRectangle(rectangle2, instance_MasterClass->i1186[3]);
	}

	if (var40->i4 == 0) {
		var40->i0->drawStringEx(var3C, var4C - 1, var48, i32, var40->i8, var40->i18, 0);
		var40->i0->drawStringEx(var3C, var4C, var48, i32, var40->i16, var40->i18, 0);
	} else {
		var40->i0->drawString(var3C, var4C, var48, i32);
	}

	if ((~i21_flags & 4) == 0)
		p0.remapRectangle(rectangle1, instance_MasterClass->i1186[1]);
}
}