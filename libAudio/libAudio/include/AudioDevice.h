#pragma once
#include "Frame.h"

class AudioDevice {
public:
    virtual void onRequestBuffer(int framesInBuffer) = 0;
    virtual void requestFrame(Frame& frame) = 0;
    virtual bool initialized() = 0;
};
