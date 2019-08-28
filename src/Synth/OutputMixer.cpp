#include "OutputMixer.h"

void OutputMixer::setMaster(float gain) {
  m_masterGain = gain;
}

void OutputMixer::tick() {
  DSPInputNode::tick();
  signal = m_masterGain * signal;
}
float OutputMixer::getMaster() const {
  return m_masterGain;
}
