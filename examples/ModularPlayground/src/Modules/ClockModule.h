#pragma once
#include <libDSP/include/Modules/DSPModule.h>
#include <libDSP/include/misc/Countdown.h>

class ClockModule : public DSPModule {
public:
  explicit ClockModule(DSPHost *parent);
  const char *TYPE() const override;
  void tick() override;

private:
  bool state = false;
    Parameter* m_ticksPerCycle;
    Output* m_clockOut;
    Input* m_runningInput;
    Countdown<int> m_countdown;
};
