#pragma once

#include "SoundStorage.h"
#include "Track.h"
#include <portaudio.h>

class DSPHost {
public:
  DSPHost();
  void tick();

  void setCrossFade(float mix);
  float getLeftChannelSignal();
  float getRightChannelSignal();
  bool running();

  void loadSound(const tPath& path);

private:
  PaStream *m_stream;
  Track m_track1;
  Track m_track2;

  float m_mainCrossFade{0.5};

  std::atomic_bool m_running{true};

  SoundStorage m_sounds;

  friend class DSPHostUserInterfaceApplication;
  friend class SamplePreviewWidget;
  friend class MixerWidget;
};
