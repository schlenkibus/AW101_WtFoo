#pragma once
#include <libDSP/include/Modules/DSPModule.h>
#include <libDSP/include/misc/Countdown.h>

class RampModule : public DSPModule {
public:
  explicit RampModule(DSPHost *parent);
  void tick() override;
  void reset() override;
  const char *getName() override;

private:
    Output* m_out;
    Input* m_hit;
    Parameter* m_time;

    long curr;
    long target;
    bool m_running = false;
};
