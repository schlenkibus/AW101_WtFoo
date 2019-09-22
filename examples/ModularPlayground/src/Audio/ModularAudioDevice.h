#pragma once
#include <examples/ModularPlayground/src/ModularPlaygroundApplication.h>
#include <libAudio/include/PortAudioDevice.h>

class ModularAudioDevice : public PortAudioDevice {
public:
    explicit ModularAudioDevice(ModularPlaygroundApplication* application, int sampleRate, int framesPerBuffer);
    void onRequestBuffer(int framesInBuffer) override;
    void requestFrame(Frame &frame) override;

  private:
    ModularPlaygroundApplication* m_app;
};
