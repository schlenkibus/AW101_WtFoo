#include "AudioDevice.h"

AudioDevice::AudioDevice(DSPHost &exitNode) : m_dspHost{exitNode}, m_ringBuffer{Frame{0}} {
}

void AudioDevice::onRequestBuffer(int framesInBuffer) {
}

void AudioDevice::requestFrame(Frame &frame) {
  m_dspHost.tick();
  auto s = m_dspHost.getAudioOut().getSignal();
  frame.l = s;
  frame.r = s;

  m_ringBuffer.put(frame);
}

const AudioDevice::tBuffer &AudioDevice::getRingBuffer() const {
  return m_ringBuffer;
}
