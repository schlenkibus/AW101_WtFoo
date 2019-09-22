#pragma once
#include "AudioDevice.h"
#include <portaudio.h>

class PortAudioDevice : public AudioDevice {
public:
  PortAudioDevice(int sampleRate, int framesPerBuffer);
  bool initialized() override;
protected:
  PaStream* m_stream{nullptr};
};
