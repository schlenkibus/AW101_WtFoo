#include "RampModule.h"
#include <libDSP/include/libDSP.h>

RampModule::RampModule(DSPHost *parent) : DSPModule(parent) {
  createParameter("Time (s)", 0.5, 0, 2.0, 4);
  createInput("HIT");
  createOutput("OUT");

  m_out = findOutput("OUT");
  m_time = findParameter("Time (s)");
  m_hit = findInput("HIT");
}

const char *RampModule::TYPE() const { return "RampModule"; }

void RampModule::tick() {
  DSPContainer::tick();

  if (!m_running && m_hit->getSignal() != 0) {
    curr = 0;
    m_running = true;
    reset();
    return;
  }

  if (m_running && m_hit->getSignal() == 0) {
    if (curr >= target) {
      m_running = false;
    } else {
      curr++;
    }
  } else {
    m_out->set(0);
    return;
  }

  auto val = static_cast<float>(target) / curr;
  m_out->set(val);
}

void RampModule::reset() {
  DSPNode::reset();
  target = static_cast<long>(DSPInfo::SampleRate * m_time->getValue());
}
