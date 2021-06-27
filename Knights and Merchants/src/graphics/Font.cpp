#include "graphics/Font.h"
#include "io/FileIo.h"
#include "engine/Bitmap.h"

namespace knights_and_merchants::graphics
{
    Font::Font(short height, int tracking, short spaceWidth)
        : i0_spaceWidth { spaceWidth }, i2_height { height }, i4_tracking { tracking } 
    {
        reset();
    }

    Font::Font(const char * const fileName)
    {
        FileIo fileIO { fileName };
        read(fileIO);
    }

    Font::~Font()
    {
        for (int i = 0; i < 256; ++i)
            if (i8[i] != nullptr)
                delete i8[i];

        reset();
    }

    void Font::reset()
    {
        for (int i = 0; i < 256; ++i)
            i8[i] = nullptr;
    }

    bool Font::read(FileIo & fileIO)
    {
        fileIO.read(&i2_height, 2);
        fileIO.read(&i0_spaceWidth, 2);
        fileIO.read(&i4_tracking, 4);

        unsigned char buffer[256];
        fileIO.read(buffer, 256);

        for (int i = 0; i < 256; ++i)
            if (buffer[i] == 1) {
                i8[i] = new Bitmap();
                i8[i]->read(fileIO);
            }
            else {
                i8[i] = nullptr;
            }


        return true;
    }

    short Font::someUnk(int p0)
    {
        if (p0 == ' ')
            return i0_spaceWidth;

        if (i8[(unsigned char)p0] == nullptr)
            return 0;

        return i8[(unsigned char)p0]->i0_width;
    }


    int Font::calculateTextWidth(char * p0, int p4, int p8)
    {
        if (p0 == nullptr)
            return 0;

        auto var8 = p4;
        if (var8 == 0)
            var8 = strlen(p0);

        auto var4 = 0;
        while ((unsigned char)*p0 > 0 && var8 > 0) {

            switch (*p0) {
            case ' ':
                var4 += i0_spaceWidth;
                break;
            case '~':
                break;
            case '|':
                return var4;
                break;
            default:
                if (*p0 == '<' && p8 != 0) {
                    // TODO: Make this if and content cleaner.

                    while (*p0++ != '>') {
                        --var8;
                        if (*p0 == 0)
                            return var4;
                    }

                    --p0;
                    ++var8;
                    break;
                }

                if (i8[(unsigned char)*p0] != nullptr)
                    var4 += i8[(unsigned char)*p0]->i0_width;

                var4 += i4_tracking;
            }

            ++p0;
            --var8;
        }

        return var4;
    }

    void Font::drawString(DrawableSurface & p0, int p4, int p8, const char * p12)
    {
        drawStringEx(p0, p4, p8, p12, 0, 0, 0);
    }

    void Font::drawStringEx(DrawableSurface & p0, int p4, int p8, const char * p12, short p16, short p20, int p24)
    {
        auto var4 = p4;
        auto var8 = p8;
        auto var10 = 0;
        char varC;
        char var20;

        while (*p12 != '\0') {
            varC = *p12;
            var20 = *p12;

            if (var20 == ' ') {
                var4 += i0_spaceWidth;
            }
            else {
                if (var20 == '|') {
                    if (p24 != 0)
                        return;

                    var4 = p4;
                    var8 += unk1();
                }
                else {
                    if (var20 == '~') {
                        var10 = 1;
                    }
                    else {
                        auto var14 = i8[(unsigned char)varC];

                        if (var14 != nullptr) {
                            if (var10 == 0) {
                                if (p16 == 0) {
                                    var14->draw(p0, var4, var8);
                                }
                                else {
                                    var14->drawSingleColored(p0, var4, var8, p16);
                                }
                            }
                            else {
                                var14->drawSingleColored(p0, var4, var8, p20);
                                var10 = 0;
                            }

                            var4 += var14->i0_width;
                        }

                        var4 += i4_tracking;
                    }
                }
            }

            p12++;
        }
    }

    void Font::drawStringExEx(DrawableSurface & p0, int p4, int p8, const char * p12, short p16)
    {
        drawStringEx(p0, p4, p8, p12, p16, p16, 0);
    }

    short Font::unk2(int p0, char * p4)
    {
        int i = 0;
        auto var4 = 0;
        auto var8 = p4;

        while (true) {
            if (*var8 == '\0')
                return -1;

            auto var18 = *var8;

            if (var18 == ' ') {
                var4 += i0_spaceWidth;
            }
            else if (var18 == '|') {
                return i + 1;
            }
            else if (var18 != '~') {
                if (i8[(unsigned char)*var8] != nullptr) {
                    var4 += i8[(unsigned char)*var8]->i0_width;
                }

                var4 += i4_tracking;
            }

            if (var4 > p0)
                return i;

            var8++;
            i++;
        }
    }

    short Font::unk1()
    {
        return (4 * i2_height) / 3;
    }
}
