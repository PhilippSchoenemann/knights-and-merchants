#include "UnkGame20.h"
#include "Map.h"
#include "UnitManager.h"
#include "io/InputHandler.h"
#include "io/MouseHandler.h"
#include "InGame.h"
#include "UnkClass900.h"
#include "UnkClass2000.h"
#include "HouseManager.h"

UnkGame20 * UnkGame20::instance;

UnkGame20::UnkGame20()
{
	i0 = 0;
	i2_wasLeftButtonDown = 0;
	i6_wasRightButtonDown = 0;
	i10_wasMiddleButtonDown = 0;
	i14 = 0;
	i18 = 0;
	i22_currentCursor = 0;
}


UnkGame20::~UnkGame20()
{
}

bool UnkGame20::unk6(const bool p0_isLeftButtonDown, const bool p4_isRightButtonDown, const bool p8_isMiddleButtonDown)
{
	auto var18 = InGame::instance.i129_humanPlayerID;
	auto var4 = 0;

	if (!p0_isLeftButtonDown || (i2_wasLeftButtonDown != 0 && i0 != 3)) {
		if (!p4_isRightButtonDown || i6_wasRightButtonDown != 0) {
			if (i0 != 1) {
				int var10;
				int var14;
				POINT varC = knights_and_merchants::io::InputHandler::instance->getMouseHandler()->i0_position;
				
				auto edi = InGame::unkClass2000_instance->unk2(varC, var10, var14, var18);

				if (edi) {
					switch (var14) {
					case 0:
						Map::unitManager->getElement(var10);
						break;
					case 1:
						Map::houseManager->getElement(var10);
						break;
					}
				}

				switch (i0) {
				case 3:
					break;
				case 4:
					break;
				case 7:
					break;
				default:

					if (edi) {
						if (var14 == 0) {
							if (Map::unitManager->getElement(var10).i3_player != var18) {
								UnkGame20::instance->unk5(InGame::someBitmaps[0]);
							} else {
								UnkGame20::instance->unk5(InGame::guiRx_getBitmap(452));
							}
						} else if (var14 == 1) {
							if (Map::houseManager->getElement(var10).i1_playerID != var18) {
								UnkGame20::instance->unk5(InGame::someBitmaps[0]);
							} else {
								UnkGame20::instance->unk5(InGame::guiRx_getBitmap(451));
							}
						}
					} else {
						UnkGame20::instance->unk5(InGame::someBitmaps[0]);
					}

					break;
				}
			}
		} else {
			if (i0 == 1) {
				InGame::unkClass900_instance->unk1(0, 0);
				unk8();
			} else {
				
			}
		}
	} else {
	
	}

	i2_wasLeftButtonDown = p0_isLeftButtonDown;
	i6_wasRightButtonDown = p4_isRightButtonDown;
	i10_wasMiddleButtonDown = p8_isMiddleButtonDown;
	return var4;
}

void UnkGame20::unk7()
{
}

void UnkGame20::unk8()
{
	i0 = 0;
	unk9();
}

void UnkGame20::unk9()
{
	unk5(InGame::someBitmaps[0]);
}

void UnkGame20::unk3()
{
	Unit & unit = Map::unitManager->getElement(i28_unitID);

	i18 = 0;
	if (i14 == 0) {
        knights_and_merchants::io::InputHandler::instance->getMouseHandler()->unfreezeCursor();
	}

	throw 0;
}

void UnkGame20::unk4()
{
    knights_and_merchants::io::InputHandler::instance->getMouseHandler()->freezeCursor();
	unk5( InGame::guiRx_getBitmap(450) );

	i14 = 1;
	i43 = 0;
	i39 = 0;
}

void UnkGame20::unk5(const knights_and_merchants::graphics::Bitmap * cursor)
{
	if (cursor != i22_currentCursor) {
		i22_currentCursor = cursor;
        knights_and_merchants::io::InputHandler::instance->getMouseHandler()->setCursor(cursor);
	}
}
