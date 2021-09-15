#pragma once

#include "UIElement.h"

namespace knights_and_merchants::utilities
{
    class Rect;
}

namespace knights_and_merchants::graphics
{
    class Bitmap;
}

namespace knights_and_merchants::ui::controls
{
    class UnkClass674 : public UIElement
    {
    public:
        UnkClass674(const knights_and_merchants::utilities::Rect & position, knights_and_merchants::graphics::Bitmap * p4, unsigned char * p8, char p12);

        virtual void vtable4_draw(graphics::DrawableSurface & surface) override;

        knights_and_merchants::graphics::Bitmap * i32;
        unsigned char * i36;
        char i40;
    };
}
