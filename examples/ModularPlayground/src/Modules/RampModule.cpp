#include "RampModule.h"
#include <libDSP/include/libDSP.h>

RampModule::RampModule(DSPHost *parent) : DSPModule(parent)
{
  createParameter("Time (s)", 0.5, 0, 1.0, 2);
  createParameter("Start", 1.0, 0.0, 1.0, 2);
  createParameter("End", 0, 0.0, 1.0, 2);
  createInput("HIT");
  createInput("RESET");
  createOutput("OUT");

  m_out = findOutput("OUT");
  m_end = findParameter("End");
  m_start = findParameter("Start");
  m_time = findParameter("Time (s)");
  m_hit = findInput("HIT");
  m_reset = findInput("RESET");
}

const char *RampModule::TYPE() const { return "RampModule"; }

void RampModule::tick() {
  DSPContainer::tick();

  if(m_reset->getSignal() != 0) {
    reset();
    m_out->set(0);
    return;
  }

  if(m_running) {
    if(curr >= target) {
      reset();
      m_running = false;
    } else {
      curr++;
      auto percent = static_cast<float>(target) / curr;
      auto val = m_start->getValue() + ((m_end->getValue() - m_start->getValue()) * percent);
      m_out->set(val);
    }
  } else {
    if(m_hit->getSignal() != 0) {
      curr = 0;
      m_running = true;
    }
  }
}

void RampModule::reset() {
  DSPNode::reset();

  target = static_cast<long>(DSPInfo::SampleRate * m_time->getValue());
  m_out->set(0);
}
