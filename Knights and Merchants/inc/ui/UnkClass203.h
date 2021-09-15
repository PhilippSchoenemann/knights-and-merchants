#ifndef KNIGHTS_AND_MERCHANTS_UNK_CLASS_203_H
#define KNIGHTS_AND_MERCHANTS_UNK_CLASS_203_H

#include "utilities/DoublyLinkedList.h"
#include "utilities/Rect.h"

namespace knights_and_merchants::io
{
    class KeyboardHandler;

    class MouseHandler;
}

class UnkClass201;

namespace knights_and_merchants::ui::controls
{
    class UIElement;
}

namespace knights_and_merchants::graphics
{
    class DrawableSurface;
}

class UnkClass200;

class UnkClass202;

class UnkClass203
{
public:
    UnkClass203(knights_and_merchants::utilities::Rect position, char p4);

    virtual ~UnkClass203();

    virtual void vtable0(bool free);

    virtual void vtable4(knights_and_merchants::graphics::DrawableSurface & surface);

    virtual void vtable8(knights_and_merchants::graphics::DrawableSurface & surface, const knights_and_merchants::utilities::Rect & relativePosition);

    virtual void vtable12(knights_and_merchants::graphics::DrawableSurface & surface);

    virtual void vtable16();

    virtual bool vtable20(unsigned short p0, int p4, int p8);

    void reset();

    void destroyContainers();

    void destroyControls();

    bool addContainer(UnkClass203 * container);

    bool addContainerRaw(UnkClass203 * container);

    bool addControl(knights_and_merchants::ui::controls::UIElement * control);

    bool addControlRaw(knights_and_merchants::ui::controls::UIElement * control);

    void enableDraw(knights_and_merchants::ui::controls::UIElement * control);

    void enableDrawAllChilds();

    UnkClass200 * getBase() const;

    UnkClass202 * getEntryI564(const int i) const;

    UnkClass201 * getEntryI4(const int i) const;

    bool handleEvents(knights_and_merchants::io::MouseHandler * p0, knights_and_merchants::io::KeyboardHandler * p4);


    UnkClass203 * i4_parent;
    UnkClass200 * i8_base;
    knights_and_merchants::utilities::DoublyLinkedList<UnkClass203> i12_containers;
    knights_and_merchants::utilities::DoublyLinkedList<knights_and_merchants::ui::controls::UIElement> i24_controls;
    int i36;
    bool i40;
    knights_and_merchants::utilities::Rect i44;
    int i60;
    char i64;
    short i65;
};

#endif