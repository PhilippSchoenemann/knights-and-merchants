#pragma once

#include "ui/UnkClass200.h"

namespace knights_and_merchants::text
{
    class Lib;
}

using knights_and_merchants::text::Lib;


namespace knights_and_merchants::graphics
{
    class Bitmap;

    class Font;

    class RX;

    class Palette;

    class DrawableSurface;
}

using knights_and_merchants::graphics::RX;
using knights_and_merchants::graphics::Palette;

namespace knights_and_merchants::ui::controls
{
    class ImageBox;

    class TextBox;

    class Button;

    class UnkClass672;

}

namespace knights_and_merchants::utilities
{
    class Rect;
}

class UnknownUICon;

class NetworkClass;

class MasterClass : public UnkClass200
{
public:
    MasterClass(int p0);

    virtual ~MasterClass();

    virtual bool vtable4(unsigned short p0, int p4, int p8) override;

    virtual void vtable12(knights_and_merchants::graphics::DrawableSurface & p0, knights_and_merchants::utilities::Rect & p4) override;

    void reset() noexcept;

    void someLoop(int p0);

    void createMainMenu();

    void createLoadSavegameMenu();

    void createCreditsMenu();

    void createTSKMenu();

    void createPlaySingleMapMenu();

    void updatePlaySingleMapMenu();

    void unk10();

    void unk20();

    int update();

    void draw(knights_and_merchants::graphics::DrawableSurface & surface);

    void readRemap(const char * fileName);


    void updateResolutionButton(knights_and_merchants::ui::controls::Button & p0);


    void react();


    void unkWndProc(bool p0);

private:
    void static drawFunction(knights_and_merchants::graphics::DrawableSurface & p0);

    void sub_4015BE();

public:
    char i882;
    int i883;
    int i887;
    char i891;
    int i892;
    int i896;
    int i900;
    Palette * i904;
    knights_and_merchants::graphics::Font * i908;
    knights_and_merchants::graphics::Font * i912;
    knights_and_merchants::graphics::Font * i916;
    knights_and_merchants::graphics::Font * i920;
    knights_and_merchants::graphics::Font * i924;
    knights_and_merchants::graphics::Font * i928[5];
    Lib * i948;
    RX * i952;
    char i956;
    int i957;
    void * i961;
    char i965[120];

    NetworkClass * i1089;

    int i1094;
    int i1098;

    int i1114;
    int i1118;
    int i1122;
    int i1126;

    knights_and_merchants::ui::controls::Button * i1134;

    int i1142;

    int i1150[6];
    UnknownUICon * i1174;
    knights_and_merchants::ui::controls::TextBox * i1178;
    knights_and_merchants::ui::controls::TextBox * i1182;
    unsigned char * i1186[5];


    int i1206;
    int i1210;
    int i1214;
    int i1218;

    int i1266;
    knights_and_merchants::ui::controls::UnkClass672 * i1270;
    int i1274;
    int i1278;
    char i1282;


    void * i1382;
    knights_and_merchants::graphics::Bitmap * i1386;
    void * i1390;
    int i1394;
    int i1398;
    knights_and_merchants::ui::controls::ImageBox * i1420;
    knights_and_merchants::ui::controls::TextBox * i1424;
    knights_and_merchants::ui::controls::Button * i1432;
    knights_and_merchants::ui::controls::Button * i1436;
    int i1440;


};

