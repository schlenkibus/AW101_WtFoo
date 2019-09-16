#pragma once
#include "../DSPNodes/DSPNode.h"
#include "../WaveTables/SineWaveTable.h"
#include <iostream>

template<class WaveTable>
class SineWaveGenerator : public DSPNode {
  public:
    SineWaveGenerator();
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
SineWaveGenerator<WaveTable>::SineWaveGenerator() {
    setFrequency(440);
}

template<class WaveTable>
void SineWaveGenerator<WaveTable>::tick() {
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
void SineWaveGenerator<WaveTable>::setFrequency(float frequency) {
    if(m_frequency == frequency)
      return;

    m_frequency = frequency;
    m_phaseInc = m_frequency * static_cast<float>(m_data.getSize()) / DSPInfo::SampleRate;
}

template <class WaveTable>
float SineWaveGenerator<WaveTable>::getFrequency() const {
  return m_frequency;
}

template <class WaveTable> void SineWaveGenerator<WaveTable>::reset() {
  m_phase = m_offset;
  signal = 0;
}

template <class WaveTable>
float SineWaveGenerator<WaveTable>::getOffset() const {
  return m_offset;
}

template <class WaveTable>
void SineWaveGenerator<WaveTable>::setOffset(float offsetPercent) {
  m_offset = offsetPercent;
}
