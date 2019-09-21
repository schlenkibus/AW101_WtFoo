#pragma once

#include "Frame.h"
#include <libDSP/>

class AudioDevice {
public:
    using tBuffer = RingBuffer<Frame, DSPInfo::FramesPerBuffer * 100>;

    explicit AudioDevice(DSPHost& dspHost);

    void onRequestBuffer(int framesInBuffer);
    void requestFrame(Frame& frame);
    virtual bool initialized() = 0;

    const tBuffer& getRingBuffer() const;

  private:
  DSPHost& m_dspHost;
    tBuffer m_ringBuffer;
};
