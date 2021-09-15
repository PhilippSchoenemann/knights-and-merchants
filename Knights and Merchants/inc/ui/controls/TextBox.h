#ifndef KNIGHTS_AND_MERCHANTS_UI_CONTROLS_TEXT_BOX_H
#define KNIGHTS_AND_MERCHANTS_UI_CONTROLS_TEXT_BOX_H

#include "UIElement.h"

namespace knights_and_merchants::ui::controls
{
    class TextBox : public UIElement
    {
    public:
        TextBox(const utilities::Rect & position, const char * text, char p8, int p12, int p16);

        virtual ~TextBox() override;

        virtual void vtable4(graphics::DrawableSurface & p0) override;

        void setText(const char * p0);

        void unknew(short p0);

        char * i32_text;
        char i36;
        int i37;
        int i41;
        short i45;
        unsigned char * i47;
        unsigned char * i51;

    private:
        void reset();
    };
}

#endif
