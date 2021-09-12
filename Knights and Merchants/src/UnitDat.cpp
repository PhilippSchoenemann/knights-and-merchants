#include "UnitDat.h"
#include "io/FileIo.h"

UnitDat::UnitDat(const char * filePath)
{
    knights_and_merchants::io::FileIo fileIO { filePath };

	for (int i = 0; i < 224; ++i)
		i0[i].read(fileIO);

	for (int i = 0; i < 41; ++i)
		i15680[i].read(fileIO);
}

bool UnitDefineData::read(knights_and_merchants::io::FileIo & fileIO)
{
	char buffer[16000];

	fileIO.read(&i0, 2);
	fileIO.read(&i2, 2);

	fileIO.read(buffer, 4); // TODO

	fileIO.read(&i8, 2);
	fileIO.read(&i10, 2);
	fileIO.read(&i12, 2);
	fileIO.read(&i14_clearUpRange, 2);
	fileIO.read(&i16, 1);
	fileIO.read(&i17, 1);
	fileIO.read(&i18, 4);

	for (int i = 0; i < 8; ++i)
		for (int j = 0; j < 8; ++j)
			i22[i][j].read(fileIO);

	for (int i = 0; i < 8; ++i)
		i4502_troupFlagAnimations[i].read(fileIO);

	fileIO.read(buffer, 2836);// TODO
	return true;
}
