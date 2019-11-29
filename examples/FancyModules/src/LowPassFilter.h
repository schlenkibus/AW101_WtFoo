#pragma once
#include <libDSP/include/Modules/DSPModule.h>

class LowPassFilter : public DSPModule
{
 public:
  explicit LowPassFilter(DSPHost* parent);
  void tick() override;

 private:
  float cutOffFrequency{0};
  float resonance{0};
  float buff1{0};
  float buff2{0};
  float ePow{0};

  Input* m_cutoff;
  Input* m_resonance;
  Output* m_out;
  Input* m_in;

  float feedBack{0};

  void init();
};