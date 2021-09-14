#include "NetworkClass.h"
#include <cstdlib>

NetworkClass::NetworkClass(LPGUID p0)
{
    reset();
    LPDIRECTPLAY ldDp = nullptr;

    i0 = p0;
    i56 = DirectPlayCreate(p0, &ldDp, nullptr);

    if (i56 == DP_OK) {
        i56 = ldDp->QueryInterface(IID_IDirectPlay2A, reinterpret_cast<void **>(&i4));

        if (i56 != DP_OK) {
            unk11();
        }

        ldDp->Release();
    } else {
        unk11();
    }
}

void NetworkClass::reset()
{
    i4 = nullptr;
    i0 = nullptr;
    i48 = 0;
    i52 = 0;
    i8 = 0;
    i60 = 0;
    i16 = 0;
    i18 = 0;
    i44 = 0;
    i12 = DPID_UNKNOWN;
    i64 = 0;
}

NetworkClass::~NetworkClass()
{
    unk1();
    unk2();

    if (i4 != nullptr) {
        unk3();
        i4->Release();
    }

    if (i8 != nullptr) {
        free(i8);
    }

    if (i52 != nullptr) {
        free(i52);
    }

    if (i64 != nullptr) {
        free(i64);
    }

    reset();
}

void NetworkClass::unk1()
{
    if (i20.startIterateBegin()) {
        do {
            if (i20.getI4() != nullptr) {
                if (i20.unk002() != nullptr)
                    free(i20.unk002());

                //if (i20.unk001() != nullptr) TODO: Wirft noch einen Fehler
                //    free(i20.unk001());
            }
        } while (i20.moveNext());
    }

    i20.clear();
    i16 = 0;
}

void NetworkClass::unk2()
{
    if (i32.startIterateBegin()) {
        do {
            if (i32.getI4() != nullptr) {
                if (i32.unk002() != nullptr)
                    free(i32.unk002());
            }
        } while (i32.moveNext());
    }

    i32.clear();
    i18 = 0;
}

void NetworkClass::unk3()
{
    unk9();
    i4->Close();
}

void NetworkClass::unk9()
{
    unk10(i12);
}

bool NetworkClass::unk10(int p0)
{
    if (p0 == DPID_UNKNOWN)
        return true;

    i56 = i4->DestroyGroup(p0);

    if (i56 == DP_OK)
        return true;

    unk11();
    return false;
}

void NetworkClass::unk11()
{
    i60 = i56;
    // TODO: Reverse
}
