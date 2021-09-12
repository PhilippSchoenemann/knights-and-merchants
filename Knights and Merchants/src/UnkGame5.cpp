#include "UnkGame5.h"
#include "Map.h"
#include "InGame.h"
#include "Tile.h"
#include "UnkGame3.h"
#include "engine/GraphicsHandler.h"
#include "graphics/DrawableSurface.h"

someStruct UnkGame5::_someStruct;

class InGame;


UnkGame5::UnkGame5(const Rect & rect, unsigned char ** p4, unsigned char * p8)
	: i20 { rect }, i36 { rect }, i52 { }
{
	reset();

	i0 = p8;

	for (int i = 0; i < 4; ++i)
		i4_textureSets[i] = p4[i];

	i100 = i20.getWidth();
	i102 = i20.getHeight();

	i117 = 1600 * i100 * (i102 + 10);

	i68 = (unsigned char * ) malloc(2 * i117 + 2000);

	i72 = i68;
	i76 = i68 + i117;

	i80 = 40 * i100;
	i84 = 40 * (i102 + 10);
	i88 = 40 * i102;
	i92 = i88;
	i96 = 40 * (i102 + i100);

	i104 = 1;

	i52.setBounds(i20.left, i20.top, i80 - 1, i88 - 1);
	i113 = false;

	UnkGame5::_someStruct.i80 = i0;
	UnkGame5::_someStruct.i4 = i80;
	UnkGame5::_someStruct.i8 = i84;
	UnkGame5::_someStruct.i72 = 3;

	for (int i = 0; i < 33; ++i) {
		i121[i] = i / 2;

		if (i121[i] > 10)
			i121[i] = 10;
	}

}

UnkGame5::~UnkGame5()
{
	free(i68);
	reset();
}

void UnkGame5::reset()
{
	i0 = nullptr;
	
	for (int i = 0; i < 4; ++i)
		i4_textureSets[i] = nullptr;

	i68 = nullptr;
	i72 = nullptr;
	i76 = nullptr;

	i109 = 0;
}

void UnkGame5::unk16(knights_and_merchants::graphics::DrawableSurface & p0)
{
	auto ebx = i72 + 200 * i80;
	auto eax = p0.i6_surface + i20.left + p0.i4_pitch * i20.top;

	for (int i = 0; i < i88; ++i) {
		memcpy(eax, ebx, i80);

		eax += p0.i4_pitch;
		ebx += i80;
	}
}

void UnkGame5::unk17(const Tile & p0)
{
	
	unsigned char * var8 { i4_textureSets[3] + 0xC0C0 };

	int edx = p0.i0;
	int esi = p0.i0;

	edx >>= 3;
	edx &= 7;
	edx <<= 8;

	esi &= 0x3F;
	esi &= 7;

	edx += esi;
	auto edi = i4_textureSets[p0.i0 >> 6];
	edx <<= 5;
	auto edxP = edx + edi;
	auto var4 = edxP;

	auto dest = var8;
	auto sour = var4;

	for (int i = 0; i < 32; ++i) {
		memcpy(dest, sour, 32);
		dest += 224 + 32;
		sour += 224 + 32;
	}


	auto ecx = p0.i22;
	edx = p0.i3;
	esi = ecx;
	edx &= 3;
	esi >>= 4;
	esi &= 3;
	esi -= edx;
	esi += 4;
	edx = esi;

	edx &= 3;
	// TODO: check strange minus and sign

	switch (edx) {
	case 1:
		edxP = i4_textureSets[3];
		ecx &= 0xf;
		ecx += 2039;
		ecx <<= 5;
		var4 = ecx + edxP;
		dest = var8;
		sour = var4;

		for (int i = 0; i < 32; ++i) {
			for (int j = 0; j < 32; ++j) {
				if (*sour != 0)
					*dest = *sour;

				dest++;
				sour -= 256;

			}

			dest += 224;
			sour += 8192;
			sour++;


		}
		return;
	case 2:
		var4 = i4_textureSets[3] + 0xFEFF + 32 * (ecx & 0xF);

		dest = var8;
		sour = var4;

		for (int i = 0; i < 32; ++i) {
			for (int j = 0; j < 32; ++j) {
				if (*sour != 0)
					*dest = *sour;

				dest++;
				sour--;
			}

			dest += 224;
			sour -= 224;
		}
		return;
	case 3:
		var4 = i4_textureSets[3] + 0xDFFF + 32 * (ecx & 0xF);

		dest = var8;
		sour = var4;

		for (int i = 0; i < 32; ++i) {
			for (int j = 0; j < 32; ++j) {
				if (*sour != 0)
					*dest = *sour;

				dest++;
				sour += 256;
			}

			dest += 224;
			sour -= 8192;
			sour--;
		}
		return;
	default:
		var4 = i4_textureSets[3] + 32 * ((ecx & 0xF) + 0x6ff);

		dest = var8;
		sour = var4;

		for (int i = 0; i < 32; ++i) {
			for (int j = 0; j < 32; ++j) {
				if (*sour != 0)
					*dest = *sour;

				dest++;
				sour++;
			}

			dest += 224;
			sour += 224;
		}
		return;
	};

	throw 0;
}

void UnkGame5::unk20(bool p0, int p4)
{
	i113 = p0;
	i88 = p0 ? p4 : i92;
}

bool UnkGame5::drawTerrain(knights_and_merchants::graphics::DrawableSurface & p0, int p4, int p8, char & p12)
{
	Rect rectangle { };
	short var3C ;
	short var40 ;

	auto var14 { false };

	if (i104 == 0) {
	
		if (i36.left != p4 || i36.top != p8) {
			auto var1C = p4 - i36.left;
			auto var18 = p8 - i36.top;
			var14 = true;
			auto var20 = i100;
			auto var24 = i102;

			if (abs(var1C) >= i100 || abs(var18) >= i102 + 5) {
				var3C = i100;
				var40 = i102 + 5;

				unk11(p4, p8, var3C, var40);
				unk12(p4, p8, 0, 0, var3C, var40);
				p12 = 1;
			} else {
				int arg8;
				int var2C;
				int var30;
				int var34;

				if (var1C == 0) {
					var34 = 0;
					arg8 = 0;
					var30 = 0;
					var2C = 0;
				} else if (var1C < 0) {
					var34 = abs(var1C);
					arg8 = 0;
					var30 = 0;
					var2C = 0;
				} else {
					arg8 = 40 * abs(var1C);
					var34 = 0;
					var30 = var20 - abs(var1C);
					var2C = i100 - abs(var1C);
				}

				int var38;
				int var28;

				int ecx;
				int edx;

				if (var18 == 0) {
					var38 = 0;
					var28 = 0;
					var24 = 0;
					ecx = 40 * (i102 + 10);
					edx = 0;
				} else if (var18 < 0) {
					var38 = abs(var18) + 1;
					var28 = 0;
					var24 = 0;
					ecx = 40 * (i102 + 9) - 40 * abs(var18);
					edx = 40;
				} else {
					var38 = 0;
					var28 = (i102 - abs(var18)) + 5;
					var24 = (i102 - abs(var18)) + 5;
					ecx = 40 * (i102 + 10) - 40 * abs(var18);
					edx = 40 * abs(var18);
				}

				rectangle.setBounds(arg8, edx, 40 * (var20 - abs(var1C)), ecx );
				unk10(rectangle, var34, var38);

				auto t = i76;
				i76 = i72;
				i72 = t;

				if (var1C != 0) {
					var40 = i102 + 5;
					var3C = abs(var1C);
					arg8 = p4 + var30;
					unk11(p4 + var30, p8, var3C, var40);
					unk12(arg8, p8, var2C, 0, var3C, var40);
				}

				if (var18 != 0) {		
					var3C = i100;
					var40 = abs(var18);
					unk11(p4, p8 + var28, var3C, var40);
					unk12(p4, p8 + var28, 0, var24, var3C, var40);
				}

				p12 = 1;
			}
		}

		var3C = i100;
		var40 = i102 + 5;
		unk11(p4, p8, var3C, var40);
		
		if (!unk15(p4, p8, 0, 0, var3C, var40) && !var14) {
			if (p12 == 0) { // TODO: normally jbe, but unsigned only 0?
				return false;
			} else {
				unk16(p0);
				p12--;
				return true;
			}
		}	
	} else {
		var3C = i100;
		var40 = i102 + 5;

		i104 = 0;

		unk11(p4, p8, var3C, var40);
		unk12(p4, p8, 0, 0, var3C, var40);
		p12 = 1;
	}

	i36.left = p4;
	i36.top = p8;
	i36.setSize(i100, i102);

	unk16(p0);

	if (p12 > 0)
		p12--;

	return true;
}

void UnkGame5::unk10(const Rect & p0, int p4, int p8)
{
	auto dword_52CB54 = p0.getWidth();
	auto dword_52CB84 = p0.getHeight();

	auto dword_52CB70 = i76 + 40 * (p4 + p8 * i80);

	_someStruct.i96 = i80 * p0.top + i72 + p0.left;

	auto dword_52CB80 = i80 - dword_52CB54;

	auto edi = dword_52CB70;
	auto esi = _someStruct.i96;
	auto ecx = dword_52CB84;
	auto ebx = dword_52CB80;
	auto edx = dword_52CB54;
	edx = (unsigned int) edx >> 2;

	while (ecx--) {
		memcpy(edi, esi, dword_52CB54);

		edi += dword_52CB54;
		esi += dword_52CB54;

		edi += ebx;
		esi += ebx;
	}
}

void UnkGame5::unk11(int p0, int p4, short & p8, short & p12)
{
	auto eax = Map::instance->i12_height;

	if (p12 + p4 > eax - 2)
		p12 = (p4 < eax - 1) ? eax - p4 - 1 : 0;
}

void UnkGame5::unk12(int p0, int p4, int p8, int p12, short p16, short p20)
{
	_someStruct.i0 = i72;

	auto var4 = 640 * p8;
	auto edi = 640 * (p12 + 5);

	for (int i = 0; i < p20; ++i) {
		auto esi = var4;

		for (int j = 0; j < p16; ++j) {
			unk13(j + p0, i + p4, esi, edi);
			esi += 640;
		}

		edi += 640;
	}
}

void UnkGame5::unk13(int p0, int p4, int p8, int p12)
{
	auto var9 = InGame::instance.i129_humanPlayerID;
	auto & tile = Map::instance->getTile(p0, p4);

	int * edi;

	tile.i14 = 0;
	if ((tile.i22 & 0xF) == 0) {
		_someStruct.i76_textureSet = i4_textureSets[tile.i0 >> 6];
		edi = UnkGame3::unk_536A0C[tile.i0 & 0x3F][tile.i3 & 3];
	} else {
		unk17(tile);

		_someStruct.i76_textureSet = i4_textureSets[3];
		edi = UnkGame3::unk_536A0C[54][tile.i3 & 3];
	}

	_someStruct.i48 = edi[0];
	_someStruct.i52 = edi[1];
	_someStruct.i56 = edi[2];
	_someStruct.i60 = edi[3];
	_someStruct.i64 = edi[4];
	_someStruct.i68 = edi[5];

	_someStruct.i12 = p8;
	_someStruct.i16 = p12 - 16 * tile.i2_height;

	if ((tile.i13_clearedFlags & (1 << var9)) == 0) {
		_someStruct.i20 = 0;
	} else {
		_someStruct.i20 = tile.i1; // i1 is char, could cause sign trouble in the future ... near future
		_someStruct.i20 <<= 8;
	}

	auto var4 = p0 + 1;
	auto var8 = p4 + 1;

	auto & tile2 = Map::instance->getTile(p0 + 1, p4 + 1);

	_someStruct.i24 = p8 + 640;
	_someStruct.i28 = p12 + 640;
	_someStruct.i28 -= 16 * tile2.i2_height;

	if ((tile2.i13_clearedFlags & (1 << var9)) == 0) {
		_someStruct.i32 = 0;
	} else {
		_someStruct.i32 = tile2.i1;
		_someStruct.i32 <<= 8;
	}

	auto & tile3 = Map::instance->getTile(p0, p4 + 1);

	_someStruct.i36 = p8;
	_someStruct.i40 = p12 + 640;
	_someStruct.i40 -= 16 * tile3.i2_height;

	if ((tile3.i13_clearedFlags & (1 << var9)) == 0) {
		_someStruct.i44 = 0;
	} else {
		_someStruct.i44 = tile3.i1;
		_someStruct.i44 <<= 8;
	}

	UnkGame5::sub_401910();

	_someStruct.i36 = _someStruct.i24;
	_someStruct.i40 = _someStruct.i28;
	_someStruct.i44 = _someStruct.i32;

	_someStruct.i64 = _someStruct.i56;
	_someStruct.i68 = _someStruct.i60;

	auto & tile4 = Map::instance->getTile(p0 + 1, p4);

	_someStruct.i24 = p8 + 640;
	_someStruct.i28 = p12;
	_someStruct.i28 -= 16 * tile4.i2_height;

	if ((tile4.i13_clearedFlags & (1 << var9)) == 0) {
		_someStruct.i32 = 0;
	} else {
		_someStruct.i32 = tile4.i1;
		_someStruct.i32 <<= 8;
	}
	
	_someStruct.i56 = edi[6];
	_someStruct.i60 = edi[7];

	UnkGame5::sub_401910();
}

bool UnkGame5::unk15(int p0, int p4, int p8, int p12, short p16, short p20)
{
	unsigned char var11 = InGame::instance.i129_humanPlayerID;

	_someStruct.i0 = i72;
	auto var10 = false;

	auto varC = 640 * p8;
	auto edi = 640 * (p12 + 5);

	for (int i = 0; i < p20; ++i) {
		auto esi = varC;

		auto * tile = &Map::instance->getTile(p0, i + p4);

		auto var4 = 1 << var11;
		for (int j = 0; j < p16; ++j) {
			if ((tile->i14 & var4) != 0) {
				unk13(j + p0, i + p4, esi, edi);
				var10 = true;
			}

			esi += 640;
			tile++;
		}

		edi += 640;
	}

	return var10;
}



void UnkGame5::sub_401910()
{

	auto esi = 0;
	auto eax = 0;

	auto dword_52CB74 = _someStruct.i72;
	auto dword_52CBA4 = 0;
	auto dword_52CB90 = 0;

	_someStruct.i88 = &_someStruct.i48;
	_someStruct.i84 = &_someStruct.i48;

	auto dword_52CB60 = &_someStruct.i12;
	auto dword_5202CC = 0x7FFFFFF8;
	auto dword_52CBA0 = 0;

	dword_52CB74--;

	auto ebp = dword_52CB60[0];
	auto edx = dword_52CB60[1];
	auto dword_52CB9C = dword_52CB60[2];
	dword_52CB60 += 3; // should be 12 in byte.

	auto dword_52CB4C = _someStruct.i88[0];
	auto dword_52CB88 = _someStruct.i88[1];
	_someStruct.i88 += 2; // should be 8 in byte.

	top:
		auto ecx = dword_52CB60[0];
		auto ebx = dword_52CB60[1];
		auto dword_52CB5C = dword_52CB60[2];
		auto dword_52CB98 = _someStruct.i88[0];
		_someStruct.i104 = _someStruct.i88[1];

	bottom:
		auto edi = _someStruct.i112;

		if (ebx <= edx) {
			if (ebx == edx)
				goto aTop;

			auto tmp1 = ebp;
			ebp = ecx;
			ecx = tmp1;
			
			tmp1 = edx;
			edx = ebx;
			ebx = tmp1;

			tmp1 = dword_52CB98;
			dword_52CB98 = dword_52CB4C;
			dword_52CB4C = tmp1;

			tmp1 = _someStruct.i104;
			_someStruct.i104 = dword_52CB88;
			dword_52CB88 = tmp1;

			tmp1 = dword_52CB5C;
			dword_52CB5C = dword_52CB9C;
			dword_52CB9C = tmp1;

			edi += 4; // should be 16 in byte
		}
		
		esi = ebx;
		esi = floor((float) esi / 16);
		eax = edx;
		eax = floor((float) eax / 16);

		esi -= eax;

		if (esi > 0) {
			if (edx < dword_5202CC)
				dword_5202CC = edx;

			if (ebx > dword_52CBA0)
				dword_52CBA0 = ebx;

			ebx -= edx;
			eax *= 8; // normally 32 but because pointer arithmetic...
			edi += eax;

			auto dword_52CB58 = 0;
			if (dword_52CB98 != dword_52CB4C) {
				auto r = dword_52CB98 - dword_52CB4C;
				r <<= 15;
				r /= esi;
				r = (r << 17) | ((unsigned int) r >> 15);
				dword_52CB58 = r;
			}

			auto dword_52CB6C = 0;
			if (_someStruct.i104 != dword_52CB88) {
				auto r = _someStruct.i104 - dword_52CB88;
				r <<= 15;
				r /= esi;
				r = (r << 17) | ((unsigned int)r >> 15);
				dword_52CB6C = r;	
			}

			auto dword_52CB64 = 0;
			if (dword_52CB5C != dword_52CB9C) {
				auto r = dword_52CB5C - dword_52CB9C;
				r <<= 15;
				r /= esi;
				r = (r << 17) | ((unsigned int)r >> 15);
				dword_52CB64 = r;
			}

			ecx -= ebp;

			eax = ecx;
			eax <<= 16;
			eax /= ebx;

			ecx = ebp;
			ecx <<= 28;
			ecx = (ecx & 0xffff0000) | (dword_52CB9C & 0xffff);
			dword_52CB9C = ecx;

			ebp = floor((float) ebp / 16);

			auto dword_52CB68 = esi;
			esi = dword_52CB58;
			ebx = dword_52CB6C;
			ecx = dword_52CB64;
			esi = (esi << 16) | ((unsigned int) esi >> 16);
			ebx = (ebx << 16) | ((unsigned int) ebx >> 16);
			ecx = (ecx << 16) | ((unsigned int) ecx >> 16);

			edx = (edx & 0xffff0000) | (eax & 0xffff);
			eax = (eax & 0xffff0000) | (esi & 0xffff);
			esi = (esi & 0xffff0000) | (ebx & 0xffff);
			ebx = (ebx & 0xffff0000) | (ecx & 0xffff);
			ecx = (ecx & 0xffff0000) | (edx & 0xffff);

			eax = (eax << 16) | ((unsigned int) eax >> 16);
			esi = (esi << 16) | ((unsigned int) esi >> 16);
			ebx = (ebx << 16) | ((unsigned int) ebx >> 16);
			ecx = (ecx << 16) | ((unsigned int) ecx >> 16);

			_someStruct.i100 = eax;
			auto dword_5202C8 = ecx;

			auto temp = ebx;
			ebx = dword_52CB68;
			dword_52CB68 = temp;

			ecx = dword_52CB4C;
			edx = dword_52CB88;
			eax = dword_52CB9C;

			do {
				edi[0] = (edi[0] & 0xffff0000) | (ebp & 0xffff);
				edi[1] = (edi[1] & 0xffff0000) | (ecx & 0xffff);
				edi[2] = (edi[2] & 0xffff0000) | (edx & 0xffff);
				edi[3] = (edi[3] & 0xffff0000) | (eax & 0xffff);
				edi += 8; // normally 32

				unsigned long long carryHelper = (unsigned long long) (unsigned int) ebp + (unsigned int)_someStruct.i100;
				int cf = (carryHelper >> 32) & 1;
				ebp = (int) carryHelper;

				carryHelper = (unsigned long long) (unsigned int) ecx + (unsigned int) esi + cf;
				cf = (carryHelper >> 32) & 1;
				ecx = (int) carryHelper;

				carryHelper = (unsigned long long) (unsigned int) edx + (unsigned int) dword_52CB68 + cf;
				cf = (carryHelper >> 32) & 1;
				edx = (int) carryHelper;

				carryHelper = (unsigned long long) (unsigned int) eax + (unsigned int) dword_5202C8 + cf;
				cf = (carryHelper >> 32) & 1;
				eax = (int) carryHelper;

				ebp += cf; // Check here again later
			} while (--ebx > 0);	
		}

	aTop:
		ebp = dword_52CB60[0];
		edx = dword_52CB60[1];
		dword_52CB9C = dword_52CB60[2];
		dword_52CB60 += 3; // normally 12
		dword_52CB4C = _someStruct.i88[0];
		dword_52CB88 = _someStruct.i88[1];
		_someStruct.i88 += 2; // normally 8
		dword_52CB74--;

		if (dword_52CB74 > 0)
			goto top;

		ecx = _someStruct.i12;
		ebx = _someStruct.i16;
		dword_52CB5C = _someStruct.i20;
		dword_52CB98 = _someStruct.i84[0];
		_someStruct.i104 = _someStruct.i84[1];

		if (dword_52CB74 >= 0)
			goto bottom;

		dword_5202CC = floor((float) dword_5202CC / 16);
		dword_52CBA0 = floor((float) dword_52CBA0 / 16);

		auto dword_52CB50 = _someStruct.i76_textureSet;
		auto dword_5202D0 = _someStruct.i80;

		ebx = dword_52CBA0;
		ebx -= dword_5202CC;

		if (ebx > 0) {
			auto dword_52CB68 = ebx;
			_someStruct.i100 = (int) (dword_5202CC * _someStruct.i4 + _someStruct.i0);
			auto dword_5202C8 = _someStruct.i112 + 8 * dword_5202CC; // normally 32

			do {
				ebx = dword_5202C8[0];
				unsigned char * edi = (unsigned char *) dword_5202C8[4];
				ebx -= dword_5202C8[4];

				if (ebx > 0) {
					edi += _someStruct.i100;
					auto dword_52CB64 = (256 * (dword_5202C8[7] - dword_5202C8[3])) / ebx;
					ebp = (256 * (dword_5202C8[6] - dword_5202C8[2])) / ebx;
					
					edx = dword_5202C8[2];
					esi = (256 * (dword_5202C8[5] - dword_5202C8[1])) / ebx;
					auto dword_52CB48 = edi;

					edi += ebx;
					auto dword_52CB78 = ebx;

					auto ebx = dword_5202D0;
					ebx = (unsigned char*) (((uintptr_t) ebx & 0xffff00ff) | (dword_5202C8[3] & 0xff00));
					_someStruct.i92 = (_someStruct.i92 & 0xffff00ff) | ((dword_5202C8[3] & 0xff) << 8);

					eax = dword_52CB64;

					short word_52CB7C = (short) eax;
					eax = ((unsigned int) eax >> 16) | (eax << 16);

					_someStruct.i108 = (_someStruct.i108 & 0xffffff00) | (unsigned char) eax;

					auto eax = dword_52CB50;
					eax = (unsigned char*) (((uintptr_t) eax & 0xffffff00) | ((dword_5202C8[1] >> 8) & 0xff));
					eax = (unsigned char*) (((uintptr_t) eax & 0xffff00ff) | (edx & 0xff00));

					int tmp = ecx;
					ecx = esi;
					esi = tmp;

					tmp = edx;
					edx = ebp;
					ebp = tmp;

					ecx = ((unsigned int) ecx >> 16) | (ecx << 16);
					edx = ((unsigned int) edx >> 16) | (edx << 16);

					ecx = (ecx & 0xffff00ff) | ((edx & 0xff) << 8);
					edx &= 0xffff0000;

					ebp = ((unsigned int) ebp >> 8) | (ebp << 24);
					esi = ((unsigned int) esi >> 8) | (esi << 24);

					auto dword_52CB8C = edx;
					ebp = (ebp & 0xffff0000) | (unsigned short) _someStruct.i92;
					edx = dword_52CB78 & 0xffff;

					do {
						ebx = (unsigned char*) (((uintptr_t) ebx & 0xffffff00) | *(unsigned char*) eax);
						ebx = (unsigned char*) (((uintptr_t) ebx & 0xffffff00) | *(unsigned char*) ebx);

						unsigned long long carryHelper = (unsigned long long) (unsigned int) esi + (unsigned int) ecx;
						int cf = (carryHelper >> 32) & 1;
						esi = (int) carryHelper;

						eax = (unsigned char*) (((uintptr_t) eax & 0xffffff00) | (((uintptr_t) eax & 0xff) + (ecx & 0xff) + cf) & 0xFF);

						carryHelper = (unsigned long long) (unsigned int)ebp + (unsigned int)dword_52CB8C;
						cf = (carryHelper >> 32) & 1;
						ebp = (int) carryHelper;

						eax = (unsigned char*) (((uintptr_t) eax & 0xffff00ff) | (((uintptr_t)eax & 0xff00) + (ecx & 0xff00) + (cf << 8)) & 0xff00);

						carryHelper = (unsigned long long) (unsigned int) (ebp & 0xffff) + (unsigned short) word_52CB7C;
						cf = (carryHelper >> 16) & 1;
						ebp = (ebp & 0xffff0000) | (unsigned short) carryHelper;

						ebx = (unsigned char*) (((uintptr_t) ebx & 0xffff00ff) | (((uintptr_t) ebx & 0xff00) + ((_someStruct.i108 & 0xff) << 8) + (cf << 8)) & 0xff00);

						edi--;

						*edi = (unsigned char) ebx;

					} while (--edx > 0);

				}

				_someStruct.i100 += _someStruct.i4;
				dword_5202C8 += 8; // normally 32
				dword_52CB68--;
			} while (dword_52CB68 > 0);
		}
}
