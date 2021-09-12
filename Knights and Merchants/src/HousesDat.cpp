#include "HousesDat.h"
#include "io/FileIo.h"

HousesDat::HousesDat(const char * filePath)
{
	knights_and_merchants::io::FileIo fileIO { filePath };

	for (int i = 0; i < 30; ++i)
		i0[i].read(fileIO);

	for (int i = 0; i < 29; ++i)
		i2100[i].read(fileIO);
}

HousesDat::~HousesDat()
{
}

void HouseDefineData::read(knights_and_merchants::io::FileIo & fileIO)
{
	fileIO.read(&i0_graphic1, 2);
	fileIO.read(&i2_graphic2, 2);
	fileIO.read(&i4_graphic3, 2);
	fileIO.read(&i6_graphic4, 2);

	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 5; ++j)
			fileIO.read(&i8_inputWareGraphics[i][j], 2);

	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 5; ++j)
			fileIO.read(&i48_outputWareGraphics[i][j], 2);

	for (int i = 0; i < 4; ++i)
		i88[i].read(fileIO);

	i368.read(fileIO);
	i438.read(fileIO);
	i508.read(fileIO);
	i578_occupiedAnimation.read(fileIO);

	for (int i = 0; i < 3; ++i)
		i648_flagAnimations[i].read(fileIO);

	for (int i = 0; i < 8; ++i)
		i858_flameAnimations[i].read(fileIO);

	for (int i = 0; i < 2; ++i)
		fileIO.read(&i1418[i], 2);

	fileIO.read(&i1422, 2);
	fileIO.read(&i1424, 1);
	fileIO.read(&i1425, 1);
	fileIO.read(&i1426, 1);
	fileIO.read(&i1427, 1);
	fileIO.read(i1428, 10 * 10);
	fileIO.read(i1528, 2);

	char buffer[1024]; // TODO: Delete later
	fileIO.read(buffer, 104);

	fileIO.read(&i1634, 2);
	fileIO.read(&i1636, 2);
	fileIO.read(i1638, 4);
	fileIO.read(i1642, 4);
	fileIO.read(&i1646, 1);
	fileIO.read(&i1647_maxCondition, 2);
	fileIO.read(&i1649_clearUpRange, 2);
	fileIO.read(&i1651, 1);

	i1652.read(fileIO);
}
