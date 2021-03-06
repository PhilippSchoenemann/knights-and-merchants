#include "ui/controls/UnkClass674.h"
#include "ui/UnkClass203.h"
#include "graphics/Bitmap.h"

namespace knights_and_merchants::ui::controls
{
    UnkClass674::UnkClass674(const Rect & position, graphics::Bitmap * p4, unsigned char * p8, char p12)
            : UIElement { position, 0, 0, -1 }
    {
        i21_flags |= 0x40;
        i40 = p12;
        i32 = p4;
        i36 = p8;
    }

    void UnkClass674::vtable4_draw(graphics::DrawableSurface & surface)
    {
        Rect rect;
        calculateAbsolutePosition(rect);

        if ((i40 & 0x80) == 0)
            i28_container->vtable8(surface, i5_position);

        if ((i21_flags & 4) == 0 && i32 != nullptr) {

            if ((i40 & 0x1F) != 1) {
                if ((i40 & 0x1F) != 2) {
                    i32->drawRemapped(surface, rect.left, rect.top, i36);
                } else {
                    i32->drawResized(surface, rect.left, rect.top, abs(rect.right - rect.left), abs(rect.bottom - rect.top));
                }
            } else {
                i32->drawRemapped(surface, rect.left + abs(rect.right - rect.left) / 2, rect.top + abs(rect.bottom - rect.top) / 2, i36);
            }
        }
    }
}