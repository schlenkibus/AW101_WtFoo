#include "AudioDevice.h"

AudioDevice::AudioDevice(DSPContainer &host) : m_hostContainer{host} {
}

void AudioDevice::onRequestBuffer() {

}

void AudioDevice::requestFrame(AudioDevice::Frame &frame) {
  m_hostContainer.tick();
  auto s = m_hostContainer.signal;
  frame.l = s;
  frame.r = s;
}
