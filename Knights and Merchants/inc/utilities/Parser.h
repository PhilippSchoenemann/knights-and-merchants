#ifndef KNIGHTS_AND_MERCHANTS_UTILITIES_PARSER_H
#define KNIGHTS_AND_MERCHANTS_UTILITIES_PARSER_H

namespace knights_and_merchants::utilities
{
    class Parser
    {
    public:
        Parser(const char * buffer, size_t bufferSize) noexcept;

        const char * searchNext(char symbol);

        const char * findNextNumber();

        const char * findNextText();

        bool readNextNumber(int * p0);
        bool readNext(char * p0);
        bool readNextFilePath(char * p0);
        bool readNextLine(char * p0);

    private:
        static bool isDigit(char symbol);
        static bool isDigitOrLetter(char symbol);
        static bool isLetter(char symbol);
        static bool isSpecial(char symbol);

        static char byte_48B21C[128];

        const char * findNext();

        const char * i0;
        const char * i4;
        const char * i8_buffer;
        size_t i12_bufferSize;
    };
}

#endif
