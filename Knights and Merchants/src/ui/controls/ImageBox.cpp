#include "ui/controls/ImageBox.h"
#include "ui/UnkClass203.h"
#include "ui/UnkClass200.h"
#include "engine/Bitmap.h"

using knights_and_merchants::utilities::Rect;

namespace knights_and_merchants::ui::controls
{
ImageBox::ImageBox(const Rect & rect, const Bitmap * p4)
	: UIElement { rect, 0, 0, -1 }
{
	i21_flags |= 0x40;
	i32 = p4;
}

ImageBox::~ImageBox()
{

}

void ImageBox::vtable4(engine::DrawableSurface & p0)
{
	Rect rect;
	calculateAbsolutePosition(rect);

	i28->getBase()->vtable12(p0, i5_position);

	if ((i21_flags & 0x4) == 0 && i32 != nullptr)
		i32->draw(p0, rect.left, rect.top);
}

void ImageBox::setImage(const Bitmap * image)
{
	i32 = image;
	registerForDraw();
}
}