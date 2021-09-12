#include "UnkGame1.h"
#include <cstdlib>
#include "graphics/Palette.h"
#include <cstdio>
#include "Globals.h"
#include "io/FileIo.h"
#include "graphics/Bitmap.h"
#include "InterchangeFileFormat.h"
#include "InGame.h"
UnkGame1 * UnkGame1::instance;



int UnkGame1::unk_498720[2];


unsigned char * UnkGame1::getRemap(char i) {
	return UnkGame1::instance->i124[i];
}

UnkGame1::UnkGame1(int p0)
{
	reset();
	i20 = (unsigned char *) malloc(0x50000);

	auto eax = (unsigned char *) (((uintptr_t) i20 + 0xFFFF) & ~0xFFFF);
	for (int i = 0; i < 4; ++i) {
		i4[i] = eax;
		eax += 0x10000;
	}

	i24 = (unsigned char *) malloc(0x12100);
	i0 = (unsigned char *) (((uintptr_t) i24 + 0xFFFF) & ~0xFFFF);

	i144 = new knights_and_merchants::graphics::Palette();

	loadPalette(p0);

	if ((i0 - i24) <= 0x800)
		i28[0] = i0 + 0x10001;
	else
		i28[0] = i24;

	int eaxx = 0x100;
	auto ecx = &i28[1];
	do {
		*ecx++ = i28[0] + eaxx;
		eaxx += 0x100;
	} while (eaxx < 0x800);

	for (int i = 0; i < 8; ++i)
		for (int j = 0; j < 2; ++j)
			i60[i][j] = (unsigned char *) malloc(0x100);

	unkFunc1();
	
	i124[0] = i0 + 0x400;
	i124[1] = i0 + 0x1400;
	i124[2] = i0 + 0x700;
	i124[3] = i0 + 0x1200;
	i124[4] = i0 + 0x1E00;

	readTextDats();
	readGourad();
}

UnkGame1::~UnkGame1()
{
	free(i20);
	free(i24);

	for (int i = 0; i < 8; ++i)
		for (int j = 0; j < 2; ++j)
			if (i60[i][j] != nullptr)
				free(i60[i][j]);

	if (i144 != nullptr)
		delete i144;

	reset();
}

void UnkGame1::reset()
{
	i0 = nullptr;

	for (int i = 0; i < 4; ++i)
		i4[i] = nullptr;

	i20 = nullptr;
	i24 = nullptr;

	for (int i = 0; i < 8; ++i)
		i28[i] = nullptr;

	for (int i = 0; i < 8; ++i)
		for (int j = 0; j < 2; ++j)
			i60[i][j] = nullptr;

	for (int i = 0; i < 5; ++i)
		i124[i] = nullptr;

	i144 = nullptr;
	i148 = 0;
}

void UnkGame1::loadPalette(int p0)
{
	i148 = (unsigned char) p0;

	char filePath[200];
	sprintf(filePath, "data/gfx/pal%d.bbm", p0);

	readLBM(filePath, i144);
	i144->i832_colorCycleCount = 0;

	i144->addColorCycle(240, 8, 0);
	i144->addColorCycle(248, 3, 2);
	i144->addColorCycle(224, 5, 0);
	i144->addColorCycle(237, 3, 2);

	i144->setColor(0, 255, 255, 0);
	i144->setColor(255, 255, 255, 0);

	unkMapColor();
}

void UnkGame1::unkFunc1()
{
	static unsigned char unk_4986E0[] = {
		0x18 ,0x19 ,0x1A ,0x1B,
		0x1C ,0x1D ,0x1E ,0x1F,
		0x20 ,0x21 ,0x22 ,0x23,
		0x24 ,0x25 ,0x26 ,0x27,
		0x68 ,0x69 ,0x6A ,0x6B,
		0x6C ,0x6D ,0x6E ,0x6F,
		0x10 ,0x11 ,0x12 ,0x13,
		0x14 ,0x15 ,0x16 ,0x17,
		0x60 ,0x61 ,0x62 ,0x63,
		0x64 ,0x65 ,0x66 ,0x67,
		0xD1 ,0xD2 ,0xD3 ,0xD4,
		0xD5 ,0xD6 ,0xD7, 0xD8,
		0x00 ,0x00 ,0x00 ,0x00,
		0x00 ,0x00 ,0x00 ,0x00,
		0x00 ,0x00 ,0x00 ,0x00,
		0x00 ,0x00 ,0x00 ,0x00
	};

	auto ptr = unk_4986E0;
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 256; ++j)
			*(i28[i] + j) = j;
		
		for (int j = 0; j < 8; ++j)
			*(i28[i] + 24 + j) = *ptr++;
	}

	for (int i = 0; i < 8; ++i)
		if (InGame::instance.i34[i][0] != 0xFF)
			for (int j = 0; j < 8; ++j)
				*(i28[i] + 24 + j) = InGame::instance.i34[i][j];
		
	for (int i = 0; i < 8; ++i)
		for (int j = 0; j < 2; ++j)
			if (i60[i][j] != nullptr) {
				
				for (int k = 0; k < 256; ++k)
					i60[i][j][k] = k;

				for (int k = 0, eax = unk_498720[j]; k < 8; ++k)
					if (eax < 0) {
						i60[i][j][24 + k] = i28[0][24];
					} else if (eax <= 7) {
						i60[i][j][24 + k] = i28[0][24 + eax];
					} else {
						i60[i][j][24 + k] = i28[0][31];
					}
			}

}

void UnkGame1::readTextDats()
{
	char filePath[200];
	for (int i = 0; i < 4; ++i) {
		sprintf(filePath, "data/gfx/text%d.dat", i);
		unique_ptr<knights_and_merchants::graphics::Bitmap> bitmap = readTextDatBitmap(filePath, true);

		memcpy(i4[i], bitmap->i12_data, 0x10000);
	}
}

void UnkGame1::readGourad()
{
	knights_and_merchants::io::FileIo fileIO { "data/gfx/gouraud.dat" };
	fileIO.read(i0, 0x2100);
}

void UnkGame1::unkMapColor()
{
	for (int i = 0; i < 8; ++i)
		if (InGame::instance.i98[i] != 0xFF)
			i144->setColor((unsigned char)(i - 27), i144->getColor(InGame::instance.i98[i]));
}
