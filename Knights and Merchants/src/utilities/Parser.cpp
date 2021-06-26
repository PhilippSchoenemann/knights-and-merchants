#include "utilities/Parser.h"

namespace knights_and_merchants::utilities
{
    char Parser::byte_48B21C[128] = {
        00, 04, 04, 04,
        04, 04, 04, 04,
        04, 04, 04, 04,
        04, 04, 04, 04,
        04, 04, 04, 04,
        04, 04, 04, 04,
        04, 04, 04, 04,
        04, 04, 04, 04,
        04, 00, 00, 00,
        00, 00, 00, 00,
        04, 00, 00, 00,
        00, 00, 00, 00,
        02, 02, 02, 02,
        02, 02, 02, 02,
        02, 02, 01, 00,
        00, 00, 00, 00,
        00, 01, 01, 01,
        01, 01, 01, 01,
        01, 01, 01, 01,
        01, 01, 01, 01,
        01, 01, 01, 01,
        01, 01, 01, 01,
        01, 01, 01, 00,
        00, 00, 00, 01,
        00, 01, 01, 01,
        01, 01, 01, 01,
        01, 01, 01, 01,
        01, 01, 01, 01,
        01, 01, 01, 01,
        01, 01, 01, 01,
        01, 01, 01, 00,
        00, 00, 00, 00
    };

    bool Parser::isDigit(const char symbol)
    {
        return byte_48B21C[symbol & 0x7F] & 2;
    }

    bool Parser::isDigitOrLetter(const char symbol)
    {
        return byte_48B21C[symbol & 0x7F] & 3;
    }

    bool Parser::isLetter(const char symbol)
    {
        return byte_48B21C[symbol & 0x7F] & 1;
    }

    bool Parser::isSpecial(const char symbol)
    {
        return byte_48B21C[symbol & 0x7F] & 4;
    }

    Parser::Parser(const char * const buffer, const size_t bufferSize) noexcept
        : i0 { buffer }, i4 { nullptr }, i8_buffer { buffer }, i12_bufferSize { bufferSize } { }

    const char * Parser::searchNext(const char symbol)
    {
        auto eax = i0;
        auto dl = *eax;
        while (dl != symbol) {
            eax++;
            if (dl == '\0' || eax > i8_buffer + i12_bufferSize)
                return nullptr;

            dl = *eax;
        }

        i0 = eax;
        return i0;
    }


    const char * Parser::findNextNumber()
    {
        auto esi = i0;
        while (!isDigit(*esi))
            if (*esi++ == '\0' || esi > i8_buffer + i12_bufferSize)
                return nullptr;

        if (*(esi - 1) == '-')
            esi--;

        i0 = esi;
        return esi;
    }

    const char * Parser::findNextText()
    {
        auto esi = i0;

        while (!isLetter(*esi))
            if (*esi++ == '\0' || esi > i8_buffer + i12_bufferSize)
                return nullptr;

        i0 = esi;
        return esi;
    }

    bool Parser::readNextNumber(int * p0)
    {
        auto ebx = false;

        i4 = i0;
        i0 = findNextNumber();

        if (i0 == nullptr) {
            i0 = i4;
            return false;
        }

        if (*i0 == '-') {
            i0++;
            ebx = true;
        }

        *p0 = 0;

        while (isDigit(*i0)) {
            *p0 = (10 * *p0) + (*i0 - '0');
            i0++;
        }

        if (ebx) {
            *p0 *= -1;
        }

        return true;
    }

    const char * Parser::findNext()
    {
        auto ptr = i0;

        while (!isDigitOrLetter(*ptr))
            if (*ptr++ == '\0')
                return nullptr;

        i0 = ptr;
        return ptr;
    }


    bool Parser::readNext(char * p0)
    {
        i4 = i0;
        i0 = findNext();

        if (i0 == nullptr) {
            i0 = i4;
            return false;
        }

        while (isDigitOrLetter(*i0))
            *p0++ = *i0++;

        *p0 = '\0';
        return true;
    }

    bool Parser::readNextFilePath(char * p0)
    {
        i4 = i0;
        i0 = findNext();

        if (i0 == nullptr) {
            i0 = i4;
            return false;
        }

        while (isDigitOrLetter(*i0) || *i0 == '.' || *i0 == '\\')
            *p0++ = *i0++;
        
        *p0 = '\0';
        return true;
    }

    bool Parser::readNextLine(char * p0)
    {
        i4 = i0;
        i0 = findNext();

        if (i0 == nullptr) {
            i0 = i4;
            return false;
        }

        while (*i0 != '\r' && *i0 != '\n' && *i0 != '\0')
            *p0++ = *i0++;

        *p0 = '\0';
        return true;
    }
}
