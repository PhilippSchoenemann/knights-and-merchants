#pragma once

#include "UIElement.h"

namespace knights_and_merchants::utilities
{
    class Rect;
}

namespace knights_and_merchants::engine
{
    class Bitmap;
}

using knights_and_merchants::utilities::Rect;
using knights_and_merchants::engine::Bitmap;

namespace knights_and_merchants::ui::controls
{
    class UnkClass674 : public UIElement
    {
    public:
        UnkClass674(const Rect & p0, Bitmap * p4, unsigned char * p8, char p12);
        virtual ~UnkClass674();

        virtual void vtable4(engine::DrawableSurface & p0) override;

        Bitmap * i32;
        unsigned char * i36;
        char i40;
    };
}
