#include "AudioDevice.h"
#include "../ModularPlayground/ModularPlaygroundApplication.h"

AudioDevice::AudioDevice(ModularPlaygroundApplication &exitNode) : m_dspApplication{exitNode}, m_ringBuffer{Frame{0}} {
}

void AudioDevice::onRequestBuffer(int framesInBuffer) {
}

void AudioDevice::requestFrame(Frame &frame) {
  m_dspApplication.tick();
  auto s = m_dspApplication.getAudioOut().getSignal();
  frame.l = s;
  frame.r = s;

  m_ringBuffer.put(frame);
}

const AudioDevice::tBuffer &AudioDevice::getRingBuffer() const {
  return m_ringBuffer;
}
