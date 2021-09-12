#include "UnkClass2000.h"

#include "InGame.h"
#include "UnkGame5.h"
#include "MiniMapMaybe.h"
#include "Map.h"
#include "Tile.h"
#include "ClassyTwo.h"
#include "UnitManager.h"
#include "UnkGame6.h"
#include "graphics/Bitmap.h"

#include <cmath>
UnkClass2000::UnkClass2000(int p0)
	: UIElement { InGame::unkGame5_instance->i52, p0, 0, -1 }, i32 { InGame::unkGame5_instance->i52 }, i48 { 0 }
{
	i21_flags |= 0x7200; // CHeck if correct
}

UnkClass2000::~UnkClass2000()
{
}

void UnkClass2000::vtable4(DrawableSurface & surface) { }

void UnkClass2000::unk111(knights_and_merchants::io::MouseHandler * p0)
{
}

bool UnkClass2000::unk2(POINT & point, int & p4, int & p8, int p12_playerID)
{
	int var4;
	int var8;

	if (unk3(point.x, point.y, var4, var8)) {
		auto ax = unk4(point, p12_playerID);

		if (ax != -1) {
			p8 = 0;
			p4 = ax;
			return true;
		}

		if ((Map::instance->getTile(var4, var8).i3 & 0x10) == 0x10) {
			auto eax = Map::instance->unk13(var4, var8);

			if (eax != -1) {
				p8 = 1;
				p4 = eax;
				return true;
			}
		}
	}

	return false;
}

bool UnkClass2000::unk3(const int p0_mouseX, const int p4_mouseY, int & p8_outX, int & p12_outY)
{
	int sX = p0_mouseX - InGame::unkGame5_instance->i52.left;
	int sY = p4_mouseY - InGame::unkGame5_instance->i52.top;

	if (sX < 0 || sY < 0)
		return false;

	auto ecx = sX / 40 + InGame::miniMapMaybe_instance->i46;
	auto ebx = sY / 40 + InGame::miniMapMaybe_instance->i50;

	while (ebx <= Map::instance->i12_height - 2) {
		auto esi = 40 * (ebx - InGame::miniMapMaybe_instance->i50);

		if (sY >= (esi - Map::instance->getTile(ecx, ebx).i2_height))
			if (sY < (esi - Map::instance->getTile(ecx, ebx + 1).i2_height + 40))
				break;

		ebx++;
	};

	p8_outX = ecx;
	p12_outY = ebx;
	return true;
}

short UnkClass2000::unk4(POINT & p0, int p4_playerID)
{
	Rect rect { };
	int var24;
	int var28;

	if (unk3(p0.x, p0.y, var28, var24)) {
		auto var1C = InGame::unkGame5_instance->i52.left + 40 * (var28 - InGame::unkGame5_instance->i36.left);
		auto var18 = InGame::unkGame5_instance->i52.top  + 40 * (var24 - InGame::unkGame5_instance->i36.top );

		Map::classyTwo_instance->setPosition(var28, var24);

		for (int var20 = -1; var20 < 8; ++var20) {
			if (var20 < 0 || Map::classyTwo_instance->move(var20)) {
				short var14 = Map::instance->getTile(Map::classyTwo_instance->i0_x, Map::classyTwo_instance->i1_y).i7_unitID;

				if (var14 != -1) {
					Unit & unit = Map::unitManager->getElement(var14);

					if (unit.i0_type < Unit::Wolf && unit.i54 != 3) {
						if (unit.i54 <= 9 || unit.i54 > 11) {
							auto ebx = var1C + 40 * (Map::classyTwo_instance->i0_x - var28) + 20;
							auto esi = var18 + 40 * (Map::classyTwo_instance->i1_y - var24)
								- Map::instance->getTile(Map::classyTwo_instance->i0_x, Map::classyTwo_instance->i1_y).i2_height
								+ Map::instance->getTile(Map::classyTwo_instance->i0_x, Map::classyTwo_instance->i1_y).i4;

							if (unit.i12 != -1) {
								knights_and_merchants::graphics::Bitmap * ebp = InGame::unkGame6_instance->i80->i0_bitmaps[unit.i12];

								rect.setBounds(ebx, esi, ebp->i0_width, ebp->i2_height);
								rect.move(ebp->i4, ebp->i8);
								
								if (unit.i24 != 0) {
									rect.move(
										std::floor((unit.i26 * unit.i24) / 256.f),
										std::floor((unit.i28 * unit.i24) / 256.f)
									);
								
									if (unit.i54 == 3) {
										rect.move(unit.i40, unit.i41);
									}
								}

								if (PtInRect(&rect, p0))
									return var14;

							}
						}
					}
				}

				if (var20 >= 0)
					Map::classyTwo_instance->moveOpposite(var20);
			}
		}
	}

	return -1;
}
