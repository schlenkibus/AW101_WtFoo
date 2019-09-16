#include "DrumKit.h"

DrumKit::DrumKit() : m_osc{} {

  m_osc.setFrequency(420);

  m_pitchEnvelope.init(1.0, static_cast<long>(DSPInfo::SampleRate * 0.002), 0.25,
                       static_cast<long>(DSPInfo::SampleRate * 0.013),
                       static_cast<long>(DSPInfo::SampleRate * 0.23));

  m_ampEnvelope.init(1.0, static_cast<long>(DSPInfo::SampleRate * 0.005), 0.75,
                       static_cast<long>(DSPInfo::SampleRate * 0.015),
                       static_cast<long>(DSPInfo::SampleRate * 0.3));
}

void DrumKit::tick() {
  if(m_ampEnvelope.running()) {

    m_osc.setFrequency((startFreq - (1 - m_pitchEnvelope.signal) * startFreq));

    m_osc.tick();
    m_ampEnvelope.tick();
    m_pitchEnvelope.tick();

    signal = m_ampEnvelope.signal * m_osc.signal;
  } else {
    if(startFreq != 0)
      m_osc.setFrequency(startFreq);

    signal = 0.0;
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
void DrumKit::reset() {
  m_pitchEnvelope.reset();
  m_ampEnvelope.reset();

  m_osc.reset();
  DSPNode::reset();
}
