#ifndef KNIGHTS_AND_MERCHANTS_UI_CONTROLS_IMAGE_BOX_H
#define KNIGHTS_AND_MERCHANTS_UI_CONTROLS_IMAGE_BOX_H

#include "UIElement.h"

namespace knights_and_merchants::engine
{
    class Bitmap;
}

using knights_and_merchants::engine::Bitmap;

class UnkClass203;

namespace knights_and_merchants::ui::controls
{
    class ImageBox : public UIElement
    {
    public:
        ImageBox(const utilities::Rect & rect, const Bitmap * p4);
        virtual ~ImageBox() override;

        virtual void vtable4(engine::DrawableSurface & p0) override;

        void setImage(const Bitmap * image);
        const Bitmap * i32;
    };
}

#endif
