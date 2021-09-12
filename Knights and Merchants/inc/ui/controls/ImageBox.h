#ifndef KNIGHTS_AND_MERCHANTS_UI_CONTROLS_IMAGE_BOX_H
#define KNIGHTS_AND_MERCHANTS_UI_CONTROLS_IMAGE_BOX_H

#include "UIElement.h"

namespace knights_and_merchants::graphics
{
    class Bitmap;
}

class UnkClass203;

namespace knights_and_merchants::ui::controls
{
    class ImageBox : public UIElement
    {
    public:
        ImageBox(const utilities::Rect & rect, const knights_and_merchants::graphics::Bitmap * p4);
        virtual ~ImageBox() override;

        virtual void vtable4(graphics::DrawableSurface & p0) override;

        void setImage(const knights_and_merchants::graphics::Bitmap * image);
        const knights_and_merchants::graphics::Bitmap * i32;
    };
}

#endif
