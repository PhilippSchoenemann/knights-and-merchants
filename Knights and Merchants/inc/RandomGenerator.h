#ifndef KNIGHTS_AND_MERCHANTS_RANDOM_GENERATOR_H
#define KNIGHTS_AND_MERCHANTS_RANDOM_GENERATOR_H

class RandomGenerator
{
public:
    RandomGenerator(const unsigned int seed);

    unsigned short next(const unsigned short maximum);

private:
    unsigned short calculateNext();

    unsigned short i0;
    unsigned short i2;
    unsigned short i4;
    unsigned short i6;
    unsigned short i8;
    unsigned short i10;

};

#endif