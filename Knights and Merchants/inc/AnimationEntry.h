#ifndef KNIGHTS_AND_MERCHANTS_ANIMATION_ENTRY_H
#define KNIGHTS_AND_MERCHANTS_ANIMATION_ENTRY_H

#include <array>

namespace knights_and_merchants::io
{
    class FileIo;
}

class AnimationEntry
{
public:
    AnimationEntry();

    virtual ~AnimationEntry() = default;

    void virtual read(knights_and_merchants::io::FileIo & fileIo);

    std::array<short, 30> i0_frames;
    short i60_frameCount;
    int i62;
    int i66;
};

#endif