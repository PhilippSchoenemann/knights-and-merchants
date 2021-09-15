#ifndef KNIGHTS_AND_MERCHANTS_UNKNOWNUICON_H
#define KNIGHTS_AND_MERCHANTS_UNKNOWNUICON_H

#include "ui/UnkClass203.h"

namespace knights_and_merchants::utilities
{
    class Rect;
}

namespace knights_and_merchants::ui::controls
{
    class TextBox;
}

class UnknownUICon : public UnkClass203
{

public:

    UnknownUICon(knights_and_merchants::utilities::Rect & position, char p16, int p20, int p24, unsigned char * p28, unsigned char * p32);

    ~UnknownUICon();

    virtual bool vtable20(unsigned short p0, int p4, int p8) override;

    void reset();

    void unk1(char * string);

private:
    static unsigned char unk_49ADB8[48];

    char * i67;
    short i71;
    short i73;
    knights_and_merchants::ui::controls::TextBox * i75;
    short i79;
    char i81;
    char i82[2000];

    void unk3();

    void unk7(unsigned short p0);
};

#endif
