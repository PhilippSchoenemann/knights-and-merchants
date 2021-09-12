#ifndef KNIGHTS_AND_MERCHANTS_MINIMAP_H
#define KNIGHTS_AND_MERCHANTS_MINIMAP_H

#include "utilities/Rect.h"

namespace knights_and_merchants::graphics
{
    class Bitmap;
    class DrawableSurface;
}

class MiniMapMaybe {
public:
	MiniMapMaybe(const knights_and_merchants::utilities::Rect & rect);
	~MiniMapMaybe();

	void reset();
	void unk1();
	void unk2(int p0, int p4);
	void holdCameraInsideMap();
	void setCameraPosition(const int tileX, const int tileY);
	void moveCamera(int p0, int p4);
	void unk6();
	void unk7();
	void moveToMouseCoordinates(const int x, const int y);

	void unk10();
	void draw(knights_and_merchants::graphics::DrawableSurface & p0);

    knights_and_merchants::utilities::Rect i0;
    knights_and_merchants::graphics::Bitmap * i16;
	int i20;
	short i24;
    knights_and_merchants::utilities::Rect i26;
	short i42;
	short i44;
	int i46;
	int i50;
	int i54[33];
	int i186[33];
	int i318;
};

#endif