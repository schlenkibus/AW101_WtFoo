#pragma once

#include "../DSPNodes/DSPContainer.h"
class AudioDevice {
public:
    typedef struct Frame {
        double l;
        double r;
    } Frame;

    explicit AudioDevice(DSPContainer& host);

    void onRequestBuffer();
    void requestFrame(Frame& frame);
    virtual bool initialized() = 0;

  private:
    DSPContainer& m_hostContainer;
};
