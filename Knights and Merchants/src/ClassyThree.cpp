#include "ClassyThree.h"
#include "Map.h"
#include "HouseManager.h"
#include "HousesDat.h"
#include "utilities/Rect.h"
#include "InGame.h"
#include "graphics/Bitmap.h"
#include "Tile.h"
#include "Unit.h"
#include "RandomGenerator.h"
#include "ClassyTwo.h"

char ClassyThree::unk493F2C[4][3] = {
	{ 0, 0x10, 0x40 }, 
	{ 2, 0x20, 0x80 }, 
	{ 4, 0x40, 0x10 }, 
	{ 6, 0x80, 0x20 }
};

void ClassyThree::clearUpUnit(const Unit & unit) const
{
	clearUpCircle(unit.i8_x, unit.i9_y, unit.getDefines().i14_clearUpRange, unit.i3_player);
}

void ClassyThree::clearUpHouse(const int houseID, const int playerID) const
{
	const House & house { Map::houseManager->getElement(houseID) };
	clearUpCircle(house.i2_x, house.i3_y, house.getDefines().i1649_clearUpRange, playerID);
}

void ClassyThree::clearUpCircle(const int p0, const int p4, const short p8, const int p12) const
{
	knights_and_merchants::utilities::Rect rect{};
	auto byte_4B9774 = p12;

	int eax = p8;
	if (p8 >= 1) {
		if (p8 > 16)
			eax = 16;
	} else {
		eax = 1;
	}

	knights_and_merchants::graphics::Bitmap & bitmap { *InGame::guiRx_getBitmap(419 + eax) };

	auto dword_4B9784 = bitmap.i12_data;
	rect.setBounds(p0 - bitmap.i0_width / 2, p4 - bitmap.i2_height / 2, bitmap.i0_width, bitmap.i2_height);

	Map::instance->snapRectangleOnMap(rect);

	dword_4B9784 += ((bitmap.i2_height / 2) - p4 + rect.top) * bitmap.i0_width;
	dword_4B9784 += (bitmap.i0_width / 2) - p0 + rect.left;

	auto word_4B9780 = bitmap.i0_width - rect.getWidth();
	auto word_4B9776 = 23 * (Map::instance->i8_width + rect.left) - 23 * (rect.right);

	auto & dword_4B9788 = Map::instance->getTile(rect.left, rect.top);

	auto word_4B978E = rect.right - rect.left;
	auto dword_4B977C = rect.bottom - rect.top;
	auto word_4B978C = 23;

	auto edx = (word_4B978C << 16) | word_4B978E;
	auto ebx = (word_4B9776 << 16) | (byte_4B9774 << 8 /* as bit*/) | byte_4B9774;
	//auto eax = (word_4B9780 << 16);

	auto esi = dword_4B9784;
	auto * edi = &dword_4B9788;

	while (dword_4B977C--) {
		auto wid = word_4B978E;

		while (wid--) {
			if (*esi != 0 && !edi->isCleared(p12))
				edi->clearUp(p12);

			esi++;
			edi++;
		}

		esi += word_4B9780;
		edi += (Map::instance->i8_width + rect.left) - rect.right;
	}
}

void ClassyThree::setStreet(const int x, const int y, const int playerID) const
{
    knights_and_merchants::utilities::Rect rect { };
	unk15(x, y, playerID);

	rect.setBounds(x - 1, y - 1, 3, 3);

	Map::instance->snapRectangleOnMap(rect);

	for (int nY = rect.top; nY < rect.bottom; ++nY)
		for (int nX = rect.left; nX < rect.right; ++nX)
			if ((Map::instance->getTile(nX, nY).i22 & 1) == 1)
				unk15(nX, nY, playerID);

	rect.left++;
	rect.top++;
	Map::instance->unk9(rect);
	Map::wellDontKnow(rect);
}

void ClassyThree::setField(const int playerID, const int p4, const int x, const int y) const
{
    knights_and_merchants::utilities::Rect rect{};

	Tile & esi = Map::instance->getTile(x, y);
	esi.i15 = playerID;
	esi.i21 = p4 | 0xF0;

	Map::classyTwo_instance->setPosition(x, y);

	switch (p4) {
	case 1:
		Map::instance->unk10(x, y, 0, 62);
		esi.setDirection(0);
		esi.unk8(0, 0);
		break;
	case 2:
		esi.i5_objectID = 54;
		esi.unk8(0, 0);
		break;
	}

	for (auto & edi : unk493F2C) {
		if (Map::classyTwo_instance->move(edi[0])) {
			Tile & eax = Map::instance->getTile(Map::classyTwo_instance->i0_x, Map::classyTwo_instance->i1_y);

			if (eax.i15 == playerID && (eax.i21 & 0xF) == p4) {
				eax.i21 = ~edi[2] & eax.i21;
				eax.i21 = ~edi[1] & eax.i21;
			}

			Map::classyTwo_instance->moveOpposite(edi[0]);
		}
	}

	rect.setBounds(x, y, 1, 1);
	rect.inflate(1, 1);

	if (Map::instance->snapRectangleOnMap(rect))
		Map::wellDontKnow(rect);

}

void ClassyThree::unk15(const int x, const int y, const int playerID) const
{
	struct {
		int i0;
		int i4;
		char i8;
	} static dword_493F08[4] { 
		{ -1,  0, 1 },
		{  1,  0, 2 },
		{  0, -1, 4 },
		{  0,  1, 8 }
	};

	auto var11 = 0;
	auto var12 = 1;
	auto var10 = 0;
	auto varC = 0;

	for (auto & what : dword_493F08) {
		if (Map::instance->areCoordinatesValid(what.i0 + x, what.i4 + y)) {
			if ((Map::instance->getTile(what.i0 + x, what.i4 + y).i22 & 1) == 1) {
				varC |= what.i8;
				var11++;
			}
		}
	}

	if (var11 != 1) {
		if (var11 != 2) {
			if (var11 != 3) {
				if (var11 == 4) {
					var10 = Map::class666_instance->next(4);
					var12 = 4;
				}
			} else {
				var12 = 3;
				switch (varC) {
				case 7:
					var10 = 3;
					break;
				case 11:
					var10 = 1;
					break;
				case 13:
					var10 = 2;
					break;
				case 14:
					var10 = 0;
					break;
				}
			}
		} else {
			if (varC != 3) {
				if (varC != 12) {
					var12 = 2;

					switch (varC) {
					case 5:
						var10 = 2;
						break;
					case 6:
						var10 = 3;
						break;
					case 9:
						var10 = 1;
						break;
					case 10:
						var10 = 0;
						break;
					}


				} else {
					var10 = 2 * Map::class666_instance->next(2);
				}
			} else {
				var10 = 2 * Map::class666_instance->next(2) + 1;
			}
		}
	} else {
		if ((varC & 3) == 0) {
			var10 = 2 * Map::instance->class666_instance->next(2);
		} else {
			var10 = 2 * Map::instance->class666_instance->next(2) + 1;
		}
	}

	Tile & esi = Map::instance->getTile(x, y);

	char value = esi.i21 & 0xF;
	if (value > 0 && value <= 2) {
		esi.i5_objectID = 255;
		unk14(0, x, y);
		esi.unk11(0);
	}

	esi.unk8(2 * var12 - 1, var10);
	esi.i15 = playerID;

}

void ClassyThree::unk14(const int p0, const int x, const int y) const
{
	Tile & eax = Map::instance->getTile(x, y);

	auto bl = (eax.i21 & 0xF);
	if (bl != 0) {
		eax.unk11(0);

		auto & c = *Map::classyTwo_instance;

		c.setPosition(x, y);

		for (int i = 0; i < 4; ++i) {
			if (c.move(unk493F2C[i][0])) {
				Tile & t = Map::instance->getTile(c.i0_x, c.i1_y);

				auto dl = t.i21 & 0xF;
				if (dl == bl) {
					t.i21 |= unk493F2C[i][2];
				}

				c.moveOpposite(unk493F2C[i][0]);
			}
		}
	}
}
