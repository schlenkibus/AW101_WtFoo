#include "AudioDevice.h"

AudioDevice::AudioDevice(DSPContainer &host) : m_hostContainer{host}, m_ringBuffer{Frame{0}} {
}

void AudioDevice::onRequestBuffer(int framesInBuffer) {
}

void AudioDevice::requestFrame(Frame &frame) {
  m_hostContainer.tick();
  auto s = m_hostContainer.signal;
  frame.l = s;
  frame.r = s;

  m_ringBuffer.put(frame);
}

const AudioDevice::tBuffer &AudioDevice::getRingBuffer() const {
  return m_ringBuffer;
}
