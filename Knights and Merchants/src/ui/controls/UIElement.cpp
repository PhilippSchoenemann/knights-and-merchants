#include "graphics/DrawableSurface.h"
#include "ui/controls/UIElement.h"
#include "ui/UnkClass203.h"

using knights_and_merchants::graphics::DrawableSurface;

namespace knights_and_merchants::ui::controls
{
    UIElement::UIElement(const Rect & position, const unsigned short p4, const char p8, const short p12)
        : i4 { p8 }, i5_position { position }, i21_flags { 0x20 }, i23 { p4 }, i25 { 0 }, i26 { p12 }, i28 { nullptr } { }

    void UIElement::registerForDraw()
    {
        if (i28 != nullptr)
            i28->enableDraw(this);
    }

    Rect & UIElement::calculateAbsolutePosition(Rect & absolutePosition) const
    {
        Rect result { i5_position.left, i5_position.top, i5_position.getWidth(), i5_position.getHeight() };
        result.move(i28->i44.left, i28->i44.top);

        absolutePosition = result;
        return absolutePosition;
    }

    UnkClass201 * UIElement::unk1() const
    {
        return (i28 != nullptr) ? i28->getEntryI4(i4) : nullptr;
    }

    UIElement & UIElement::vtable0(const bool free)
    {
        this->~UIElement();

        if (free)
            operator delete(this);

        return *this;
    }

    void UIElement::vtable4(DrawableSurface & surface) { }

    bool UIElement::vtable8(const POINT point) const
    {
        Rect absolutePosition;
        calculateAbsolutePosition(absolutePosition);

        return PtInRect(&absolutePosition, point);
    }

    bool UIElement::vtable12(const int x, const int y)
    {
        return true;
    }

    bool UIElement::isEnabled() const
    {
        return (i21_flags & 4) == 0;
    }

    void UIElement::setEnabled(const bool enabled)
    {
        if (isEnabled() == enabled)
            return;
    
        if (enabled)
            i21_flags &= ~4;
        else
            i21_flags |= 4;

        registerForDraw();    
    }

    DrawableSurface & UIElement::calculateSurface(DrawableSurface & result, const DrawableSurface & source) const
    {
        Rect absolutePosition;
        calculateAbsolutePosition(absolutePosition);

        result.i0_width = absolutePosition.getWidth();
        result.i2_height = absolutePosition.getHeight();
        result.i4_pitch = source.i4_pitch;
        result.i6_surface = source.i6_surface + absolutePosition.left + source.i4_pitch * absolutePosition.top;

        return result;
    }
}
