#ifndef KNIGHTS_AND_MERCHANTS_UI_CONTROLS_BUTTON_H
#define KNIGHTS_AND_MERCHANTS_UI_CONTROLS_BUTTON_H

#include "UIElement.h"

namespace knights_and_merchants::ui::controls
{
    class Button : public UIElement
    {
    public:
        Button(const utilities::Rect & position, unsigned short eventID, const char * text, char p12, unsigned char keyboardKey);

        Button(const utilities::Rect & position, unsigned short eventID, int textID, char p12, unsigned char keyboardKey);

        virtual ~Button() override;

        virtual void vtable4_draw(graphics::DrawableSurface & surface) override;

        void setText(const char * text);

    private:
        void reset();

        char * i32_text;
        short i36;
        short i38;
    };
}

#endif
