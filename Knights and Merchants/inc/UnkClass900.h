#ifndef KNIGHTS_AND_MERCHANTS_UNK_CLASS_900_H
#define KNIGHTS_AND_MERCHANTS_UNK_CLASS_900_H

#include "ui/UnkClass203.h"

class UnkClass900 : public UnkClass203 {
public:
	UnkClass900(const Rect & p0, char p4);
	virtual ~UnkClass900();

	virtual void vtable8(knights_and_merchants::graphics::DrawableSurface & p0, const Rect & p4) override;
	virtual void vtable12(knights_and_merchants::graphics::DrawableSurface & p0) override;
	virtual void vtable16() override;
	virtual bool vtable20(short p0, int p4, int p8) override;

	void unk1(int p0, int p4);
	void unk2();
	void createMenu();
	void createBackButton();
	void createTitle(int p0);
	void createBuildingSelectionMenu();

	short getSelectedGroupID();

	char i67;
	char i68;
	knights_and_merchants::ui::controls::UIElement * i73[206];
	short i897;
};

#endif