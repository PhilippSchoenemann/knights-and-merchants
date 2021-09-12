#include "ClassyTwo.h"
#include <cmath>

ClassyTwo::ClassyTwo(int width, int height, unsigned char x, unsigned char y)
	: i0_x { x }, i1_y { y }, i2_maxX { width - 2 }, i6_maxY { height - 2 }
{

}

void ClassyTwo::setPosition(unsigned char x, unsigned char y)
{
	i0_x = x;
	i1_y = y;
}

bool ClassyTwo::move(char direction)
{
	switch (direction) {
	case 0:
		if (i1_y <= 0)
			return false;

		--i1_y;
		break;
	case 1: 
		if (i1_y <= 0 || i0_x >= i2_maxX)
			return false;

		++i0_x;
		--i1_y;
		break;
	case 2:
		if (i0_x >= i2_maxX)
			return false;

		++i0_x;
		break;
	case 3:
		if (i0_x >= i2_maxX || i1_y >= i6_maxY)
			return false;

		++i0_x;
		++i1_y;
		break;
	case 4:
		if (i1_y >= i6_maxY)
			return false;

		++i1_y;
		break;
	case 5:
		if (i0_x <= 0 || i1_y >= i6_maxY)
			return false;

		--i0_x;
		++i1_y;
		break;
	case 6:
		if (i0_x <= 0)
			return false;

		--i0_x;
		break;
	case 7:
		if (i0_x <= 0 || i1_y <= 0)
			return false;

		--i0_x;
		--i1_y;
		break;
	}

	return true;
}

void ClassyTwo::saveCurrentPosition()
{
	i10_savedX = i0_x;
	i11_savedY = i1_y;
}

void ClassyTwo::restoreSavedPosition()
{
	i0_x = i10_savedX;
	i1_y = i11_savedY;
}

bool ClassyTwo::moveOpposite(char direction)
{
	return move((direction + 4) % 8);
}

bool ClassyTwo::isNeighbor(unsigned char x, unsigned char y)
{
	int dx = x - i0_x;
	int dy = y - i1_y;

	return abs(dx) <= 1 && abs(dy) <= 1 && (dx != 0 || dy != 0);
}

char ClassyTwo::unk7(unsigned char x, unsigned char y)
{
	throw 0;
}

