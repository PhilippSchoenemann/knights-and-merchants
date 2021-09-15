#include "ui/UnknownUICon.h"
#include "ui/controls/TextBox.h"
#include "UnkClass3000.h"
#include <cstdlib>

 using knights_and_merchants::utilities::Rect;
 using knights_and_merchants::ui::controls::TextBox;

 unsigned char UnknownUICon::unk_49ADB8[48] = {
        0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x2B, 0x35, 0x0D, 0x10, 0x11,
        0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25,
        0x26, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33, 0x34, 0x27, 0x28, 0x1A, 0x1B, 0x29, 0x39
};

UnknownUICon::UnknownUICon(knights_and_merchants::utilities::Rect & p0, char p16, int p20, int p24, unsigned char * p28, unsigned char * p32)
    : UnkClass203 { p0, p16 }
{
    Rect rect { };
    reset();

    rect.setBounds(0, 0, rect.getWidth(), rect.getHeight());

    i75 = new TextBox { rect, "0", p16, 1, 0 }; // TODO: Second param is unk string ref. Change later.
    addControl(i75);

    i75->i47 = p28;
    i75->i51 = p32;

    i71 = p20;
    i79 = p24;

    rect.setBounds(2000, 2000, 10, 10);

    for (int i = 0; i < 48; ++i) {
        auto * edi = new UnkClass3000 { rect, static_cast<unsigned short>(50000 + i), unk_49ADB8[i] };
        addControl(edi);

        edi->i21_flags |= 0x7000;
    }

    addControl(new UnkClass3000(rect, 50100, 28));

    auto * edi =  new UnkClass3000(rect, 50101, 14);
    addControl(edi);
    edi->i21_flags |= 0x7000;

    edi =  new UnkClass3000(rect, 50102, 1);
    addControl(edi);
    edi->i21_flags |= 0x7000;

    edi =  new UnkClass3000(rect, 50103, 210);
    addControl(edi);
    edi->i21_flags |= 0x7000;

    edi =  new UnkClass3000(rect, 50104, 211);
    addControl(edi);
    edi->i21_flags |= 0x7000;

    edi =  new UnkClass3000(rect, 50106, 205);
    addControl(edi);
    edi->i21_flags |= 0x7000;

    edi =  new UnkClass3000(rect, 50105, 203);
    addControl(edi);
    edi->i21_flags |= 0x7000;

    edi =  new UnkClass3000(rect, 50107, 199);
    addControl(edi);
    edi->i21_flags |= 0x7000;

    edi =  new UnkClass3000(rect, 50108, 207);
    addControl(edi);
    edi->i21_flags |= 0x7000;

    edi =  new UnkClass3000(rect, 50109, 200);
    addControl(edi);
    edi->i21_flags |= 0x7000;

    i67 = static_cast<char*>(malloc(i71));
    i67[0] = '\0';
}


void UnknownUICon::reset() {
    i67 = 0;
    i73 = 0;
    i71 = 0;
    i81 = 0;
    i82[0] = '\n';
}


bool UnknownUICon::vtable20(unsigned short p0, int p4, int p8) {
    if (p4 != 9)
        return UnkClass203::vtable20(p0, p4, p8);

    if (p0 >= 50000 && p0 < 50048) {
        // TODO: reverse me
        return true;
    }

    switch (p0)
    {
    case 50101:
    case 50103:
    case 50104:
    case 50105:
    case 50106:
    case 50107:
    case 50108:
    case 50109:
        // TODO: reverse
        return true;
    case 50100:
    case 50102:
        return UnkClass203::vtable20(i79, p4, p8);
    default:
        return UnkClass203::vtable20(p0, p4, p8);

}

}

void UnknownUICon::unk1(char * string)
{
    if (string == nullptr) {
        i67[0] = '\0';
        i73 = 0;
        unk3();
    } else {
        if (strlen(string) + 1 > i71) {
            i71 = strlen(string) + 1;
        }
        if (i67 != nullptr) {
            free(i67);
        }

        i67 = static_cast<char*>(malloc(i71));
        strncpy(i67, string, strlen(string));
        i73 = 0;
        unk3();
    }
}

void UnknownUICon::unk3()
{
    if (i67 != nullptr) {
        if (i81 == 0) {
            i75->setText(i67);
        } else {
            char varC8[200]; // TODO: Large enough?

            auto eax = 0;

            if (strlen(i67) > 0) {
                memset(varC8, '*', strlen(i67));
                eax = strlen(i67);
            }

            varC8[eax] = '\0';
            i75->setText(varC8);
        }
    }

    i75->unknew(i73);
}
