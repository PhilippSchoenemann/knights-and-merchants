#pragma once
#include <memory>

namespace knights_and_merchants::engine
{
    class UnkClass5;
    class Bitmap;
}

using knights_and_merchants::engine::UnkClass5;
using knights_and_merchants::engine::Bitmap;
using std::unique_ptr;

struct InterchangeFileFormat {
	unsigned char * fileData;
	size_t          fileSize;
	unsigned char * chunkBMHD;
	unsigned char * chunkBODY;
	unsigned char * chunkCMAP;
};

bool readLBM(const char * const filePath, UnkClass5 * unk);

void IFF_transferColorMapTo(const InterchangeFileFormat & p0, UnkClass5 * unk);

void IFF_getBitmap(const InterchangeFileFormat & p0, Bitmap * p4);

unsigned char * IFF_searchChunk(const InterchangeFileFormat & p0, const char * p4);



unique_ptr<Bitmap> readTextDatBitmap(const char * filePath, bool isEncrypted);