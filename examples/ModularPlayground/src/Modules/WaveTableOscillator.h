#pragma once
#include "examples/ModularPlayground/src/WaveTables.h"
#include <iostream>
#include <libDSP/include/Modules/DSPModule.h>

template <class WaveTable> class WaveTableOscillator : public DSPModule
{
 public:
  explicit WaveTableOscillator(DSPHost *host);
  void tickInternals() override;
  void setFrequency(float frequency);
  float getFrequency() const;

 protected:
  float m_frequency { 440 };
  float m_phaseInc {};
  float m_phase { 0 };
  float m_offset { 0 };

  float m_signal { 0.0 };

  DSPOutputNode *m_output;

  WaveTable m_data;
};

template <class WaveTable>
WaveTableOscillator<WaveTable>::WaveTableOscillator(DSPHost *host)
    : DSPModule(host)
{
  setFrequency(80);
  m_output = createOutput("OUT");
}

template <class WaveTable> void WaveTableOscillator<WaveTable>::setFrequency(float frequency)
{
  if(m_frequency == frequency)
    return;

  m_frequency = frequency;
  m_phaseInc = m_frequency * static_cast<float>(m_data.getSize()) / DSPInfo::SampleRate;
}

template <class WaveTable> float WaveTableOscillator<WaveTable>::getFrequency() const
{
  return m_frequency;
}

template <class WaveTable> void WaveTableOscillator<WaveTable>::tickInternals()
{
  auto pos = m_phase + m_phaseInc;

  if(pos < m_data.getSize())
  {
    m_phase = pos;
  }
  else
  {
    auto tooMuch = pos - m_data.getSize() - 1;
    m_phase = tooMuch;
  }

  m_output->setSignal(m_data.get((int) m_phase % m_data.getSize()));
}