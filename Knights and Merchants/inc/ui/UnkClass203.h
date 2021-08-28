#pragma once

#include "utilities/DoublyLinkedList.h"
#include "utilities/Rect.h"

namespace knights_and_merchants {
    namespace io {
        class KeyboardHandler;
        class MouseHandler;
    }
}

class UnkClass201;

namespace knights_and_merchants {
    namespace ui {
        namespace controls {
            class UIElement;
        }
    }
}

namespace knights_and_merchants {
    namespace engine {
        class DrawableSurface;
    }
}

using knights_and_merchants::utilities::DoublyLinkedList;
using knights_and_merchants::utilities::Rect;

class UnkClass200;
class UnkClass202;

class UnkClass203 {
public:
	UnkClass203(const Rect position, const char p4);
	virtual ~UnkClass203();

	virtual void vtable0(const bool free);
	virtual void vtable4(knights_and_merchants::engine::DrawableSurface & surface);
	virtual void vtable8(knights_and_merchants::engine::DrawableSurface & surface, const Rect & relativePosition);
	virtual void vtable12(knights_and_merchants::engine::DrawableSurface & surface);
	virtual void vtable16();
	virtual bool vtable20(short p0, int p4, int p8);

	void reset();

	void destroyContainers();
	void destroyControls();

	bool addContainer(UnkClass203 * container);
	bool addContainerRaw(UnkClass203 * container);

	bool addControl(knights_and_merchants::ui::controls::UIElement * control);
	bool addControlRaw(knights_and_merchants::ui::controls::UIElement * control);

	void enableDraw(knights_and_merchants::ui::controls::UIElement * control);
	void enableDrawAllChilds();

	UnkClass200 * getBase() const;

	UnkClass202 * getEntryI564(const int i) const;

	UnkClass201 * getEntryI4(const int i) const;

	bool handleEvents(knights_and_merchants::io::MouseHandler * p0, knights_and_merchants::io::KeyboardHandler * p4);



	UnkClass203 * i4_parent;
	UnkClass200 * i8_base;
	DoublyLinkedList<UnkClass203> i12_containers;
	DoublyLinkedList<knights_and_merchants::ui::controls::UIElement> i24_controls;
	int i36;
	bool i40;
	Rect i44;
	int i60;
	char i64;
	short i65;
};

