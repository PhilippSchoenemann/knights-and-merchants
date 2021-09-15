#ifndef KNIGHTS_AND_MERCHANTS_UI_CONTROLS_SCROLL_TEXT_BOX_H
#define KNIGHTS_AND_MERCHANTS_UI_CONTROLS_SCROLL_TEXT_BOX_H

#include "UIElement.h"

namespace knights_and_merchants::ui::controls
{
    class ScrollTextBox : public UIElement //Prev=UnkClass672
    {
    public:
        ScrollTextBox(const utilities::Rect & position, int p4, char * p8);

        virtual ~ScrollTextBox();

        virtual void vtable4_draw(graphics::DrawableSurface & p0) override;

        void reset();

        bool updateScroll();

        char * i32;
        char * i36;
        int i40;
        int i44;
    };
}

#endif