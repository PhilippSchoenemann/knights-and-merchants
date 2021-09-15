#ifndef KNIGHTS_AND_MERCHANTS_UI_CONTROLS_IMAGE_BOX_H
#define KNIGHTS_AND_MERCHANTS_UI_CONTROLS_IMAGE_BOX_H

#include "UIElement.h"

namespace knights_and_merchants::graphics
{
    class Bitmap;
}

namespace knights_and_merchants::ui::controls
{
    class ImageBox : public UIElement
    {
    public:
        ImageBox(const utilities::Rect & position, const knights_and_merchants::graphics::Bitmap * image);

        virtual void vtable4_draw(graphics::DrawableSurface & surface) override;

        void setImage(const knights_and_merchants::graphics::Bitmap * image);

        const knights_and_merchants::graphics::Bitmap * i32_image;
    };
}

#endif
