#include "ArrayUnkMap.h"
#include "io/FileIo.h"

ArrayUnkMap::ArrayUnkMap(const int size)
	: Array<MapElem> { size, sizeof(MapElem), MapElem::isUsed, MapElem::setUnused }, i32 { 0 }
{

}

ArrayUnkMap::~ArrayUnkMap()
{
	reset();
}

void ArrayUnkMap::reset()
{
	i32 = 0;
}

bool ArrayUnkMap::read(knights_and_merchants::io::FileIo & fileIO)
{
    fileIO.read(&i32, 2);
    if (!Array::resetNRead(fileIO))
    	return false;

	//if (!fileIO.read(&i32, 2) || !Array::resetNRead(fileIO))
	//	return false;

	i24 = MapElem::isUsed;
	i28 = MapElem::setUnused;
	return true;
}

void MapElem::read(knights_and_merchants::io::FileIo & fileIO)
{
	fileIO.read(&i0, 4);
	fileIO.read(&i4, 4);
	fileIO.read(&i8, 4);
	fileIO.read(&i12, 4);
	fileIO.read(&i16, 1);
}
