#include "ui/UnkClass200.h"
#include "ui/UnkClass203.h"
#include "ui/controls/UIElement.h"
#include "io/MouseHandler.h"
#include "io/KeyboardHandler.h"

using knights_and_merchants::io::MouseHandler;
using knights_and_merchants::io::KeyboardHandler;
using knights_and_merchants::ui::controls::UIElement;
using knights_and_merchants::graphics::DrawableSurface;
using knights_and_merchants::utilities::Rect;

UnkClass200::UnkClass200(const Rect rect)
        : i856 { rect }
{
    reset();

    i848 = new UnkClass203(rect, 0);
    i848->i8_base = this;

    i852 = i848;
}

UnkClass200::~UnkClass200()
{
    destroy();
    reset();
}

void UnkClass200::reset()
{
    i844 = 0;
    i848 = nullptr;
    i852 = nullptr;
    i874 = nullptr;
    i878 = nullptr;
    i872 = -1;

    for (auto & e: i4)
        e = UnkClass201();

    for (auto & e: i564)
        e = UnkClass202();
}

void UnkClass200::destroy()
{
    if (i848 != nullptr) {
        i848->destroyContainers();
        i848->vtable0(true);
    }

    i848 = nullptr;
    i852 = nullptr;
}

UnkClass201 * UnkClass200::getEntryI4(const int i)
{
    return i < 20 ? &i4[i] : nullptr;
}

UnkClass202 * UnkClass200::getEntryI564(const int i)
{
    return i < 10 ? &i564[i] : nullptr;
}

void UnkClass200::addControl(UIElement * control) const
{
    i848->addControl(control);
}

void UnkClass200::addContainer(UnkClass203 * container) const
{
    i848->addContainer(container);
}

bool UnkClass200::setEntryI4(const int i, const UnkClass201 & entry)
{
    return i < 20 && (i4[i] = entry, true);
}

bool UnkClass200::setEntryI564(const int i, const UnkClass202 & entry)
{
    return i < 10 && (i564[i] = entry, true);
}

void UnkClass200::handleEvents(MouseHandler * mouseHandler, KeyboardHandler * keyboardHandler)
{
    setI872(-1);

    if (i878 != nullptr) {
        if (i878->handleEvents(mouseHandler, keyboardHandler))
            return;

        keyboardHandler = nullptr;
    }

    i848->handleEvents(mouseHandler, keyboardHandler);
}

void UnkClass200::vtable0(DrawableSurface & surface)
{
    i848->vtable4(surface);
}

bool UnkClass200::vtable4(unsigned short p0, int p4, int p8)
{
    return true;
}

void UnkClass200::vtable8()
{
    i848->enableDrawAllChilds();
}

void UnkClass200::vtable12(DrawableSurface & surface, Rect & p4)
{

}