#include "ModularAudioDevice.h"
#include "ModularPlaygroundApplication.h"

ModularAudioDevice::ModularAudioDevice(ModularPlaygroundApplication *application, int sampleRate, int framesPerBuffer)
    : PortAudioDevice(sampleRate, framesPerBuffer)
    , m_app { application }
{
}

void ModularAudioDevice::onRequestBuffer(int framesInBuffer)
{
}

void ModularAudioDevice::requestFrame(Frame &frame)
{
  m_app->tick();
  m_app->fillFrame(frame);
}
