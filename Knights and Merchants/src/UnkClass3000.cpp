#include "UnkClass3000.h"

using knights_and_merchants::utilities::Rect;

UnkClass3000::UnkClass3000(const Rect & position, const unsigned short eventID, const unsigned char keyboardKey)
        : UIElement { position, eventID, 0, -1 }
{
    i25_keyboardKey = keyboardKey;
}
