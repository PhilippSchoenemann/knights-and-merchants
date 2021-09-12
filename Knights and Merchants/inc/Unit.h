#ifndef KNIGHTS_AND_MERCHANTS_UNIT_H
#define KNIGHTS_AND_MERCHANTS_UNIT_H

#include "Map.h"
#include "UnitDat.h"

class Group;
class Unit {
public:

	enum Type {
		None = -1,
		Serf = 0,
		Woodcutter = 1,
		Miner = 2,
		AnimalBreeder = 3,
		Farmer = 4,
		Carpenter = 5,
		Baker = 6,
		Butcher = 7,
		Fisherman = 8,
		Laborer = 9,
		Stonemason = 10,
		Blacksmith = 11,
		Metallurgist = 12,
		Recruit = 13,
		Militia = 14,
		AxeFighter = 15,
		SwordFighter = 16,
		Bowman = 17,
		Crossbowman = 18,
		LanceCarrier = 19,
		Pikeman = 20,
		Scout = 21,
		Knight = 22,
		Barbarian = 23,
		Rebel = 24,
		Rogue = 25,
		Warrior = 26,
		Vagabond = 27,
		Catapult = 28,
		Ballista = 29,
		Wolf = 30,
		Fish = 31,
		Seasnake = 32,
		Seastar = 33,
		Crab = 34,
		SeaFlower = 35,
		SeaLeaf = 36,
		SeaDuck = 37
	};

	static bool isUsed(const Unit & unit);

	static void setUnused(Unit & unit);

	Unit();
	~Unit();

	const UnitDefineData & getDefines() const {
		return Map::unitDat_instance->i15680[i0_type];
	}

	void unk3();
	void unk7(char p0);
	void unk8(char p0);
	void unk9();
	void unk4();
	void unk14();
	void unk15();
	char getGroupType();

	Group & getGroup();

	Type i0_type;
	short i1;
	char i3_player;
	int i4;
	unsigned char i8_x;
	unsigned char i9_y;
	char i10_direction;
	char i11;
	short i12;
	short i14;
	unsigned char i16_hunger;
	char i17;
	char i19;
	short i20;
	short i22;
	short i24;
	short i26;
	short i28;
	int i30;

	char i34;
	char i35;
	short i36;
	char i38;
	char i39;
	char i40;
	char i41;

	short i45;
	short i47_groupId;
	bool i49_isGroupLeader;
	int i50;
	char i54;
	char i55;
	char i56;
	char i57;

};

#endif