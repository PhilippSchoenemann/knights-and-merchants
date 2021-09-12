#include "UnkClass700.h"
#include "ui/UnkClass201.h"
#include "graphics/Bitmap.h"
#include "ui/UnkClass203.h"
#include "UnkGame1.h"
#include "engine/GraphicsHandler.h"
#include "graphics/DrawableSurface.h"

UnkClass700::UnkClass700(const Rect & p0, int p4, const Bitmap * p8, int p12, int p16, char p20)
	: UIElement { p0, p4, p12, p16 }
{
	reset();

	i25 = p20;
	i32 = p8;
}

UnkClass700::~UnkClass700()
{
}

void UnkClass700::vtable4(DrawableSurface & p0)
{
	Rect rect1 { };
	Rect rect2 { };

	auto var4C = unk1();

	calculateAbsolutePosition(rect1);

	if (i36 == -1) {
		i36 = i5_position.left % (var4C->i24->i0_width - i5_position.getWidth() - 1);
		i38 = i5_position.top % (var4C->i24->i2_height - i5_position.getHeight() - 1);
	}

	if (i32 == nullptr)
		return;

	DrawableSurface var3C { };
	calculateSurface(var3C, p0);

	auto var99 = 0;

	auto var40 = i5_position.getWidth() / 2;
	auto var44 = i5_position.getHeight() / 2;
	auto var48 = i21_flags & 0x18;

	if (var48 != 0) {
		var40 += 2;
		var44 += 2;
		var99 = 3;
	}

	i28->vtable8(p0, i5_position);

	if (var48 == 0) {
		var4C->i24->drawRemapped(var3C, -i36, -i38, i40);
	} else {

		var3C.i0_width -= var99;
		var3C.i2_height -= var99;
		var3C.i6_surface += var3C.i4_pitch * var99 + var99;
		var4C->i24->drawRemapped(var3C, -i36, -i38, i40);

		var3C.i6_surface = var3C.i6_surface - (var3C.i4_pitch * var99 + var99);

		var3C.i0_width += var99;
		var3C.i2_height += var99;
		rect2.setBounds(rect1.left, rect1.top, rect1.getWidth(), rect1.getHeight());
		rect2.setSize(rect2.getWidth(), var99);
		p0.remapRectangle(rect2, UnkGame1::getRemap(0));

		rect2.setBounds(rect2.left, var99 + rect2.top, var99, rect1.getHeight() - var99);
		p0.remapRectangle(rect2, UnkGame1::getRemap(0));
	}

	for (int i = 0; i < 3; ++i) {
		p0.remapRow(rect1.left + i + var99, rect1.right - i, rect1.top + i + var99, UnkGame1::getRemap(1) - 256 * i);
	}

	for (int i = 0; i < 3; ++i) {
		p0.remapColumn(rect1.top + i + var99, rect1.bottom, rect1.left + i + var99, UnkGame1::getRemap(1) - 256 * i);
	}

	if (var48 == 0) {
		for (int i = 0, var50 = 0; i < 3; ++i, var50 += 0x100) {
			p0.remapRow(rect1.left + i + var99, rect1.right - i, rect1.bottom - i - 1, UnkGame1::getRemap(0) + var50);
		}

		for (int i = 0, var50 = 0; i < 3; ++i, var50 += 0x100) {
			p0.remapColumn(rect1.top + i + var99, rect1.bottom, rect1.right - i - 1, UnkGame1::getRemap(0) + var50);
		}
	}

	i32->draw(var3C, var40, var44);

	if ((~i21_flags & 4) == 0) {
		p0.remapRectangle(rect1, UnkGame1::getRemap(0));
	} else if ((i21_flags & 0x1A) != 0) {
		rect2.setBounds(var99 + rect1.left + 3, var99 + rect1.top + 3, rect1.getWidth() - 6, rect1.getHeight() - 6);
		p0.remapRectangle(rect2, UnkGame1::getRemap(3));
	}

}

void UnkClass700::reset()
{
	i32 = nullptr;
	i36 = -1;
	i38 = -1;
	i40 = nullptr;
}
