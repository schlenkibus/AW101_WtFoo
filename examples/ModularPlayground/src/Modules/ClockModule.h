#pragma once
#include <libDSP/include/Modules/DSPModule.h>
#include <libDSP/include/misc/Countdown.h>

class ClockModule : public DSPModule {
public:
  explicit ClockModule(DSPHost *parent, bool slow);
  void tick() override;

 private:
  Parameter *m_cycleLength;
  Output *m_clockOut;
  Input *m_runningInput;
  Countdown<int> m_countdown;
};

class AlternatingClock : public DSPModule {
public:
    explicit AlternatingClock(DSPHost* parent);
    void tick() override;

   private:
    Parameter* m_cycleLength;
    Output* m_clockOut;
    Countdown<long> m_countdown;

    bool high = false;
};
