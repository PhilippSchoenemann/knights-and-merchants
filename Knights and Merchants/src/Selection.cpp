#include "Selection.h"

#include "Map.h"


Selection::Selection(short width, short height)
	: i0_width { width }, i2_height { height }, i4_x { 1 }, i8_y { 1 }, i12 { 1 }, i16 { 0 }
{
	
}

void Selection::move(int dx, int dy)
{
	i4_x += dx;
	i8_y += dy;
	unk1();
}

void Selection::setSize(short width, short height)
{
	i0_width = width;
	i2_height = height;
	unk1();
}

void Selection::setPosition(int x, int y)
{
	i4_x = x;
	i8_y = y;
	unk1();
}

void Selection::unk1()
{
	if (i4_x < 0)
		i4_x = 0;

	if (i8_y < 0)
		i8_y = 0;

	if ((i0_width + i4_x) > (Map::instance->i8_width - 1))
		i4_x = Map::instance->i8_width - i0_width - 1;

	if ((i2_height + i8_y) > (Map::instance->i12_height - 1))
		i8_y = Map::instance->i12_height - i2_height - 1;
}

void Selection::resetPosition()
{
	i4_x = 0;
	i8_y = 0;
	unk1();
}
