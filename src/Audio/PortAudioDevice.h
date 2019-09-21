#pragma once
#include "AudioDevice.h"
#include <portaudio.h>

class ModularPlaygroundApplication;

class PortAudioDevice : public AudioDevice {
public:
  PortAudioDevice(ModularPlaygroundApplication& host, int sampleRate, int framesPerBuffer);
  bool initialized() override;

protected:
    PaStream* m_stream{nullptr};
};
