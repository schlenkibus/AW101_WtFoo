#include "ModularAudioDevice.h"

ModularAudioDevice::ModularAudioDevice(
    ModularPlaygroundApplication *application, int sampleRate,
    int framesPerBuffer)
    : PortAudioDevice(sampleRate, framesPerBuffer), m_app{application} {

}

void ModularAudioDevice::onRequestBuffer(int framesInBuffer) {

}

void ModularAudioDevice::requestFrame(Frame &frame) {
  m_app->tick();
  frame.l = m_app->m_leftSignalNode.signal;
  frame.r = m_app->m_rightSignalNode.signal;
}
