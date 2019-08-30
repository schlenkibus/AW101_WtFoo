#include "Voice.h"

void Voice::tick() {
  m_oscillatorI.tick();
  m_oscillatorII.tick();

  m_envelope.tick();

  auto oscPure = m_oscillatorI.signal + m_oscillatorII.signal;

  signal = oscPure * m_envelope.signal;
}


void Voice::noteOn(int k, float velocity) {
  reset();
  key = k;
  m_envelope.noteOn(velocity);
  m_oscillatorI.setFrequency(key);
  m_oscillatorII.setFrequency(key * m_oscillatorII.getOffset());
}

void Voice::reset() {
  m_envelope.reset();
  m_oscillatorII.reset();
  m_oscillatorI.reset();
  signal = 0;
}
void Voice::noteOff() {
  m_envelope.noteOff();
}
