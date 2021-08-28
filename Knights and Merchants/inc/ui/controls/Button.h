#ifndef KNIGHTS_AND_MERCHANTS_UI_CONTROLS_BUTTON_H
#define KNIGHTS_AND_MERCHANTS_UI_CONTROLS_BUTTON_H

#include "UIElement.h"

namespace knights_and_merchants::ui::controls
{
    class Button : public UIElement
    {
    public:
        Button(const utilities::Rect & p0, short p4, const char * p8, char p12, int p16);
        Button(const utilities::Rect & p0, short p4, int p8, char p12, int p16);

        virtual ~Button() override;

        virtual void vtable4(engine::DrawableSurface & p0) override;

        void setText(const char * p0);

    private:
        void reset();

        char * i32;
        short i36;
        short i38;
    };
}

#endif
