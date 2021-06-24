#include "Globals.h"

unk screenConstants[4] { 
	{ 800,  600, 200, 0, 15, 15, 20, 0 }, 
	{ 1024, 768, 224, 4, 20, 19, 17, -4 }, 
	{ 1280, 960, 200, 0, 27, 24, 17, 0 },
	{ 1280, 1024, 200, 12, 27, 25, 17, -12 }
};

anoUnk word_4982C0[4] {
	{ 408, 550, 405, -1, 402 },
	{ 409, 551, 406, 553, 403 },
	{ 410, 552, 407, 554, 404 },
	{ 410, 552, 407, 580, 404 }
};

// InGame globals

char soundFileNames[16][30] =
{
    "militia",
    "axeman",
    "swordman",
    "bowman",
    "crossbow",
    "lanceman",
    "pikeman",
    "cavalry",
    "knights",
    "barbarian",
    "bowman",
    "lanceman",
    "barbarian",
    "cavalry",
    "nix",
    "nix"
};

char actionNames[13][30] =
{
    "SELECT",
    "SEND",
    "ATTACK",
    "HALT",
    "LEFT",
    "RIGHT",
    "EAT",
    "HALVE",
    "JOIN",
    "FORMAT",
    "DEATH",
    "STORM",
    "BATTLE"
};


int dword_53C57C;