#include "ClockModule.h"
#include <libDSP/include/DSPInfo.h>

ClockModule::ClockModule(DSPHost *parent)
    : DSPModule(parent), m_countdown{100} {
  m_runningInput = createInput("Active In");
  m_clockOut = createOutput("Clock Out");
  m_cycleLength = createParameter("Cycle Length", 1, 1, DSPInfo::SampleRate, 0);
}

void ClockModule::tick() {
  DSPContainer::tick();

  m_countdown.setLength(static_cast<int>(m_cycleLength->getValue()));

  if (m_runningInput->getSignal() > 0.0) {
    if (!m_countdown.tick_check()) {
      m_clockOut->set(1.0);
      m_countdown.reset();
    } else {
      m_clockOut->set(0.0);
    }
  }
}
