#include "InterchangeFileFormat.h"
#include "io/FileIo.h"
#include "engine/Bitmap.h"
#include "graphics/Palette.h"

using std::make_unique;
using knights_and_merchants::io::FileIo;
using knights_and_merchants::graphics::Color;
using knights_and_merchants::graphics::Palette;

bool readLBM(const char * const filePath, Palette * unk) {
	InterchangeFileFormat x { };

	FileIo fileIO { filePath };

	x.fileSize = fileIO.getFileSize();
	x.fileData = (unsigned char *) malloc(x.fileSize);

	if (x.fileData == nullptr)
		return false;

    fileIO.read(x.fileData, x.fileSize);
    if (   (x.chunkBMHD = IFF_searchChunk(x, "BMHD")) == nullptr
        || (x.chunkBODY = IFF_searchChunk(x, "BODY")) == nullptr
        || (x.chunkCMAP = IFF_searchChunk(x, "CMAP")) == nullptr)
    {
        free(x.fileData);
        return false;
    }
	/*if (!fileIO.read(x.fileData, x.fileSize) TODO: bool to exception
		|| (x.chunkBMHD = IFF_searchChunk(x, "BMHD")) == nullptr
		|| (x.chunkBODY = IFF_searchChunk(x, "BODY")) == nullptr
		|| (x.chunkCMAP = IFF_searchChunk(x, "CMAP")) == nullptr)
	{
		free(x.fileData);
		return false;
	}*/

	IFF_transferColorMapTo(x, unk);

	free(x.fileData);
	return true;
}

void IFF_transferColorMapTo(const InterchangeFileFormat & p0, knights_and_merchants::graphics::Palette * unk)
{
	const auto * color = reinterpret_cast<const Color *>(p0.chunkCMAP + 8);

	for (int i = 0; i < 256; ++i, ++color)
		unk->setColor(i, color->r, color->g, color->b);
}

void IFF_getBitmap(const InterchangeFileFormat & p0, Bitmap * p4) {
	if (p4 == nullptr || p4->i12_data == nullptr)
		return;

	auto width = (p0.chunkBMHD[8] << 8) | p0.chunkBMHD[9];
	auto height = (p0.chunkBMHD[10] << 8) | p0.chunkBMHD[11];

	auto ptr = p0.chunkBODY + 8;

	if (p0.chunkBMHD[18] != 0) {
		if (height <= 0)
			return;

		for (int i = 0; i < height; ++i) {
			for (int ecx = 0; ecx < width;) {
				auto dl = *ptr++;
				if (dl == 0x80)
					continue;

				if (dl > 0x80) {
					dl = 1 - dl;

					if (dl > 0) {
						while (dl--) {
							if (ecx < p4->i0_width && i < p4->i2_height)
								p4->i12_data[p4->i0_width * i + ecx] = *ptr;

							ecx++;
						}
					}

					ptr++;
				}
				else {
					dl++;

					if (dl > 0) {
						while (dl--) {
							if (ecx < p4->i0_width && i < p4->i2_height)
								p4->i12_data[p4->i0_width * i + ecx] = *ptr++;

							ecx++;
						}
					}
				}
			}
		}
	}
	else {
		if (height <= 0)
			return;

		for (int i = 0; i < height; ++i)
			for (int j = 0; j < width; ++j)
				if (j < p4->i0_width && i < p4->i2_height)
					p4->i12_data[p4->i0_width * i + j] = *ptr++;
	}
}

unsigned char * IFF_searchChunk(const InterchangeFileFormat & p0, const char * p4) {
	for (int i = 0; i < p0.fileSize; ++i) {
		auto ptr1 = p0.fileData + i;
		auto ptr2 = (const unsigned char *) p4;

		int correct = 0;
		for (int j = 0; j < 4; ++j)
			if (*ptr1++ == *ptr2++)
				correct++;

		if (correct == 4)
			return p0.fileData + i;
	}
	
	return nullptr;
}



unique_ptr<Bitmap> readTextDatBitmap(const char * filePath, bool isEncrypted)
{
	InterchangeFileFormat ff{ };

	FileIo fileIO{ filePath };

	ff.fileSize = fileIO.getFileSize();
	if (ff.fileSize <= 0 || ff.fileSize == INVALID_FILE_SIZE)
		return unique_ptr<Bitmap> { };

	ff.fileData = (unsigned char *)malloc(ff.fileSize);
	if (ff.fileData == nullptr)
		return unique_ptr<Bitmap> { };


    fileIO.read(ff.fileData, ff.fileSize);
    /*if (!fileIO.read(ff.fileData, ff.fileSize)) { TODO: exception handling
		free(ff.fileData);
		return unique_ptr<Bitmap> { };
	}*/

	if (isEncrypted)
		for (int i = 0; i < ff.fileSize; ++i)
			ff.fileData[i] ^= 0xEF;

	if ((ff.chunkBMHD = IFF_searchChunk(ff, "BMHD")) == nullptr
		|| (ff.chunkBODY = IFF_searchChunk(ff, "BODY")) == nullptr
		|| (ff.chunkCMAP = IFF_searchChunk(ff, "CMAP")) == nullptr)
	{
		free(ff.fileData);
		return unique_ptr<Bitmap> { };
	}

	int width = (ff.chunkBMHD[8] << 8) | ff.chunkBMHD[9];
	int height = (ff.chunkBMHD[10] << 8) | ff.chunkBMHD[11];

	auto bitmap = make_unique<Bitmap>(width, height, nullptr);

	IFF_getBitmap(ff, bitmap.get());

	free(ff.fileData);
	return bitmap;
}
