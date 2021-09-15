#include "ui/controls/TextBox.h"
#include <cstring>
#include <cstdio>
#include "ui/UnkClass203.h"
#include "ui/UnkClass201.h"
#include "ui/UnkClass200.h"
#include "graphics/Font.h"
#include "engine/GraphicsHandler.h"
#include "graphics/DrawableSurface.h"

using knights_and_merchants::graphics::DrawableSurface;

namespace knights_and_merchants::ui::controls
{
    TextBox::TextBox(const Rect & position, const char * text, char p8, int p12, int p16)
            : UIElement { position, 0, p8, -1 }
    {
        reset();

        i21_flags |= 0x40;
        i36 = p16;

        setText(text);

        i37 = p12;
    }

    TextBox::~TextBox()
    {
        if (i32_text != nullptr)
            free(i32_text);

        reset();
    }

    void TextBox::setText(const char * p0)
    {
        if (i32_text != nullptr) {
            free(i32_text);
            i32_text = nullptr;
        }

        if (p0 != nullptr) {
            i32_text = (char *) malloc(strlen(p0) + 1);

            if (i32_text != nullptr)
                strcpy(i32_text, p0);
        }

        registerForDraw();
    }

    void TextBox::vtable4(DrawableSurface & p0)
    {
        Rect rect1;
        calculateAbsolutePosition(rect1);

        i28_container->getBase()->vtable12(p0, rect1);

        if (i37 != 0)
            p0.remapRectangle(rect1, i47);

        auto var34 = UIElement::unk1();
        if (var34 != nullptr && i32_text != nullptr) {

            DrawableSurface var2C;
            calculateSurface(var2C, p0);

            auto var30 = var34->i16;

            auto textWidth = var34->i0->calculateTextWidth(i32_text, 0, 0);
            int ebp = 0;
            int eax = 0;

            switch (i36) {
            default: {
                if (textWidth < rect1.getWidth()) {
                    auto ehm = rect1.right - textWidth - rect1.left;

                    if (ehm < 0)
                        ++ehm;

                    ebp = ehm / 2;
                }
            }
            case 0: {
                auto ahh = rect1.bottom - var34->i0->i2_height - rect1.top;

                if (ahh < 0)
                    ++ahh;

                eax = ahh / 2;
            }
                goto l14;
            case 3:
                ebp = 5;
                eax = 5;
            case 1:
            case 4:
            l14:
                break;
            }

            if (i4 == 1) {
                eax += 2;
                ebp += 2;
            }

            if (var34->i4 == 0) {
                var34->i0->drawStringEx(var2C, ebp, eax, i32_text, var30, var34->i18, 0);
            } else {
                var34->i0->drawString(var2C, ebp, eax, i32_text);
            }

            if (i41 != 0) {
                if (i45 > 0 && i45 <= strlen(i32_text)) {
                    auto var30 = (char *) malloc(i45 + 1);

                    if (var30 != nullptr) {
                        strncpy(var30, i32_text, i45);
                        var30[i45] = '\0';

                        ebp += var34->i0->calculateTextWidth(var30, 0, 0);
                        free(var30);
                    }
                }

                auto esi = var34->i0->someUnk(i45 >= strlen(i32_text) ? ' ' : i32_text[i45]);
                if (esi > 0) {
                    rect1.move(ebp, 0);
                    rect1.setSize(esi, abs(rect1.bottom - rect1.top));

                    p0.remapRectangle(rect1, i51);
                }


            }
        }

    }

    void TextBox::reset()
    {
        i32_text = nullptr;
        i41 = 0;
        i45 = 0;
        i47 = nullptr;
        i51 = nullptr;
    }

    void TextBox::unknew(short p0)
    {
        if (i41 == 0 || i45 != p0) {
            i41 = 1;
            i45 = p0;
            registerForDraw();
        }
    }
}