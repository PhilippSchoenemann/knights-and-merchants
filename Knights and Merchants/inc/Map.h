#ifndef KNIGHTS_AND_MERCHANTS_MAP_H
#define KNIGHTS_AND_MERCHANTS_MAP_H

#include <memory>
#include <string>

using std::string;
using std::unique_ptr;

class Tile;
class ArrayUnkMap;
class Selection;
class UnitManager;
class HouseManager;
class PlayerStatistics;
class HousesDat;
class UnitDat;
class StoreHouseManager;
class GroupManager;
class ClassyThree;
class RandomGenerator;
class ClassyTwo;
class ArrayUnk00;

namespace knights_and_merchants::utilities
{
    class Rect;
}

namespace knights_and_merchants::io
{
    class FileIo;
}

class Map {
public:
	static Map * instance;
	static Selection * classy0_instance;
	static UnitManager * unitManager;
	static HouseManager * houseManager;
	static PlayerStatistics * playerStatistics;
	static HousesDat * housesDat_instance;
	static UnitDat * unitDat_instance;
	static StoreHouseManager * arrayStoreHouses_instance;
	static GroupManager * groupManager;
	static ClassyThree * classyThree_instance;
	static RandomGenerator * class666_instance;
	static ClassyTwo * classyTwo_instance;
	static ArrayUnk00 * arrayUnk00_instance;


	static void wellDontKnow(const knights_and_merchants::utilities::Rect & rect);

	Map(const int width, const int height, const char p8);
	Map(const string & mapFile);
	~Map();

	void clearMap(int playerID);
	void flatMap();

	bool snapRectangleOnMap(knights_and_merchants::utilities::Rect & rect);
	void unk5(knights_and_merchants::utilities::Rect & rect, const int p4);
	void unk6(const int x, const int y);
	void unk7(const int x, const int y);

	void unk8(knights_and_merchants::utilities::Rect rect, char p4);
	void unk9(knights_and_merchants::utilities::Rect & rect);

	void unk10(const int x, const int y, const int textureSet, const int textureID);

	short unk13(int p0, int p4);

	void unk15();

	void unk17();

	void unk18();
	void unk19();

	void reset();
	bool read(knights_and_merchants::io::FileIo & fileIO);

	bool areCoordinatesValid(const int x, const int y) const;

	Tile & getTile(const int x, const int y);
	const Tile & getTile(const int x, const int y) const;

	unique_ptr<Tile[]> i0_tiles;
	unique_ptr<ArrayUnkMap> i4;
	int i8_width;
	int i12_height;
	int i16;
};

#endif