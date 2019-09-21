#include "DrumModule.h"

DrumModule::DrumModule(DSPHost *parent) : DSPModule(parent) {
  m_audioOut = createOutput("Audio");
  createInput("Hit");
  createInput("Reset");

  m_hitIn = findInput("Hit");
  m_resetIn = findInput("Reset");
}

void DrumModule::tick() {
  DSPContainer::tick();

  if(m_hitIn->getSignal() != 0) {
  }

  if(m_resetIn->getSignal() != 0) {
  }

  m_audioOut->set(0.0);
}

const char *DrumModule::TYPE() const {
  return "DrumModule";
}

void DrumModule::setBaseFrequency(float frequency) {
}
