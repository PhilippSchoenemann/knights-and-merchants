#pragma once
#include "UnkClass201.h"
#include "UnkClass202.h"
#include "utilities/Rect.h"

namespace knights_and_merchants {
    namespace io {
        class KeyboardHandler;
        class MouseHandler;
    }
}

class UnkClass203;

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

using knights_and_merchants::utilities::Rect;

class UnkClass200 {
public:
	explicit UnkClass200(const Rect rect);
	virtual ~UnkClass200();

	virtual void vtable0(knights_and_merchants::engine::DrawableSurface & surface);
	virtual bool vtable4(short p0, int p4, int p8);
	virtual void vtable8();
	virtual void vtable12(knights_and_merchants::engine::DrawableSurface & surface, Rect & p4);

	void reset();
	void destroy();

	UnkClass201 * getEntryI4(const int i);
	UnkClass202 * getEntryI564(const int i);

	bool setEntryI4(const int i, const UnkClass201 & entry);
	bool setEntryI564(const int i, const UnkClass202 & entry);

	void addControl(knights_and_merchants::ui::controls::UIElement * control);
	void addContainer(UnkClass203 * container);


	void setI872(short p0) { i872 = p0; }

	void handleEvents(knights_and_merchants::io::MouseHandler * p0, knights_and_merchants::io::KeyboardHandler * p4);



	UnkClass201 i4[20];
	UnkClass202 i564[10];
	int i844;
	UnkClass203 * i848;
	UnkClass203 * i852;
	Rect i856;
	short i872;
    knights_and_merchants::ui::controls::UIElement * i874;
	UnkClass203 * i878;
	
};

