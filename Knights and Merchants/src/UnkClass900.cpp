#include "UnkClass900.h"
#include "graphics/Bitmap.h"
#include "UnkClass700.h"
#include "InGame.h"
#include "UnkClass800.h"
#include "Map.h"
#include "UnitManager.h"
#include "Unit.h"
#include "engine/GraphicsHandler.h"
#include "graphics/DrawableSurface.h"
#include "ui/UnkClass202.h"
#include "graphics/Bitmap.h"
UnkClass900::UnkClass900(const Rect & p0, char p4)
	: UnkClass203 { p0, 2 }, i67 { p4 }
{
	unk1(0, 0);
}

UnkClass900::~UnkClass900()
{
}

void UnkClass900::vtable8(knights_and_merchants::graphics::DrawableSurface & p0, const Rect & p4)
{
	Rect rect { p4 };

	rect.move(i44.left, i44.top);

    knights_and_merchants::graphics::DrawableSurface var1C { p0 };
	
	var1C.i0_width = rect.getWidth();
	var1C.i2_height = rect.getHeight();
	var1C.i6_surface = p0.i6_surface + rect.left + p0.i4_pitch * rect.top;

	getEntryI564(i64)->i12[3]->draw(var1C, -p4.left, -p4.top);
}

void UnkClass900::vtable12(knights_and_merchants::graphics::DrawableSurface & p0)
{
	getEntryI564(i64)->i12[3]->draw(p0, i44.left, i44.top);
}

void UnkClass900::vtable16()
{
	// TODO: reverse this later
	switch (i68 - 1) {
	
	}
}

bool UnkClass900::vtable20(short p0, int p4, int p8)
{
	switch (p4) {
	case 1:
	case 9:

		switch (p0) {
		case 67:
			unk1(15, 0);
			return true;
		}

		break;
	case 3:
		break;
	}

	return false;
}

void UnkClass900::unk1(int p0, int p4)
{
	Rect rect { 9, 60, 180, 30 };

	auto bl = i68;
	i68 = p0;

	unk2();

	if (i68 <= 8)
		createMenu();

	switch (i68 - 1) {
	case 14:
		createTitle(170);
		createBackButton();
		break;
	}

	enableDrawAllChilds();
}

void UnkClass900::unk2()
{
	destroyControls();

	for (int i = 0; i < 206; ++i)
		i73[i] = 0;
}

void UnkClass900::createMenu()
{
	Rect rect { 9, 4, 42, 36 };
	i73[0] = new UnkClass700(rect, 60, InGame::guiRx_getBitmap(438), 1, 160, 2);
	addControl(i73[0]);

	rect.move(rect.getWidth() + 3, 0);
	i73[1] = new UnkClass700(rect, 61, InGame::guiRx_getBitmap(439), 1, 161, 3);
	addControl(i73[1]);

	rect.move(rect.getWidth() + 3, 0);
	i73[2] = new UnkClass700(rect, 65, InGame::guiRx_getBitmap(440), 1, 162, 4);
	addControl(i73[2]);

	rect.move(rect.getWidth() + 3, 0);
	i73[4] = new UnkClass700(rect, 67, InGame::guiRx_getBitmap(441), 1, 164, 5);
	addControl(i73[4]);

	if ((InGame::instance.i20 & 0xFF0000) != 0) { // TODO: Make isTactic cleaner
		i73[0]->setEnabled(false);
		i73[1]->setEnabled(false);
		i73[2]->setEnabled(false);
	}


}

void UnkClass900::createBackButton()
{
	Rect rect { 9, 4, 42, 36 };

	i73[5] = new UnkClass700(rect, 68, InGame::guiRx_getBitmap(442), 2, 165, 1);
	addControl(i73[5]);
}

void UnkClass900::createTitle(int p0)
{
	Rect rect { 57, 8, 128, 36 };

	i73[6] = new UnkClass800(rect, InGame::getTextLibString(p0).c_str(), 7, 1);
	addControl(i73[6]);

}

void UnkClass900::createBuildingSelectionMenu()
{
	throw 0;
}

short UnkClass900::getSelectedGroupID()
{
	if (i68 < 3 || i68 > 8)
		return -1;

	if (i897 == -1)
		return 0;

	const Unit & unit = Map::unitManager->getElement(i897);

	if ((int)unit.i0_type < 14 || (int)unit.i0_type > 29) // TODO: Make enum better
		return -1;

	return unit.i47_groupId;
}
