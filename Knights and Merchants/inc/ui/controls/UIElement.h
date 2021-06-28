#ifndef KNIGHTS_AND_MERCHANTS_UI_ELEMENT_H
#define KNIGHTS_AND_MERCHANTS_UI_ELEMENT_H

#include <Windows.h>

#include "utilities/Rect.h"

class UnkClass201;
class UnkClass203;

namespace knights_and_merchants::engine
{
    struct DrawableSurface;
}

using knights_and_merchants::engine::DrawableSurface;
using knights_and_merchants::utilities::Rect;

namespace knights_and_merchants::ui::controls
{
    class UIElement
    {
    public:
        UIElement(const Rect & p0, short p4, char p8, short p12);
        virtual ~UIElement() = default;

        virtual UIElement & vtable0(bool free);

        virtual void vtable4(DrawableSurface & surface);

        [[nodiscard]]
        virtual bool vtable8(POINT point) const;

        virtual bool vtable12(int x, int y);

        bool isEnabled() const;
        void setEnabled(bool enabled);

        Rect & calculateAbsolutePosition(Rect & absolutePosition) const;

        void registerForDraw();

        UnkClass201 * unk1() const;
        DrawableSurface & calculateSurface(DrawableSurface & result, const DrawableSurface & source) const;

        char i4;
        Rect i5;
        short i21;
        short i23;
        char i25;
        short i26;
        UnkClass203 * i28;
    };
}

#endif
