#pragma once

#include "UIElement.h"

namespace knights_and_merchants::ui::controls
{
    class UnkClass672 : public UIElement
    {
    public:
        UnkClass672(const utilities::Rect & p0, int p4, char * p8);
        virtual ~UnkClass672();

        virtual void vtable4(engine::DrawableSurface & p0) override;

        void reset();
        bool updateScroll();

        char * i32;
        char * i36;
        int i40;
        int i44;
    };
}
