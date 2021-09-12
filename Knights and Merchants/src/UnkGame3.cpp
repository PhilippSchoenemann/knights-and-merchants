#include "UnkGame3.h"

UnkGame3 * UnkGame3::instance;

int UnkGame3::unk_536A0C[64][4][8];

UnkGame3::UnkGame3()
{
	int esi = 0;
	auto eaxx = unk_536A0C;

	for (int i = 0; i < 8; ++i) {
		int edi = esi + 0x1fff;
		int ecx = 0;

		for (int j = 0; j < 8; ++j) {
			int (& eax)[4][8] = *eaxx;

			eax[0][0] = ecx;
			eax[0][1] = esi;
			eax[0][2] = ecx + 0x1f00;
			eax[0][3] = edi;
			eax[0][4] = ecx;
			eax[0][5] = edi;
			eax[0][6] = ecx + 0x1f00;
			eax[0][7] = esi;

			eax[1][0] = ecx;
			eax[1][1] = edi;
			eax[1][2] = eax[0][6];
			eax[1][3] = esi;
			eax[1][4] = eax[0][2];
			eax[1][5] = edi;
			eax[1][6] = ecx;
			eax[1][7] = esi;

			eax[2][0] = eax[0][2];
			eax[2][1] = edi;
			eax[2][2] = ecx;
			eax[2][3] = esi;
			eax[2][4] = eax[0][6];
			eax[2][5] = esi;
			eax[2][6] = ecx;
			eax[2][7] = edi;

			eax[3][0] = eax[0][6];
			eax[3][1] = esi;
			eax[3][2] = ecx;
			eax[3][3] = edi;
			eax[3][4] = ecx;
			eax[3][5] = esi;
			eax[3][6] = eax[0][2];
			eax[3][7] = edi;

			eaxx++;
			ecx += 0x2000;
		}

		esi += 0x2000;
	}
}

UnkGame3::~UnkGame3()
{

}