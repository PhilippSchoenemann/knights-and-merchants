#ifndef KNIGHTS_AND_MERCHANTS_UNK_CLASS_200_H
#define KNIGHTS_AND_MERCHANTS_UNK_CLASS_200_H

#include "UnkClass201.h"
#include "UnkClass202.h"
#include "utilities/Rect.h"

namespace knights_and_merchants::io
{
    class KeyboardHandler;

    class MouseHandler;
}

class UnkClass203;

namespace knights_and_merchants::ui::controls
{
    class UIElement;
}

namespace knights_and_merchants::graphics
{
    class DrawableSurface;
}

class UnkClass200
{
public:
    explicit UnkClass200(knights_and_merchants::utilities::Rect rect);

    virtual ~UnkClass200();

    virtual void vtable0(knights_and_merchants::graphics::DrawableSurface & surface);

    virtual bool vtable4(unsigned short p0, int p4, int p8);

    virtual void vtable8();

    virtual void vtable12(knights_and_merchants::graphics::DrawableSurface & surface, knights_and_merchants::utilities::Rect & p4);

    void reset();

    void destroy();

    UnkClass201 * getEntryI4(const int i);

    UnkClass202 * getEntryI564(const int i);

    bool setEntryI4(const int i, const UnkClass201 & entry);

    bool setEntryI564(const int i, const UnkClass202 & entry);

    void addControl(knights_and_merchants::ui::controls::UIElement * control) const;

    void addContainer(UnkClass203 * container) const;


    void setI872(short p0) { i872 = p0; }

    void handleEvents(knights_and_merchants::io::MouseHandler * p0, knights_and_merchants::io::KeyboardHandler * p4);


    UnkClass201 i4[20];
    UnkClass202 i564[10];
    int i844;
    UnkClass203 * i848;
    UnkClass203 * i852;
    knights_and_merchants::utilities::Rect i856;
    short i872;
    knights_and_merchants::ui::controls::UIElement * i874;
    UnkClass203 * i878;

};

#endif