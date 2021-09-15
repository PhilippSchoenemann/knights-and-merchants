#include "UnkGame111.h"
#include "UnkGame1.h"
#include "InGame.h"
#include "ui/UnkClass201.h"
#include "ui/UnkClass202.h"
#include "graphics/Palette.h"
#include "Globals.h"
#include "Settings.h"
#include "UnkClass670.h"
#include "UnkClass671.h"
#include "ArrayBriefings.h"
#include "Settings.h"
#include "graphics/Bitmap.h"
#include "MiniMapMaybe.h"
#include "UnkGame20.h"
#include "io/InputHandler.h"
#include "ui/UnkClass203.h"
#include "UnkClass2000.h"
#include "engine/GraphicsHandler.h"
#include "Settings.h"
#include "graphics/DrawableSurface.h"
#include "io/MouseHandler.h"
#include "io/KeyboardHandler.h"

using knights_and_merchants::Settings;

UnkClass201 UnkGame111::uc201[8];
UnkClass202 UnkGame111::uc202[6];

UnkGame111::UnkGame111(const Rect & rect)
	: UnkClass200 { rect }
{
	reset();

	knights_and_merchants::graphics::Palette * palette = UnkGame1::instance->i144;

	UnkGame111::uc201[0].i4 = 0;
	UnkGame111::uc201[0].i8 = palette->getMostSimilarColor(190, 190, 190);
	UnkGame111::uc201[0].i10 = palette->getMostSimilarColor(100, 100, 100);
	UnkGame111::uc201[0].i12 = palette->getMostSimilarColor(25, 25, 25);
	UnkGame111::uc201[0].i14 = palette->getMostSimilarColor(20, 20, 20);
	UnkGame111::uc201[0].i16 = palette->getMostSimilarColor(180, 180, 180);
	UnkGame111::uc201[0].i18 = palette->getMostSimilarColor(170, 0, 0);
	UnkGame111::uc201[0].i20 = palette->getMostSimilarColor(250, 250, 150);
	UnkGame111::uc201[0].i22 = palette->getMostSimilarColor(180, 180, 180);
	UnkGame111::uc201[0].i24 = InGame::guiRx_getBitmap(401);

	UnkGame111::uc202[0].i4 = UnkGame111::uc201[0].i10;

	UnkGame111::uc201[1] = UnkGame111::uc201[0];
	UnkGame111::uc201[2] = UnkGame111::uc201[0];

	UnkGame111::uc201[1].i18 = palette->getMostSimilarColor(250, 60, 60);
	UnkGame111::uc201[1].i16 = palette->getMostSimilarColor(240, 180, 130);
	UnkGame111::uc201[1].i12 = palette->getMostSimilarColor(40, 40, 40);

	UnkGame111::uc201[3] = UnkGame111::uc201[0];
	UnkGame111::uc201[4] = UnkGame111::uc201[0];
	UnkGame111::uc201[5] = UnkGame111::uc201[0];
	UnkGame111::uc201[6] = UnkGame111::uc201[0];
	UnkGame111::uc201[7] = UnkGame111::uc201[0];

	UnkGame111::uc201[5].i24 = InGame::guiRx_getBitmap(word_4982C0[Settings::instance.i268_resolution].i0);
	UnkGame111::uc201[5].i16 = palette->getMostSimilarColor(50, 25, 0);
	UnkGame111::uc201[5].i18 = palette->getMostSimilarColor(60, 45, 10);

	UnkGame111::uc202[1].i12[3] = InGame::guiRx_getBitmap(word_4982C0[Settings::instance.i268_resolution].i8);
	UnkGame111::uc202[2].i12[3] = InGame::guiRx_getBitmap(word_4982C0[Settings::instance.i268_resolution].i8);
	UnkGame111::uc202[3].i12[3] = InGame::guiRx_getBitmap(word_4982C0[Settings::instance.i268_resolution].i8);
	UnkGame111::uc202[4].i12[3] = InGame::guiRx_getBitmap(word_4982C0[Settings::instance.i268_resolution].i8);
	UnkGame111::uc202[5].i12[3] = InGame::guiRx_getBitmap(word_4982C0[Settings::instance.i268_resolution].i0);

	UnkGame111::uc201[1].i0 = InGame::fontMini;
	UnkGame111::uc201[2].i0 = InGame::fontAntiqua;
	UnkGame111::uc201[5].i0 = InGame::fontAntiqua;

	UnkGame111::uc201[0].i0 = InGame::fontGame;
	UnkGame111::uc201[3].i0 = InGame::fontGame;

	UnkGame111::uc201[7].i0 = InGame::fontMetal;

	UnkGame111::uc201[4].i0 = InGame::fontOutline;
	UnkGame111::uc201[6].i0 = InGame::fontGrey;

	UnkGame111::uc201[4].i4 = 1;
	UnkGame111::uc201[6].i4 = 1;
	UnkGame111::uc201[5].i4 = 1;
	UnkGame111::uc201[7].i4 = 1;

	UnkGame111::uc201[3].i16 = palette->getMostSimilarColor(220, 220, 200);
	UnkGame111::uc201[3].i18 = palette->getMostSimilarColor(180, 50, 0);

	for (int i = 0; i < 8; ++i)
		setEntryI4(i, UnkGame111::uc201[i]);

	for (int i = 0; i < 6; ++i)
		setEntryI564(i, UnkGame111::uc202[i]);

	i848->i65 |= 1;

	Rect var1C {
            screenConstants[Settings::instance.i268_resolution].i8 + 31,
            screenConstants[Settings::instance.i268_resolution].i28 + screenConstants[Settings::instance.i268_resolution].height - 20,
		560,
		20
	};

	i898 = new UnkClass670(var1C, 4);
	addControl(i898);
	
	var1C.setBounds(
            screenConstants[Settings::instance.i268_resolution].i8,
            screenConstants[Settings::instance.i268_resolution].i28 + screenConstants[Settings::instance.i268_resolution].height - 48,
		30,
		48
	);

	for (int i = 0; i < 12; ++i) {
		i912[i] = new UnkClass671(var1C, 47 + i, 0);
		addControl(i912[i]);

		var1C.move(0, -var1C.getHeight());
	}

	if (InGame::instance.i130 == 2)
		throw 0; // i916->i25 = 28;
}

UnkGame111::~UnkGame111()
{
	reset();
}

void UnkGame111::vtable0_draw(knights_and_merchants::graphics::DrawableSurface & surface)
{
	if (i886 != 0) {
		Rect var10 { 0, 0, screenConstants[Settings::instance.i268_resolution].width, screenConstants[Settings::instance.i268_resolution].height };
		vtable12(surface, var10);
		i886 = 0;
		i890 = 0;
	} else if (i890 != 0) {
		Rect var10 { 0, 0, 210, 200 };
		vtable12(surface, var10);
		i890 = 0;
	}

    UnkClass200::vtable0_draw(surface);
}

bool UnkGame111::vtable4_handleEvent(unsigned short eventID, int p4, int p8)
{
	knights_and_merchants::io::MouseHandler & mouse = *knights_and_merchants::io::InputHandler::instance->getMouseHandler();
	UnkGame20 & unkGame20 = *UnkGame20::instance;

	if (unkGame20.i18 != 0 && mouse.i64_isLeftButtonDown == 0 && mouse.i68_isRightButtonDown == 0)
		unkGame20.unk3();
			
	switch (p4) {
	case 1:
	case 9:
		if (eventID < 47 || eventID >= 59) {
			switch (eventID) {
			case 1:
				InGame::miniMapMaybe_instance->moveToMouseCoordinates(mouse.i0_position.x, mouse.i0_position.y);
				return true;
			case 2:
				if (unkGame20.i18 != 0) {
					unkGame20.unk7();
				} else {
					for (int i = 0; i < 12; ++i) {
						if (i912[i]->i32 != -1 && (i912[i]->i21_flags & 10) == 10)
							return false;
					}

					unkGame20.unk6(true, false, false);
				}


				return true;
			}
		} else {
			// TODO: reverse
		}

		break;
	case 3:
		break;
	case 5:
		if (eventID != 2)
			return true;

		if (UnkGame20::instance->i14 == 0)
			UnkGame20::instance->unk4();

		return true;
	case 7:
		if (eventID < 18 || eventID > 26) {
			if (UnkGame20::instance->i14 == 0) {
				if (UnkGame20::instance->i18 == 0 && eventID == 2) {
					// TODO: unk111 must be reversed
					InGame::unkClass2000_instance->unk111(knights_and_merchants::io::InputHandler::instance->getMouseHandler());

					for (int i = 0; i < 12; ++i) {
						if (i912[i]->i32 != -1 && (i912[i]->i21_flags & 10) == 10)
							return false;
					}

					auto & mh = *knights_and_merchants::io::InputHandler::instance->getMouseHandler();
					return UnkGame20::instance->unk6(mh.i64_isLeftButtonDown, mh.i68_isRightButtonDown, mh.i72_isMiddleButtonDown);
				}
			} else {
			
			}
		} else {
			if (eventID == 18) {
				if (mouse.i56_cursor != unkGame20.i22_currentCursor) {
					if (unkGame20.i22_currentCursor == nullptr) {
						mouse.setCursor(InGame::someBitmaps[0]);
						unkGame20.unk5(InGame::someBitmaps[0]);
					} else {
						mouse.setCursor(unkGame20.i22_currentCursor);
					}
				}

				return false;
			} else { // 19 - 26
				if (mouse.i56_cursor != InGame::someBitmaps[eventID - 18])
					mouse.setCursor(InGame::someBitmaps[eventID - 18]);
				
				auto tickCount = GetTickCount();
				if (i960 + 50 < tickCount) {
					i960 = tickCount;

					static POINT dword_498278[9] {
						{  0,  0 },
						{ -1,  0 },
						{  1,  0 },
						{  0, -1 },
						{  0,  1 },
						{ -1, -1 },
						{  1, -1 },
						{ -1,  1 },
						{  1,  1 }
					};

					InGame::miniMapMaybe_instance->moveCamera(dword_498278[eventID - 18].x, dword_498278[eventID - 18].y);

					if (Settings::instance.i264_scrolling != 0)
						InGame::miniMapMaybe_instance->moveCamera(dword_498278[eventID - 18].x, dword_498278[eventID - 18].y);
				}

				return false;
			}
		}
		break;
	case 8:
		break;
	}

	return false;
}

void UnkGame111::vtable8_registerForRedraw()
{
	i886 = 1;
    UnkClass200::vtable8_registerForRedraw();
}

void UnkGame111::vtable12(knights_and_merchants::graphics::DrawableSurface & p0, Rect & p4)
{
    knights_and_merchants::graphics::DrawableSurface var1C { p4.getWidth(), p4.getHeight(), p0.i4_pitch, p0.i6_surface + p4.left + p0.i4_pitch * p4.top };

	InGame::guiRx_getBitmap(word_4982C0[Settings::instance.i268_resolution].i4)->draw(var1C, -p4.left, -p4.top);

	if (i904 != 0) {
		InGame::guiRx_getBitmap(word_4982C0[Settings::instance.i268_resolution].i0)->draw(
			var1C,
            screenConstants[Settings::instance.i268_resolution].i8 - p4.left,
            screenConstants[Settings::instance.i268_resolution].i28 + screenConstants[Settings::instance.i268_resolution].height - p4.top - 170
		);
	}

	if (word_4982C0[Settings::instance.i268_resolution].i6 != -1) {
		Rect rect {
                screenConstants[Settings::instance.i268_resolution].i8,
			0,
                screenConstants[Settings::instance.i268_resolution].width - screenConstants[Settings::instance.i268_resolution].i8,
			4 
		};
		p0.fillRectangle(rect, 3);

		rect.setBounds(rect.left, screenConstants[Settings::instance.i268_resolution].height - 4, rect.getWidth(), 4);
		p0.fillRectangle(rect, 3);

		InGame::guiRx_getBitmap(word_4982C0[Settings::instance.i268_resolution].i6)->draw(var1C, -p4.left, 200 - p4.top);
	}

}

bool UnkGame111::handleInput()
{
	if (i872 != i902) {
		i902 = i872;
		i898->unknown1((i872 != -1) ? i872 : 0);
	}

	switch (knights_and_merchants::io::InputHandler::instance->getKeyboardHandler()->unk2()) {
	case DIK_F8:
		if (InGame::instance.i130 != 2)
			InGame::instance.unk8();

		break;
	case DIK_F11:
		InGame::instance.i28 = 1;

		break;
	case DIK_F12:
		if (InGame::instance.i130 != 2) {
			dword_53D584 = true;
			InGame::instance.i33 = 1;
		}

		break;
	}

	if (knights_and_merchants::io::InputHandler::instance->getKeyboardHandler()->isKeyDown(DIK_RIGHT) != 0) {
		InGame::miniMapMaybe_instance->moveCamera(1, 0);

		if (Settings::instance.i264_scrolling != 0)
			InGame::miniMapMaybe_instance->moveCamera(1, 0);
	}

	if (knights_and_merchants::io::InputHandler::instance->getKeyboardHandler()->isKeyDown(DIK_LEFT) != 0) {
		InGame::miniMapMaybe_instance->moveCamera(-1, 0);

		if (Settings::instance.i264_scrolling != 0)
			InGame::miniMapMaybe_instance->moveCamera(-1, 0);
	}

	if (knights_and_merchants::io::InputHandler::instance->getKeyboardHandler()->isKeyDown(DIK_UP) != 0) {
		InGame::miniMapMaybe_instance->moveCamera(0, -1);

		if (Settings::instance.i264_scrolling != 0)
			InGame::miniMapMaybe_instance->moveCamera(0, -1);
	}

	if (knights_and_merchants::io::InputHandler::instance->getKeyboardHandler()->isKeyDown(DIK_DOWN) != 0) {
		InGame::miniMapMaybe_instance->moveCamera(0, 1);

		if (Settings::instance.i264_scrolling != 0)
			InGame::miniMapMaybe_instance->moveCamera(0, 1);
	}
	
	handleEvents(knights_and_merchants::io::InputHandler::instance->getMouseHandler(), knights_and_merchants::io::InputHandler::instance->getKeyboardHandler());
	return i882 == 0;
}

void UnkGame111::unk09()
{
	auto var4 = ArrayBriefings::instance->i12;

	int ebx = 0;
	int i = 0;
	for (; i < 12; ++i) {
		short esi = -1;
		int edi = -1;

		Briefing * b = &ArrayBriefings::instance->getElement(0);

		for (int j = 0; j <= var4; ++j, ++b) {
			if (b->i5 != nullptr && b->i0 <= edi && b->i0 >= ebx) {
				edi = b->i0;
				esi = j;
			}
		}

		if (esi == -1)
			break;

		ebx = ArrayBriefings::instance->getElement(esi).i0 + 1;

		i912[i]->setBriefingID(esi);
	}

	for (; i < 12; ++i)
		i912[i]->setBriefingID(-1);
}

void UnkGame111::reset()
{
	i960 = 0;
	i882 = 0;
	i890 = 0;
	i886 = 1;

	for (int i = 0; i < 8; ++i)
		UnkGame111::uc201[i] = UnkClass201();

	for (int i = 0; i < 6; ++i)
		UnkGame111::uc202[i] = UnkClass202();

	for (int i = 0; i < 12; ++i)
		i912[i] = 0;

	i904 = 0;
	i908 = 0;
	i902 = -1;
	i898 = 0;
}

void UnkGame111::drawMenu(knights_and_merchants::graphics::DrawableSurface & p0)
{
	if (i904 != 0) {
		InGame::guiRx_getBitmap(word_4982C0[Settings::instance.i268_resolution].i2)->draw(
			p0,
            screenConstants[Settings::instance.i268_resolution].i8,
            screenConstants[Settings::instance.i268_resolution].i28 - screenConstants[Settings::instance.i268_resolution].i24 + screenConstants[Settings::instance.i268_resolution].height - 170
		);
	}

	if (InGame::instance.i133 > 1) {
		InGame::guiRx_getBitmap((InGame::instance.i4 & 0xF) + 555)->draw(
			p0,
            screenConstants[Settings::instance.i268_resolution].i8 + 50,
            screenConstants[Settings::instance.i268_resolution].i12 + 50
		);
	}

	drawWhat(p0);
}

void UnkGame111::drawWhat(knights_and_merchants::graphics::DrawableSurface & p0)
{
	for (int i = 0; i < 12; ++i)
		if (i912[i]->i32 != -1)
            i912[i]->vtable4_draw(p0);

    i898->vtable4_draw(p0);
}
