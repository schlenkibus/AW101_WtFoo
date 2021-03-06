#include "SequencerModule.h"

SequencerModule::SequencerModule(DSPHost *parent)
    : DSPModule(parent)
{
  m_input = createInput("Tick");
  m_output = createOutput("Out");

  for(auto i = 0; i < m_stepValues.size(); i++)
  {
    createParameter(std::to_string(i), 0, 0, 1.0, 3);
  }

  for(auto i = 0; i < m_stepValues.size(); i++)
  {
    m_stepValues[i] = findParameter(std::to_string(i));
  }
}

void SequencerModule::tickInternals()
{
  if(m_input->getSignal() > 0.0 && !stepped)
  {
    if(m_currentIndex == m_stepValues.size())
    {
      m_currentIndex = 0;
    }

    auto val = m_stepValues[m_currentIndex++]->getValue();
    m_output->setSignal(val);
    stepped = true;
  }
  else if(m_input->getSignal() <= 0.0 && stepped)
  {
    stepped = false;
  }
}
