#include "SineOscillatorModule.h"

SineOscillatorModule::SineOscillatorModule(DSPHost *host)
    : DSPModule(host), m_osc{host} {
  m_signalOut = createOutput("Sine");
  createInput("Frequency");
  createInput("Reset");

  createParameter("Base Frequency", 321.0, 0.2, 1300, 0);
  createParameter("Frequency Range", 20, 1, 30, 0);

  m_frequencyRange = findParameter("Frequency Range");
  m_baseFrequency = findParameter("Base Frequency");

  m_resetIn = findInput("Reset");
  m_frequencyIn = findInput("Frequency");
}

void SineOscillatorModule::tick() {
  DSPContainer::tick();

  if (m_resetIn->getSignal() != 0.0f) {
    m_osc.reset();
    m_signalOut->set(0);
    return;
  }

  m_osc.setFrequency(
      m_baseFrequency->getValue() +
      (m_frequencyIn->getSignal() * m_frequencyRange->getValue()));

  m_osc.tick();
  m_signalOut->set(m_osc.signal);
}
const char *SineOscillatorModule::getName() { return "Sine Oscillator"; }
