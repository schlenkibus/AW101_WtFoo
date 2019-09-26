#pragma once
#include <libDSP/include/Modules/DSPModule.h>
#include <libDSP/include/misc/Countdown.h>

class RampModule : public DSPModule {
public:
  explicit RampModule(DSPHost *parent);
  const char *TYPE() const override;
  void tick() override;
  void reset() override;

private:
    Output* m_out;
    Input* m_reset;
    Input* m_hit;
    Parameter* m_start;
    Parameter* m_end;
    Parameter* m_time;

    long curr;
    long target;
    bool m_running = false;
};
