#pragma once

#include "UIElement.h"

namespace knights_and_merchants::ui::controls
{
    class UnkClass672 : public UIElement
    {
    public:
        UnkClass672(const utilities::Rect & position, int p4, char * p8);
        virtual ~UnkClass672();

        virtual void vtable4(graphics::DrawableSurface & p0) override;

        void reset();
        bool updateScroll();

        char * i32;
        char * i36;
        int i40;
        int i44;
    };
}
