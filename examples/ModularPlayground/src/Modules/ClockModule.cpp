#include "ClockModule.h"
#include <libDSP/include/DSPInfo.h>

const char *ClockModule::TYPE() const { return "ClockModule"; }

ClockModule::ClockModule(DSPHost *parent) : DSPModule(parent), m_countdown{100} {
  m_runningInput = createInput("ON");
  m_clockOut = createOutput("CLK");
  m_ticksPerCycle = createParameter("TICKS", 100, 1, DSPInfo::SampleRate * 10);
}

void ClockModule::tick() {
  DSPContainer::tick();

  m_countdown.setLength(static_cast<int>(m_ticksPerCycle->getValue()));

  if(m_runningInput->getSignal() >= 0.0) {
    if(m_countdown.tick_check()) {
      m_countdown.reset();
      state = !state;
      m_clockOut->set(state);
    }
  }
}
