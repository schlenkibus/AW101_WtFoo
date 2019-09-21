#pragma once
#include "../../LibDSP/Modules/DSPModule.h"
#include "../../Mixer/Audio/DrumKit.h"

class DrumModule : public DSPModule {
public:
  DrumModule();
  const char *TYPE() const override;
  void tick() override;

  void setBaseFrequency(float  frequency);
protected:
    DrumKit* m_drumKit; //Placeholder
    const Output* m_audioOut;
    const Input* m_hitIn;
    const Input* m_resetIn;
};
