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
    Parameter* m_attackTime;
    Parameter* m_releaseTime;
    Parameter* m_topGain;

    long curr;
    long targetTop;
    long targetEnd;
    bool m_running = false;
    bool m_inDecay = false;
};
