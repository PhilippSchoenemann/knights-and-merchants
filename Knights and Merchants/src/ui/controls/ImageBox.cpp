#include "ui/controls/ImageBox.h"
#include "ui/UnkClass203.h"
#include "ui/UnkClass200.h"
#include "graphics/Bitmap.h"

using knights_and_merchants::utilities::Rect;
using knights_and_merchants::graphics::Bitmap;

namespace knights_and_merchants::ui::controls
{
    ImageBox::ImageBox(const Rect & position, const Bitmap * image)
            : UIElement { position, 0, 0, -1 }
    {
        i21_flags |= 0x40;
        i32_image = image;
    }

    ImageBox::~ImageBox()
    {

    }

    void ImageBox::vtable4(graphics::DrawableSurface & surface)
    {
        Rect absolutePosition;
        calculateAbsolutePosition(absolutePosition);

        i28_container->getBase()->vtable12(surface, i5_position);

        if ((i21_flags & 0x4) == 0 && i32_image != nullptr)
            i32_image->draw(surface, absolutePosition.left, absolutePosition.top);
    }

    void ImageBox::setImage(const Bitmap * image)
    {
        i32_image = image;
        registerForDraw();
    }
}