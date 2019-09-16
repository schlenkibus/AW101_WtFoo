#pragma once

#include "Frame.h"
#include "../DSPNodes/DSPContainer.h"
#include "../DSPNodes/DSPInfo.h"
#include "../misc/RingBuffer.h"

class AudioDevice {
public:
    using tBuffer = RingBuffer<Frame, DSPInfo::FramesPerBuffer * 100>;

    explicit AudioDevice(DSPContainer& host);

    void onRequestBuffer(int framesInBuffer);
    void requestFrame(Frame& frame);
    virtual bool initialized() = 0;

    const tBuffer& getRingBuffer() const;

  private:
    DSPContainer& m_hostContainer;
    tBuffer m_ringBuffer;
};
