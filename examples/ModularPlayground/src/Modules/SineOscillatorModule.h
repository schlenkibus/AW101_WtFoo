#pragma once
#include "WaveTableOscillator.h"
#include <libDSP/include/Modules/DSPModule.h>

class SineOscillatorModule : public DSPModule {
public:
  explicit SineOscillatorModule(DSPHost *host);
  const char *TYPE() const override;
  void tick() override;

  void setFrequencyBase(float baseFreq);
  void setFrequencyRange(float range);

  float getFrequencyBase() const;
  float getFrequencyRange() const;

private:
  WaveTableOscillator<SineWaveTable<4096>> m_osc;
  Output *m_signalOut;
  Input *m_frequencyIn;
  Input *m_resetIn;

  float m_baseFreqency = 440;
  float m_frequencyRange = 220;
};