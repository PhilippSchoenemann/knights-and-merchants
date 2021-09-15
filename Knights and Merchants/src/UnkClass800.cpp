#include "UnkClass800.h"
#include "ui/UnkClass203.h"
#include "ui/UnkClass201.h"
#include "graphics/Font.h"
#include <cmath>

UnkClass800::UnkClass800(const Rect & p0, const char * p4, const char p8, const char p12)
	: UIElement { p0, 0, p8, -1 }
{
	reset();

	i21_flags |= 0x40;
	setText(p4);
	i36 = p12;
}

UnkClass800::~UnkClass800()
{
	if (i32 != nullptr)
		free(i32);

	reset();
}

void UnkClass800::vtable4(DrawableSurface & p0)
{
	Rect rect { };

	auto var50 = i4;
	auto var70 = i28_container;

	var70->vtable8(p0, i5_position);

	if (i32 == nullptr)
		return;

	calculateAbsolutePosition(rect);
	auto var2C = unk1();

	if (var2C == nullptr)
		return;

	auto varC = var2C->i8;
	auto var3C = var2C->i10;
	auto var10 = var2C->i12;
	auto var30 = var2C->i16;

	auto var34 = var2C->i0->calculateTextWidth(i32, 0, 0);
	auto var74 = i36;

	int var4;
	int var8;
	int t;

	switch (var74) {
	case 0:
		var8 = rect.left;

		t = rect.bottom - rect.top - var2C->i0->i2_height;
		if (t < 0)
			t++;

		var4 = rect.top + (int) std::floor((float) t / 2);
		break;
	case 1:
		var8 = rect.left;
		var4 = rect.top + 1;
		break;
	default:
		if (var34 < rect.getWidth()) {
			auto t = rect.right - rect.left - var34;
			if (t < 0)
				t++;

			var8 = rect.left + (int) std::floor((float) t / 2);
		} else {
			var8 = rect.left;
		}

		t = rect.bottom - rect.top - var2C->i0->i2_height;
		if (t < 0)
			t++;

		var4 = rect.top + (int)std::floor((float)t / 2);
	}

	if ((i21_flags & 4) == 4) {
		varC = var2C->i10;
		var3C = var2C->i12;
		var10 = var2C->i14;
	}

	auto var14 = i32;

	do {
		auto var38 = var2C->i0->unk2(rect.getWidth(), var14);
		if (var38 == -1) {
			if (var2C->i4 == 0) {
				var2C->i0->drawStringEx(p0, var8, var4, var14, var30, var2C->i18, 0);
			} else {
				var2C->i0->drawString(p0, var8, var4, var14);
			}

			break;
		} else {
			if (var38 <= 0) {
				var14++;
			} else {
				auto var18 = *(var14 + var38);
				*(var14 + var38) = '\0';

				if (var2C->i4 == 0) {
					var2C->i0->drawStringEx(p0, var8, var4, var14, var30, var2C->i18, 0);
				} else {
					var2C->i0->drawString(p0, var8, var4, var14);
				}

				*(var14 + var38) = var18;
				var14 += var38;
			}

			var4 += var2C->i0->unk1();

			if (i36 == 2) {
				var34 = var2C->i0->calculateTextWidth(var14, 0, 0);
				
				if (var34 < rect.getWidth()) {
					t = var8 = rect.right - rect.left - var34;
					if (t < 0)
						t++;

					var8 = rect.left + (int)std::floor((float)t / 2);
				} else {
					var8 = rect.left;
				
				}

			}
		}

	} while (true);
}

void UnkClass800::reset()
{
	i32 = nullptr;
}

void UnkClass800::setText(const char * p0)
{
	if (i32 != nullptr) {
		free(i32);
		i32 = nullptr;
	}

	if (p0 != nullptr) {
		i32 = (char *) malloc(strlen(p0) + 1);

		if (i32 != nullptr)
			memcpy(i32, p0, strlen(p0) + 1);	
	}

	registerForDraw();
}
