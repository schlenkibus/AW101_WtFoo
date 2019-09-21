#pragma once
#include "../LibDSP/DSPInfo.h"
#include "../LibDSP/DSPNodes/DSPNode.h"
#include "../WaveTables/SineWaveTable.h"
#include <iostream>

template<class WaveTable>
class WaveTableOscillator : public DSPNode {
  public:
    WaveTableOscillator();
    void tick() override;
    void setFrequency(float frequency);
    float getFrequency() const;
    void reset() override;
    float getOffset() const;
    void setOffset(float offsetPercent);



  protected:
    float m_frequency{440};
    float m_phaseInc{};
    float m_phase{0};
    float m_offset{0};

    WaveTable m_data;
};

template<class WaveTable>
WaveTableOscillator<WaveTable>::WaveTableOscillator() {
    setFrequency(440);
}

template<class WaveTable>
void WaveTableOscillator<WaveTable>::tick() {
    auto pos = m_phase + m_phaseInc;

    if(pos < m_data.getSize()) {
      m_phase = pos;
    } else {
      auto tooMuch = pos - m_data.getSize() - 1;
      m_phase = tooMuch;
    }

    signal = m_data.get((int)m_phase % m_data.getSize());
}

template<class WaveTable>
void WaveTableOscillator<WaveTable>::setFrequency(float frequency) {
    if(m_frequency == frequency)
      return;

    m_frequency = frequency;
    m_phaseInc = m_frequency * static_cast<float>(m_data.getSize()) / DSPInfo::SampleRate;
}

template <class WaveTable>
float WaveTableOscillator<WaveTable>::getFrequency() const {
  return m_frequency;
}

template <class WaveTable> void WaveTableOscillator<WaveTable>::reset() {
  m_phase = m_offset;
  signal = 0;
}

template <class WaveTable>
float WaveTableOscillator<WaveTable>::getOffset() const {
  return m_offset;
}

template <class WaveTable>
void WaveTableOscillator<WaveTable>::setOffset(float offsetPercent) {
  m_offset = offsetPercent;
}
