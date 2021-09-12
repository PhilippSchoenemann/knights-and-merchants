#include "AnimationEntryEx.h"
#include "io/FileIo.h"

void AnimationEntryEx::read(knights_and_merchants::io::FileIo & fileIo)
{
	AnimationEntry::read(fileIo);

    fileIo.read(&i70, 4);
    fileIo.read(&i74, 4);
    fileIo.read(&i78, 4);
    fileIo.read(&i82, 4);
    fileIo.read(&i86, 4);
    fileIo.read(&i90, 4);
    fileIo.read(&i94, 1);
    fileIo.read(&i95, 4);
}