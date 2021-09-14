#ifndef KNIGHTS_AND_MERCHANTS_NETWORKCLASS_H
#define KNIGHTS_AND_MERCHANTS_NETWORKCLASS_H

#include "initguid.h"
#include <dplay.h>
#include "utilities/DoublyLinkedList.h"

class NetworkClass
{
public:
    NetworkClass(LPGUID p0);
    ~NetworkClass();

    void reset();

    LPGUID i0;
    LPDIRECTPLAY2A i4;
    void * i8;
    DPID i12;
    short i16;
    short i18;
    knights_and_merchants::utilities::DoublyLinkedList<void *> i20;
    knights_and_merchants::utilities::DoublyLinkedList<void *> i32;
    int i44;
    int i48;
    void * i52;
    HRESULT i56;
    int i60;
    void * i64;

    void unk1();

    void unk2();

    void unk3();
    void unk9();

    bool unk10(int p0);

    void unk11();
};

#endif
