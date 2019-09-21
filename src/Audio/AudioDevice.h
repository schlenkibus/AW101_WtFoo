#pragma once

#include "../DSPNodes/DSPInfo.h"
#include "../DSPNodes/DSPInputNode.h"
#include "../DSPNodes/DSPOutputNode.h"
#include "../misc/RingBuffer.h"
#include "Frame.h"

class ModularPlaygroundApplication;

class AudioDevice {
public:
    using tBuffer = RingBuffer<Frame, DSPInfo::FramesPerBuffer * 100>;

    explicit AudioDevice(ModularPlaygroundApplication& exitNode);

    void onRequestBuffer(int framesInBuffer);
    void requestFrame(Frame& frame);
    virtual bool initialized() = 0;

    const tBuffer& getRingBuffer() const;

  private:
    ModularPlaygroundApplication& m_dspApplication;
    tBuffer m_ringBuffer;
};
