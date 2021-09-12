#pragma once
#include <Windows.h>

namespace knights_and_merchants {
    namespace text {
        class Lib;
    }

    namespace graphics
    {
        class DrawableSurface;
    }
}

class UnkGame1;

struct unk {
	int width;
	int height;
	int i8;
	int i12;
	int i16;
	int i20;
	int i24;
	int i28;
};

struct anoUnk {
	short i0;
	short i2;
	short i4;
	short i6;
	short i8;
};

extern unk screenConstants[];

extern anoUnk word_4982C0[];

// InGame globals



extern int dword_53BC94;
extern int dword_53BC98;
extern int dword_53C57C;

extern char soundFileNames[16][30];
extern char actionNames[13][30];

extern unsigned char byte_53998A[8]; // Map colors of players.

extern HINSTANCE base_hInstance;

extern HWND base_hWnd;

extern knights_and_merchants::text::Lib* base_Lib_Setup;

extern char globals_gameState;

extern void showVideo(const char*);

extern void clearScreen(knights_and_merchants::graphics::DrawableSurface& str);

extern  void sub_4015C8();