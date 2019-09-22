#pragma once
#include "WaveTableOscillator.h"
#include <libDSP/include/Modules/DSPModule.h>

class SineOscillatorModule : public DSPModule {
public:
  explicit SineOscillatorModule(DSPHost *host);
  const char *TYPE() const override;
  void tick() override;

private:
  WaveTableOscillator<SineWaveTable<4096>> m_osc;
  Output *m_signalOut;
  Input *m_frequencyIn;
  Input *m_resetIn;

  Parameter* m_baseFrequency;
  Parameter* m_frequencyRange;
};