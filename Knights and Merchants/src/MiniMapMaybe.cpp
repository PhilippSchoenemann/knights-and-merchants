#include "MiniMapMaybe.h"
#include "graphics/Bitmap.h"
#include "Map.h"
#include "SoundManager.h"
#include "InGame.h"
#include "UnitManager.h"
#include "UnkGame1.h"
#include "Tile.h"
#include "engine/GraphicsHandler.h"
#include "graphics/DrawableSurface.h"
#include <cmath>

using std::floor;


MiniMapMaybe::MiniMapMaybe(const Rect & rect)
	: i0 { rect }, i26 { }
{
	reset();

	i16 = new knights_and_merchants::graphics::Bitmap(Map::instance->i8_width, Map::instance->i12_height, nullptr);
	i46 = 0;
	i50 = 0;
	i24 = 31;

	i42 = 10;
	i44 = 10;

	for (int i = 0, edi = -16; i < 33; ++i, ++edi) {
		float eax = edi;

		if (eax < 0)
			eax++;

		eax = floor(eax / 2) + 16;

		i54[i] = eax;
		i186[i] = eax / 2;

		i54[i] = 256 * i54[i];
		i186[i] = 256 * i186[i];
	}

	unk1();
}

MiniMapMaybe::~MiniMapMaybe()
{
	if (i16 != nullptr)
		delete i16;

	reset();
}

void MiniMapMaybe::reset()
{
	i318 = 1;

	i16 = nullptr;
	i20 = 0;
	i24 = 0;
}

void MiniMapMaybe::unk1()
{
	i26.left = (176 * i46) / Map::instance->i8_width + i0.left;
	i26.top = (176 * i50) / Map::instance->i12_height + i0.top;

	i26.right = (176 * i42) / Map::instance->i8_width + i26.left + 1;
	i26.bottom = (176 * i44) / Map::instance->i12_height + i26.top + 1;

	if (SoundManager::instance != nullptr) {
        SoundManager::instance->setX(i42 / 2 + i46);
        SoundManager::instance->setY(i44 / 2 + i50);
		//instance_SoundsData->i150_x = i42 / 2 + i46;
		//instance_SoundsData->i154_y = i44 / 2 + i50;
	}
}

void MiniMapMaybe::unk2(int p0, int p4)
{
	i42 = p0;
	i44 = p4;
	holdCameraInsideMap();
	unk1();
}

void MiniMapMaybe::holdCameraInsideMap()
{
	if (i46 < 0)
		i46 = 0;

	if (i50 < 0)
		i50 = 0;

	if ((i42 + i46) > (Map::instance->i8_width - 1))
		i46 = Map::instance->i8_width - i42 - 1;

	if ((i44 + i50) > (Map::instance->i12_height - 1))
		i50 = Map::instance->i12_height - i44 - 1;
}

void MiniMapMaybe::setCameraPosition(const int tileX, const int tileY)
{
	i46 = tileX;
	i50 = tileY;
	holdCameraInsideMap();
	unk1();
}

void MiniMapMaybe::moveCamera(int p0, int p4)
{
	i46 += p0;
	i50 += p4;
	holdCameraInsideMap();
	unk1();
}

void MiniMapMaybe::unk6()
{
	auto dword_5369D0 = i16->i0_width * i20 + i16->i12_data;

	const Tile * tile = & Map::instance->getTile(0, i20);

	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < Map::instance->i8_width; ++j) {
			if (tile->isCleared(InGame::instance.i129_humanPlayerID)) {
				if (tile->i7_unitID == -1) {
					if (tile->i15 == -1) {
						*dword_5369D0 = *(UnkGame1::instance->i0 + i54[tile->i1] + *(InGame::patternDat + 6 * tile->i0));
					} else {
						*dword_5369D0 = tile->i15 + 229;
					}
				} else {
					*dword_5369D0 = Map::unitManager->getElement(tile->i7_unitID).i3_player + 229;
				}
			} else {
				*dword_5369D0 = 3;
			}

			dword_5369D0++;
			tile++;
		}

		i20++;

		if (i20 >= Map::instance->i12_height) {
			i20 = 0;

			dword_5369D0 = i16->i12_data;

			tile = &Map::instance->getTile(0, 0);
			tile += Map::instance->i8_width;
			dword_5369D0 += Map::instance->i8_width;
		}
	}
}

void MiniMapMaybe::unk7()
{
	i20 = 0;

	for (int i = 0; i < Map::instance->i12_height / 8; ++i)
		unk6();
	
	i20 = 0;
}

void MiniMapMaybe::moveToMouseCoordinates(const int x, const int y)
{
	i46 = x - i0.left;
	i50 = y - i0.top;

	i46 = static_cast<int>((Map::instance->i8_width   * i46) / 176.f);
	i50 = static_cast<int>((Map::instance->i12_height * i50) / 176.f);

	i46 = i46 - i42 / 2;
	i50 = i50 - i44 / 2;

	holdCameraInsideMap();
	unk1();

}

void MiniMapMaybe::unk10()
{
	Rect rect { 10, 10, Map::instance->i8_width, Map::instance->i12_height };

	this->~MiniMapMaybe();
	new (this) MiniMapMaybe(rect);

	holdCameraInsideMap();
	unk1();
}

void MiniMapMaybe::draw(knights_and_merchants::graphics::DrawableSurface & p0)
{
	if (i318 != 0) {
		unk6();

		i16->drawResized(p0, i0.left, i0.top, 176, 176);
		p0.unk1(i26, 4);
	}
}
