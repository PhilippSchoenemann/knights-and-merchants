#include "AnimationEntry.h"
#include "io/FileIo.h"

using std::fill_n;

constexpr short UNUSED_FRAME = -1;

AnimationEntry::AnimationEntry()
        : i60_frameCount { }, i62 { }, i66 { }
{
    i0_frames.fill(UNUSED_FRAME);
}

void AnimationEntry::read(knights_and_merchants::io::FileIo & fileIo)
{
    for (short & i0_frame: i0_frames)
        fileIo.read(&i0_frame, 2);

    fileIo.read(&i60_frameCount, 2);
    fileIo.read(&i62, 4);
    fileIo.read(&i66, 4);
}
