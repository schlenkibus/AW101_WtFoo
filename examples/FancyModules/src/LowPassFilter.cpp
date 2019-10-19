
#include <libDSP/include/DSPHost.h>
#include <cmath>
#include <libDSP/include/libDSP.h>
#include "LowPassFilter.h"


LowPassFilter::LowPassFilter(DSPHost *parent)
    : DSPModule(parent)
{
  createInput("Cutoff");
  createInput("Resonance");
  m_in = createInput("In");
  m_cutoff = findInput("Cutoff");
  m_resonance = findInput("Resonance");
  m_out = createOutput("Out");

  init();
}

void LowPassFilter::tick()
{
  DSPContainer::tick();

  if(cutOffFrequency != m_cutoff->getSignal()) {
    init();
  }

  if(resonance != m_resonance->getSignal()) {
    init();
  }

  buff1 = buff1 + cutOffFrequency * (m_in->getSignal() - buff1 + feedBack * (buff1 - buff2));
  buff2 = buff2 + cutOffFrequency * (buff1 - buff2);
  m_out->set(buff1);
}

const char* LowPassFilter::getName()
{
  return "Low Pass Filter";
}

void LowPassFilter::init()
{
  cutOffFrequency = std::max<float>(m_cutoff->getSignal(), 0.01);
  resonance = std::max<float>(m_resonance->getSignal(), 0);

  feedBack = resonance + resonance / (1.0 - cutOffFrequency);

  auto delta = 1.0 / DSPInfo::SampleRate;
  ePow = 1- std::exp(-delta * cutOffFrequency);
}
