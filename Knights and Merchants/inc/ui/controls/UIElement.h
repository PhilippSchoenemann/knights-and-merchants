#ifndef KNIGHTS_AND_MERCHANTS_UI_ELEMENT_H
#define KNIGHTS_AND_MERCHANTS_UI_ELEMENT_H

#include <Windows.h>
#include "utilities/Rect.h"

class UnkClass201;
class UnkClass203;

namespace knights_and_merchants::graphics
{
    class DrawableSurface;
}

namespace knights_and_merchants::ui::controls
{
    class UIElement
    {
    protected:
        typedef graphics::DrawableSurface DrawableSurface;
        typedef utilities::Rect Rect;

    public:
        UIElement(const Rect & position, short p4, char p8, short p12);

        UIElement(const UIElement & other) = default;
        UIElement(UIElement && other) = default;

        UIElement & operator=(const UIElement & other) = default;
        UIElement & operator=(UIElement && other) = default;

        virtual ~UIElement() = default;

        virtual UIElement & vtable0(bool free);
        virtual void vtable4(DrawableSurface & surface);
        virtual bool vtable8(POINT point) const;
        virtual bool vtable12(int x, int y);

        bool isEnabled() const;
        void setEnabled(bool enabled);

        utilities::Rect & calculateAbsolutePosition(Rect & absolutePosition) const;

        void registerForDraw();

        UnkClass201 * unk1() const;
        DrawableSurface & calculateSurface(DrawableSurface & result, const DrawableSurface & source) const;

        char i4;
        Rect i5_position;
        short i21_flags;
        short i23;
        char i25;
        short i26;
        UnkClass203 * i28;
    };
}

#endif
