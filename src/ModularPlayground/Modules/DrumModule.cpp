#include "DrumModule.h"

DrumModule::DrumModule() {
  m_drumKit = createNode<DrumKit>();
  m_audioOut = createOutput("Audio");
  m_hitIn = createInput("Hit");
  m_resetIn = createInput("Reset");
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
