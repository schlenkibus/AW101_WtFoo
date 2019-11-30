#include <libDSP/include/libDSP.h>
#include "BPMBeepBoop.h"

BPMBeepBoop::BPMBeepBoop(DSPHost* parent)
    : DSPModule(parent)
    , m_scales { -1, 1, 2, 3, 4, 5, 6, 8, 16, 32, 64 }
{
  m_bpm = createParameter("BPM", 130, 5, 300, 1);

  for(auto& s : m_scales)
    if(s < 0)
      createOutput(std::to_string(s * -2) + "/1");
    else
      createOutput("1/" + std::to_string(s));

  updateBPM();
}

void BPMBeepBoop::updateBPM()
{
  if(m_cachedBPM != m_bpm->getValue())
  {
    m_cachedBPM = static_cast<int>(m_bpm->getValue());
    for(auto i = 0; i < m_clockTargets.size(); i++)
    {
      auto bps = 60.0 / m_cachedBPM;
      float scale = m_scales[i];
      if(scale < 0)
        scale = (scale * -1) / 2;
      auto scaled = bps / scale;
      auto ticksPerBeat = scaled * DSPInfo::SampleRate;
      m_clockTargets[i] = ticksPerBeat;
    }
  }
}

void BPMBeepBoop::tickInternals()
{
  updateBPM();

  int i = 0;
  for(auto& o : m_outputs)
  {
    m_clockTicks[i]++;
    auto value = m_clockTicks[i] >= m_clockTargets[i];
    o->setSignal(value);
    if(value)
    {
      m_clockTicks[i] = 0;
    }
    i++;
  }
}
