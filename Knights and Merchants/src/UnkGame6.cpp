#include "UnkGame6.h"
#include "graphics/RX.h"
#include "UnkGame1.h"
#include "engine/GraphicsHandler.h"
#include "Map.h"
#include "graphics/Bitmap.h"
#include "Tile.h"
#include "InGame.h"
#include "UnkClass900.h"
#include "HouseManager.h"
#include "HousesDat.h"
#include "UnitManager.h"
#include "UnitDat.h"
#include "graphics/DrawableSurface.h"

char UnkGame6::drawUnitUnkArray[8] { 3, 2, 2, 1, 6, 7, 6, 6 };

short UnkGame6::unkTable[64];

void UnkGame6::calculateUnkTable()
{
	
	for (int i = 0; i < 64; ++i) {
		unkTable[i] = static_cast<short>(9.0 * sin(0.0490873852109375 * i)); // 0.0490873852109375 = pi / 64
	}
}

UnkGame6::UnkGame6(const Rect & rect)
	: i0 { rect }
{
	reset();

	i20 = i0.getWidth();
	i28 = i20;

	i24 = i0.getHeight();
	i32 = i24;

	i76 = new knights_and_merchants::graphics::RX("data/gfx/res/trees.rx");
	i80 = new knights_and_merchants::graphics::RX("data/gfx/res/units.rx");
	i84 = new knights_and_merchants::graphics::RX("data/gfx/res/houses.rx");

	i40 = UnkGame1::instance->i0 + 0x500;
}

UnkGame6::~UnkGame6()
{
	if (i76 != nullptr)
		delete i76;

	if (i80 != nullptr)
		delete i80;

	if (i84 != nullptr)
		delete i84;

	reset();
}

void UnkGame6::reset()
{
	for (int i = 0; i < 8; ++i)
		i44[i] = nullptr;

	i40 = nullptr;
	i76 = nullptr;
	i80 = nullptr;
	i84 = nullptr;
	i16 = 0;
}

void UnkGame6::draw(knights_and_merchants::graphics::DrawableSurface & p0, int p4, int p8, bool p12)
{
	i88 = InGame::instance.i129_humanPlayerID;
	i91 = InGame::instance.i8;
	i89 = InGame::unkClass900_instance->getSelectedGroupID();

	auto var10 = p4;
	auto var14 = p8;

    knights_and_merchants::graphics::DrawableSurface varC { p0 };

	varC.i0_width = 40 * i28;
	varC.i2_height = (i16 != 0) ? i36 : 40 * i32;
	varC.i6_surface += p0.i4_pitch * i0.top + i0.left;

	auto var2C = i28;

	int eax = 0;

	while (p8 - eax > 1) {
		if (eax >= 4)
			break;

		eax++;
	}

	auto var44 = eax;

	p8 -= var44;
	auto var18 = -40 * var44 ;
	auto var28 = Map::instance->i12_height - 1;

	auto ebx = 0;


	if (var44 + p8 < var28) {
		auto var24 = i32 + 5;
		auto edx = 0;

		while (edx < var24) {
			ebx++;
			edx = ebx;
			if (ebx + var44 + p8 >= var28)
				break;
		}
	}

	var44 += ebx;

	auto ecx = 0;
	while (i28 + p4 + ecx < Map::instance->i8_width - 2) {
		if (ecx >= 4)
			break;

		ecx++;
	}

	eax = 0;

	while (p4 - eax > 1) {
		if (eax >= 4)
			break;

		eax++;
	}
	
	ecx += eax;
	p4 -= eax;

	auto var24 = -40 * eax;
	auto var3C = var2C + ecx;

	// Until here is checked for (2, 4)
	var2C = var3C + p4 - 1;

	auto var30 = var3C;
	auto var20 = var24 + 40 * (var30 - 1);

	Tile * esi;
	auto edi = var18;
	for (int var40 = 0; var40 < var44; ++var40) {
		Tile * ebp = &Map::instance->getTile(var2C, var40 + p8);
		auto var4C = var20;

		if (var3C > 0) {
			auto var38 = var4C + 40;
			esi = ebp + 1;

			for (int var28 = var30; var28 > 0; --var28) {
				if ((esi - 1)->isCleared(i88)) {
					if ((esi - 1)->isI17(i88)) {
						auto var34 = InGame::guiRx_getBitmap(ebp->unk9(i88) + 103);
						auto arg0 = InGame::guiRx_getBitmap(ebp->unk9(i88) + 115);

						if ((ebp->unk9(i88) - 2) == 0) {

							if ((ebp - Map::instance->i8_width)->unk9(i88) != 2) {
								var34->unk1(varC, var4C, edi - (esi - 1)->i2_height, (esi - 1)->i2_height - esi->i2_height);
							}

							if ((esi - 2)->unk9(i88) != 2) {
								arg0->unk2(varC, var4C, edi - (esi - 1)->i2_height, nullptr, (esi - 1)->i2_height - (ebp + Map::instance->i8_width)->i2_height + 40);
							}

							if (esi->unk9(i88) != 2) {
								arg0->unk2(varC, var38, edi - esi->i2_height, nullptr, esi->i2_height - (esi + Map::instance->i8_width)->i2_height + 40);
							}

							if ((ebp + Map::instance->i8_width)->unk9(i88) != 2) {
								var34->unk1(varC, var4C, edi - (ebp + Map::instance->i8_width)->i2_height + 40, (ebp + Map::instance->i8_width)->i2_height - (ebp + Map::instance->i8_width + 1)->i2_height);
							}

							if ((esi - 1)->i16 != -1) {
								InGame::guiRx_getHouseSign((esi - 1)->i16)->drawRemapped(varC, var38 - 14, (esi - 1)->i4 - (esi - 1)->i2_height + edi, nullptr);
							}
						
						} else {
							var34->unk1(varC, var4C, edi - (esi - 1)->i2_height, (esi - 1)->i2_height - (ebp + Map::instance->i8_width + 1)->i2_height + 40);
							var34->unk1(varC, var4C, edi - (ebp + Map::instance->i8_width)->i2_height + 40, (ebp + Map::instance->i8_width)->i2_height - esi->i2_height - 40);
						}
					}

					if (((esi - 1)->i21 & 0xF) != 0) {
						// TODO: reverse
					}
				}

				var4C -= 40;
				var38 -= 40;
				ebp--;
				esi--;
			}
		} 

		edi += 40;
	}

	auto arg0 = var18;

	auto var38 = var3C + p4;
	var2C = var38 - 1;
	var30 = var3C;
	p4 = 40 * var30 + var24;

	for (int var40 = 0; var40 < var44; ++var40) {
		auto var34 = var40 + p8;
		auto ebx = p4 - 40;

		Tile * esi = &Map::instance->getTile(var2C, var34);

		
		for (int var24 = var30; var24 > 0; --var24) {
			
			if (esi->isCleared(i88)) {
				
				if (esi->i9_houseID != -1) {
					drawHouse(varC, ebx, arg0 - esi->i2_height, esi->i9_houseID);
				}

				if (esi->i5_objectID != 255) { // TODO: Getreide und soetwas wird anscheinend noch nicht richtig angezeigt
					if (InGame::mapelemDat[esi->i5_objectID].i82 == 0) {
						i76->i0_bitmaps[InGame::mapelemDat[esi->i5_objectID].i0_frames[(esi->getObjectAnimationDelta() + i91) % InGame::mapelemDat[esi->i5_objectID].i60_frameCount]]->draw(varC, ebx, arg0 - esi->i2_height);
					} else {
						drawObject(varC, ebx, arg0, *esi);
					}
				}
			}

			esi--;
			ebx -= 40;
		}
		
		ebx = p4 + 20;

		if (var3C > 0) {
			Tile * esi = &Map::instance->getTile(var38, var34);

			for (int i = 0; i < var30; ++i) {
				
				if (esi->isCleared(i88) && esi->i7_unitID != -1) {
					Unit & unit = Map::unitManager->getElement(esi->i7_unitID);

					if (unit.i24 != 0 && unit.i10_direction == 5 && unit.i24 > 0x80) {
						drawUnit(varC, ebx, esi->i4 - esi->i2_height + arg0, unit, p12);
					}	
				}

				esi--;
				ebx -= 40;
			}
		}


		if (var3C + 1 > 0) {
			Tile * esi = &Map::instance->getTile(var38, var34);
			ebx = p4 + 20;
			
			for (int var24 = var3C + 1; var24 > 0; var24--) {
				if (esi->isCleared(i88)) {
					if (esi->i7_unitID != -1) {
						Unit & unit = Map::unitManager->getElement(esi->i7_unitID);

						if (unit.i24 == 0) { // TODO: Is this really equal?
							drawUnit(varC, ebx, esi->i4 - esi->i2_height + arg0, unit, p12);
						} else {
							drawUnit(varC, ebx, esi->i4 - esi->i2_height + arg0, unit, p12);
						}
					}

					if (esi->i5_objectID != 255) {
						// TODO: reverse this object stuff
					}


				}

				esi--;
				ebx -= 40;
			}
		}

		if (var3C + 1 > 0) {
			Tile * esi = &Map::instance->getTile(var38, var34);
			ebx = p4 + 20;

			for (int i = 0; i < var3C + 1; ++i) {
				if (esi->isCleared(i88) && esi->i7_unitID != -1) {
					Unit & unit = Map::unitManager->getElement(esi->i7_unitID);

					if (unit.i24 != 0 && unit.i10_direction == 1) {
						drawUnit(varC, ebx, esi->i4 - esi->i2_height + arg0, unit, p12);
					}

				}

				esi--;
				ebx -= 40;
			}
		}




		arg0 += 40;
	}


}

void UnkGame6::drawUnit(knights_and_merchants::graphics::DrawableSurface & surface, int p4, int p8, Unit & unit, bool p16)
{
	if (unit.i54 <= 9) {
		auto var14 = 0;
		auto var4 = 0;
		auto var8 = unit.i56;
		auto & unitData = Map::unitDat_instance->i15680[unit.i0_type];
		auto varC = unit.i10_direction;
		auto var10 = unit.i57;

		if (unit.i54 == 3) {
			var14 = 1;
			p8 += unit.i40;
			p4 += unit.i41;
		}

		int argC;
		if (unit.i24 != 0) {
			p4 += floor((unit.i26 * unit.i24) / 256.f);
			p8 += floor((unit.i28 * unit.i24) / 256.f);

			if (unit.i30 != 0) {
				short cx = UnkGame6::unkTable[unit.i24 / 4];

				switch (unit.i10_direction) {
				case 0:
					p4 -= cx;
					break;
				case 1:
					p4 -= cx;
					p8 -= cx;
					break;
				case 2:
					p8 -= cx;
					break;
				case 3:
					p4 += cx;
					p8 -= cx;
					break;
				case 4:
					p4 += cx;
					break;
				case 5:
					p4 += cx;
					p8 += cx;
					break;
				case 6:
					p8 += cx;
					break;
				case 7:
					p4 -= cx;
					p8 += cx;
					break;
				}
			}

			var14 = 1;

			if (unit.i54 == 5)
				var14 = 0;

			argC = 1;
		} else {
			if (unit.i11 != -1 || unit.i54 < 4)
				var14 = 1;

			argC = unit.i54;
		}

		if (unit.i54 != 9) {
			if (unit.i0_type >= Unit::Militia && unit.i0_type <= Unit::Ballista && unit.i49_isGroupLeader) {

				if (unit.i10_direction <= 2 || unit.i10_direction >= 7) {
					var4 = 1;
				} else {
					AnimationEntry & e = unitData.i4502_troupFlagAnimations[unit.i10_direction];

					if (unit.i47_groupId != i89) {
						i80->i0_bitmaps[e.i0_frames[i91 % e.i60_frameCount]]->drawRemapped(surface, p4 + e.i62, p8 + e.i66, i44[unit.i3_player]);
					} else {
						i80->i0_bitmaps[e.i0_frames[i91 % e.i60_frameCount]]->drawRemapped(surface, p4 + e.i62, p8 + e.i66, UnkGame1::instance->i60[unit.i3_player][i91 & 1]);
					}
				}
			}

			if (var14 == 0) {
				AnimationEntry & e = (unit.i56 == -1) ? unitData.i22[1][unit.i10_direction] : unitData.i22[unit.i56][unit.i10_direction];

				short frame = e.i0_frames[unit.i14 % e.i60_frameCount];

				i80->i0_bitmaps[frame]->drawRemapped(surface, p4, p8, i44[unit.i3_player]);
				unit.i12 = frame;
			} else {
				short next;

				if (unit.i0_type != Unit::Fish) { 
					if (argC != 0) {
						AnimationEntry & e = unitData.i22[0][unit.i10_direction];
						next = e.i0_frames[unit.i14 % e.i60_frameCount];
					} else {
						AnimationEntry & e = unitData.i22[0][unit.i10_direction];
						next = e.i0_frames[drawUnitUnkArray[unit.i10_direction] % e.i60_frameCount];
					}
				} else {
					AnimationEntry & e = unitData.i22[unit.i1][unit.i10_direction];
					next = e.i0_frames[drawUnitUnkArray[unit.i10_direction] % e.i60_frameCount];
				}

				i80->i0_bitmaps[next]->drawRemapped(surface, p4, p8, i44[unit.i3_player]);
				unit.i12 = next;

				if (unitData.i18 != 0) {
					// TODO:
				}
			}

			if (unit.i19 != -1) {
				i80->i0_bitmaps[6250 + unit.i17 & 3 + 8 * unit.i19]->draw(surface, p4, p8 - 60);
			}

			if (var4 != 0) {
				AnimationEntry & edi = unitData.i4502_troupFlagAnimations[varC];
				
				if (unit.i47_groupId != i89) {
					i80->i0_bitmaps[edi.i0_frames[i91 % edi.i60_frameCount]]->drawRemapped(surface, p4 + edi.i62, p8 + edi.i66, i44[unit.i3_player]);
				} else {
					i80->i0_bitmaps[edi.i0_frames[i91 % edi.i60_frameCount]]->drawRemapped(surface, p4 + edi.i62, p8 + edi.i66, UnkGame1::instance->i60[unit.i3_player][i91 & 1]);
				}
			}
		} else {
			AnimationEntry & e = unitData.i22[3][unit.i10_direction];
			i80->i0_bitmaps[e.i0_frames[unit.i14 % e.i60_frameCount]]->draw(surface, p4, p8);
			return;
		}
	}
}

void UnkGame6::drawHouse(knights_and_merchants::graphics::DrawableSurface & p0, int p4, int p8, short p12)
{
	House & house = Map::houseManager->getElement(p12);

    HouseDefineData & housesData = Map::housesDat_instance->i2100[house.i0_type];

	if (house.i7 == 0)
		return;
	
	if (house.i7 == 1) {
	
	} else {
		i84->i0_bitmaps[housesData.i0_graphic1]->drawRemapped(p0, p4, p8, nullptr);

		if (house.i0_type != 11) {
			for (int i = 0; i < 4; ++i) {
				char eax = house.i10.done.i10[i];

				if (housesData.i1638[i] != -1 && eax > 0) {
					eax--;

					if (eax >= 5)
						eax = 4;

					short graphic = housesData.i8_inputWareGraphics[i][eax];
					if (graphic != -1) {
						i84->i0_bitmaps[graphic]->draw(p0, p4, p8);
					}
				}
			}

			switch (house.i0_type) {
			case 2: case 10: case 19: case 20:

				for (int i = 0, ebx = 0; i < 4; ++i) {
					if (housesData.i1642[i] != -1 && house.i10.done.i18[i] > 0) {
						
						for (int edi = 0; edi < house.i10.done.i18[i]; ++edi, ++ebx) {
							if (ebx >= 5)
								goto switchEnd;

							i84->i0_bitmaps[housesData.i48_outputWareGraphics[i][ebx]]->draw(p0, p4, p8);
						}

						if (ebx >= 5)
							break;
						
					}
				}
				break;
			default:
				// TODO: aaa
				break;
			}
		switchEnd:;
	
		}

		AnimationEntry & x = housesData.i508;
		if (x.i60_frameCount > 0)
			i84->i0_bitmaps[x.i0_frames[(i91 + p12) % x.i60_frameCount]]->drawRemapped(p0, x.i62 + p4, x.i66 + p8, nullptr);

		switch (house.i0_type) {
		case 12:	
		case 16:
		case 27:
			throw 0; // TODO: reverse the cases.
		}

		switch (house.i7) {
		case 3: case 5:
			if (house.i10.done.i37_isOccupied != 0 && housesData.i578_occupiedAnimation.i60_frameCount > 0)
				i84->i0_bitmaps[housesData.i578_occupiedAnimation.i0_frames[i91 % housesData.i578_occupiedAnimation.i60_frameCount]]->drawRemapped(p0, housesData.i578_occupiedAnimation.i62 + p4, housesData.i578_occupiedAnimation.i66 + p8, i44[house.i1_playerID]);
			
			break;
		case 4:
			if (house.i10.done.i28 != -1 && housesData.i88[house.i10.done.i28].i60_frameCount > 0)
				i84->i0_bitmaps[housesData.i88[house.i10.done.i28].i0_frames[house.i10.done.i26 % housesData.i88[house.i10.done.i28].i60_frameCount]]->drawRemapped(p0, housesData.i88[house.i10.done.i28].i62 + p4, housesData.i88[house.i10.done.i28].i66 + p8, i44[house.i1_playerID]);

			if (housesData.i438.i60_frameCount > 0)
				i84->i0_bitmaps[housesData.i438.i0_frames[(i91 + p12) % housesData.i438.i60_frameCount]]->drawRemapped(p0, housesData.i438.i62 + p4, housesData.i438.i66 + p8, nullptr);

			break;
		}

		for (int i = 0; i < 3; ++i) {
			const AnimationEntry & e = housesData.i648_flagAnimations[i];

			if (e.i60_frameCount <= 0)
				break;
			
			i84->i0_bitmaps[e.i0_frames[i91 % e.i60_frameCount]]->drawRemapped(p0, e.i62 + p4, e.i66 + p8, i44[house.i1_playerID]);
		}

		for (int i = 0; i < house.i6_visibleFlames; ++i) {
			const AnimationEntry & e = housesData.i858_flameAnimations[i];
			i84->i0_bitmaps[e.i0_frames[i91 % e.i60_frameCount]]->draw(p0, e.i62 + p4, e.i66 + p8);
		}
	}
}

void UnkGame6::drawObject(knights_and_merchants::graphics::DrawableSurface & p0, int p4, int p8, Tile & p12)
{
	auto & mapElem = InGame::mapelemDat[p12.i5_objectID];

	knights_and_merchants::graphics::Bitmap * bitmap = i76->i0_bitmaps[mapElem.i0_frames[(p12.getObjectAnimationDelta() + i91) % mapElem.i60_frameCount]];
	
	int esi = p12.i4 / 2;
	bitmap->draw(p0, p4 + 8, esi - p12.i2_height + p8);
	bitmap->draw(p0, p4 + 28, esi - (&p12 + 1)->i2_height + p8);
}


