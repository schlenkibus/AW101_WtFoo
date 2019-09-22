#pragma once
#include "AudioDevice.h"
#include <portaudio.h>

class PortAudioDevice : public AudioDevice {
public:
  PortAudioDevice(int sampleRate, int framesPerBuffer);
  bool initialized() override;
  void onRequestBuffer(int framesInBuffer) override;
  void requestFrame(Frame &frame) override;

protected:
  PaStream* m_stream{nullptr};
};
