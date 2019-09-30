#include "ModularAudioDevice.h"

ModularAudioDevice::ModularAudioDevice(
    ModularPlaygroundApplication *application, int sampleRate,
    int framesPerBuffer)
    : PortAudioDevice(sampleRate, framesPerBuffer), m_app{application} {

}

void ModularAudioDevice::onRequestBuffer(int framesInBuffer) {
    m_app->slowTick();
}

void ModularAudioDevice::requestFrame(Frame &frame) {
  m_app->tick();
  m_app->fillFrame(frame);
}
