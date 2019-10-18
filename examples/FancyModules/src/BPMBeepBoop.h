#pragma once
#include <libDSP/include/Modules/DSPModule.h>

class BPMBeepBoop : public DSPModule
{
 public:
  explicit BPMBeepBoop(DSPHost *parent);
  void tick() override;

  void updateBPM();
  const char* getName() override;

 private:
  Parameter* m_bpm;

  int m_cachedBPM{};

  std::array<int, 10> m_scales;
  std::array<long, 10> m_clockTargets{};
  std::array<long, 10> m_clockTicks{};
};