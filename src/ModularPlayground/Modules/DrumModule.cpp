#include "DrumModule.h"

DrumModule::DrumModule(DSPHost *parent) : DSPModule(parent) {
  m_drumKit = createNode<DrumKit>();
  m_audioOut = createOutput("Audio");
  createInput("Hit");
  createInput("Reset");

  m_hitIn = findInput("Hit");
  m_resetIn = findInput("Reset");
}

void DrumModule::tick() {
  DSPContainer::tick();

  if(m_hitIn->getSignal() != 0) {
    m_drumKit->hit();
  }

  if(m_resetIn->getSignal() != 0) {
    m_drumKit->reset();
  }

  m_audioOut->set(m_drumKit->signal);
}

const char *DrumModule::TYPE() const {
  return "DrumModule";
}

void DrumModule::setBaseFrequency(float frequency) {
  m_drumKit->startFreq = frequency;
}
