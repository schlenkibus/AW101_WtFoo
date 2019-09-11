#include "DrumKit.h"

DrumKit::DrumKit() : m_osc{} {

  m_osc.setFrequency(300);

  m_ampEnvelope.init(1.0, static_cast<long>(DSPInfo::SampleRate * 0.1), 0.8,
                       static_cast<long>(DSPInfo::SampleRate * 0.05),
                       static_cast<long>(DSPInfo::SampleRate * 0.25));

  m_pitchEnvelope.init(1.0, static_cast<long>(DSPInfo::SampleRate * 0.05), 0.5,
                       static_cast<long>(DSPInfo::SampleRate * 0.15),
                       static_cast<long>(DSPInfo::SampleRate));
}

void DrumKit::tick() {
  if(m_ampEnvelope.running()) {

    m_osc.setFrequency((startFreq - (1 - m_pitchEnvelope.signal) * startFreq));

    m_osc.tick();
    m_ampEnvelope.tick();
    m_pitchEnvelope.tick();

    _signal = m_ampEnvelope.signal * m_osc.signal;
  } else {
    if(startFreq != 0)
      m_osc.setFrequency(startFreq);
    _signal = 0.0;
  }
}

void DrumKit::hit() {
  if(!m_ampEnvelope.running()) {
    if(startFreq != 0)
      m_osc.setFrequency(startFreq);

    m_osc.reset();
    m_pitchEnvelope.noteOff();

    m_ampEnvelope.noteOn(0);
    m_pitchEnvelope.noteOn(0);
    startFreq = m_osc.getFrequency();
  }

}
