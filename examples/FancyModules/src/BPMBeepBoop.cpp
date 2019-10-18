#include <libDSP/include/libDSP.h>
#include "BPMBeepBoop.h"

BPMBeepBoop::BPMBeepBoop(DSPHost* parent)
    : DSPModule(parent)
    , m_scales { 1, 2, 3, 4, 5, 6, 8, 16, 32, 64 }
{
  m_bpm = createParameter("BPM", 130, 5, 300, 1);

  for(auto& s : m_scales)
    createOutput("1/" + std::to_string(s));

  updateBPM();
}
const char* BPMBeepBoop::getName()
{
  return "BPMBeepBoop";
}

void BPMBeepBoop::updateBPM()
{
  if(m_cachedBPM != m_bpm->getValue())
  {
    m_cachedBPM = static_cast<int>(m_bpm->getValue());
    for(auto i = 0; i < m_clockTargets.size(); i++)
    {
      auto bps = m_cachedBPM / 60.0;
      auto scaled = bps / m_scales[i];
      auto ticksPerBeat = scaled * DSPInfo::SampleRate;
      m_clockTargets[i] = ticksPerBeat;
    }
  }
}

void BPMBeepBoop::tick()
{
  DSPContainer::tick();

  updateBPM();

  int i = 0;
  for(auto& o : m_outputs)
  {
    m_clockTicks[i]++;
    auto value = m_clockTicks[i] >= m_clockTargets[i];
    o.set(value);
    if(value)
    {
      m_clockTicks[i] = 0;
    }
    i++;
  }
}
