#include "ArrayUnk00.h"
#include "Map.h"
#include "HouseManager.h"
#include "House.h"


ArrayUnk00::ArrayUnk00(const int maxSlots)
	: Array<ArrayUnk00Element> { maxSlots }
{
}

ArrayUnk00::~ArrayUnk00()
{
}

short ArrayUnk00::unk1(const int p0, const char p4)
{
	short id { unk11(-1, p0) };

	if (id != INVALID_ID) {
		auto & e = getElement(id);

		e.i6 = 1;
		e.i7 = p4;
		e.i1 = -1;
		e.i8 = 0xf000;

	}

	return id;
}

short ArrayUnk00::unk11(const short p0, const int p4)
{
	int id { addSlot() };

	if (id != INVALID_ID) {
		auto & e = getElement(id);

		e.i3 = p4;
		e.i1 = p0;
		e.i0 = 1;
		e.i8 = 0;

		e.i5 = Map::houseManager->getElement(p4).i1_playerID;
	}

	return id;
}

bool ArrayUnk00Element::isUsed(const ArrayUnk00Element & e)
{
	return e.i6 != -1;
}

void ArrayUnk00Element::setUnused(ArrayUnk00Element & e)
{
	e.i6 = -1;
}
