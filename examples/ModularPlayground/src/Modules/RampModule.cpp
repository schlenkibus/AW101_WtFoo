#include "RampModule.h"
#include <libDSP/include/libDSP.h>

RampModule::RampModule(DSPHost *parent)
    : DSPModule(parent)
{
  createParameter("Top Gain", 1.0, 0.0, 1.0, 2);
  createParameter("Attack Time (s)", 0.5, 0.001, 2.0, 4);
  createParameter("Release Time (s)", 0.5, 0.001, 2.0, 4);

  createInput("Trigger");
  createOutput("Ramp");

  m_topGain = findParameter("Top Gain");
  m_attackTime = findParameter("Attack Time (s)");
  m_releaseTime = findParameter("Release Time (s)");

  m_hit = findInput("Trigger");
  m_out = findOutput("Ramp");
}

void RampModule::tick()
{
  DSPContainer::tick();

  if(!m_running && m_hit->getSignal() != 0)
  {
    curr = 0;
    m_running = true;
    m_inDecay = false;
    reset();
    return;
  }

  if(m_running)
  {
    if(m_inDecay && curr >= targetEnd)
    {
      m_running = false;
      m_inDecay = false;
    }
    else if(!m_inDecay && curr >= targetTop)
    {
      targetEnd = static_cast<long>(DSPInfo::SampleRate * m_releaseTime->getValue());
      m_inDecay = true;
      curr = 0;
    }
    else
    {
      curr++;
    }
  }
  else
  {
    m_out->set(0);
    return;
  }

  if(m_inDecay)
  {
    auto val = m_topGain->getValue() - m_topGain->getValue() * (curr / static_cast<float>(targetEnd));
    m_out->set(val);
  }
  else
  {
    auto val = m_topGain->getValue() * (static_cast<float>(targetTop) / (curr));
    m_out->set(val);
  }
}

void RampModule::reset()
{
  DSPNode::reset();

  targetTop = static_cast<long>(DSPInfo::SampleRate * m_attackTime->getValue());
  targetEnd = static_cast<long>(DSPInfo::SampleRate * m_releaseTime->getValue());
}
const char *RampModule::getName()
{
  return "Ramp Module";
}
