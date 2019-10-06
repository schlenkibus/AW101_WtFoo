#include "ClockModule.h"
#include <libDSP/include/DSPInfo.h>

ClockModule::ClockModule(DSPHost *parent, bool slow)
    : DSPModule(parent), m_countdown{100} {
  m_runningInput = createInput("Active In");
  m_clockOut = createOutput("Clock Out");
  if(slow)
    m_cycleLength = createParameter("Cycle Length", 1, DSPInfo::SampleRate / 10, DSPInfo::SampleRate * 20, 0);
  else
    m_cycleLength = createParameter("Cycle Length", 1, 1, DSPInfo::SampleRate / 10, 0);
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
const char *ClockModule::getName() { return "Clock Module"; }

AlternatingClock::AlternatingClock(DSPHost *parent) : DSPModule(parent), m_countdown{50} {
  m_clockOut = createOutput("Out");
  m_cycleLength = createParameter("Lenght", 1, 1, DSPInfo::SampleRate * 10, 0);
}


void AlternatingClock::tick() {
  DSPContainer::tick();

  m_countdown.setLength(static_cast<int>(m_cycleLength->getValue()));

  if (!m_countdown.tick_check()) {
    m_clockOut->set(high ? 1.0 : 0.0);
    m_countdown.reset();
    high = !high;
  }
}

const char* AlternatingClock::getName() {
  return "Alternating Clock Module";
}