#pragma once
#include <libDSP/include/Modules/DSPModule.h>
#include <libDSP/include/misc/Countdown.h>

class ClockModule : public DSPModule {
public:
  explicit ClockModule(DSPHost *parent);
  void tick() override;
  const char *getName() override;

private:
  Parameter *m_cycleLength;
  Output *m_clockOut;
  Input *m_runningInput;
  Countdown<int> m_countdown;
};
