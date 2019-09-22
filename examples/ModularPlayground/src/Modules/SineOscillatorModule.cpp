#include "SineOscillatorModule.h"

SineOscillatorModule::SineOscillatorModule(DSPHost *host) : DSPModule(host), m_osc{host} {
  m_signalOut = createOutput("Sine");
  createInput("Frequency");
  createInput("Reset");

  createParameter("Base Frequency", 321.0, 80, 1300, 0);
  createParameter("Frequency Range", 20, 1, 30, 0);

  m_resetIn = findInput("Reset");
  m_frequencyIn = findInput("Frequency");
}

void SineOscillatorModule::tick() {
  DSPContainer::tick();

  if(m_resetIn->getSignal() != 0.0f)
    m_osc.reset();

  m_osc.setFrequency(m_baseFreqency + (m_frequencyIn->getSignal() * m_frequencyRange));

  m_osc.tick();
  m_signalOut->set(m_osc.signal);
}

void SineOscillatorModule::setFrequencyBase(float baseFreq) {
  m_baseFreqency = baseFreq;
}

void SineOscillatorModule::setFrequencyRange(float range) {
  m_frequencyRange = range;
}

float SineOscillatorModule::getFrequencyBase() const {
  return m_baseFreqency;
}

float SineOscillatorModule::getFrequencyRange() const {
  return m_frequencyRange;
}

const char *SineOscillatorModule::TYPE() const { return "SineOscillatorModule"; }