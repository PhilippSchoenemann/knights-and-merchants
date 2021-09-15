#ifndef KNIGHTS_AND_MERCHANTS_UNK_CLASS_670_H
#define KNIGHTS_AND_MERCHANTS_UNK_CLASS_670_H

#include "ui/controls/UIElement.h"

class UnkClass670 : public knights_and_merchants::ui::controls::UIElement
{
public:
    UnkClass670(const Rect & rect, const int p4);

    virtual ~UnkClass670();

    virtual void vtable4_draw(DrawableSurface & p0) override;

    void reset();

    void unknown1(short p0);

    short i32;
};

#endif