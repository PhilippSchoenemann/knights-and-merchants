#include "UnkClass3000.h"

using knights_and_merchants::utilities::Rect;

UnkClass3000::UnkClass3000(const Rect & position, const unsigned short p4, const unsigned char p8)
        : UIElement { position, p4, 0, -1 }
{
    i25 = p8;
}
