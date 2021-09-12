#pragma once
#include <memory>

namespace knights_and_merchants::graphics
{
    class Bitmap;
    class Palette;
}

using knights_and_merchants::graphics::Palette;

using std::unique_ptr;

struct InterchangeFileFormat {
	unsigned char * fileData;
	size_t          fileSize;
	unsigned char * chunkBMHD;
	unsigned char * chunkBODY;
	unsigned char * chunkCMAP;
};

bool readLBM(const char * const filePath, Palette * unk);

void IFF_transferColorMapTo(const InterchangeFileFormat & p0, Palette * unk);

void IFF_getBitmap(const InterchangeFileFormat & p0, knights_and_merchants::graphics::Bitmap * p4);

unsigned char * IFF_searchChunk(const InterchangeFileFormat & p0, const char * p4);



unique_ptr<knights_and_merchants::graphics::Bitmap> readTextDatBitmap(const char * filePath, bool isEncrypted);