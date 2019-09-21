#pragma once
#include <libDSP/Modules/DSPModule.h>

class DrumModule : public DSPModule {
public:
  DrumModule(DSPHost *parent);
  const char *TYPE() const override;
  void tick() override;

  void setBaseFrequency(float  frequency);
protected:
    const Output* m_audioOut;
    const Input* m_hitIn;
    const Input* m_resetIn;
};
