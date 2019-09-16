#include "PortAudioDevice.h"

static int audioCallBack(const void *inputBuffer, void *outputBuffer,
                         unsigned long framesPerBuffer,
                         const PaStreamCallbackTimeInfo *timeInfo,
                         PaStreamCallbackFlags statusFlags, void *userData) {
  auto *dspHost = reinterpret_cast<PortAudioDevice *>(userData);
  auto *out = reinterpret_cast<float *>(outputBuffer);

  dspHost->onRequestBuffer();
  AudioDevice::Frame f;

  for (decltype(framesPerBuffer) i = 0; i < framesPerBuffer; i++) {
    dspHost->requestFrame(f);
    *out++ = f.l;
    *out++ = f.r;
  }

  return 0;
}

PortAudioDevice::PortAudioDevice(DSPContainer& host, int sampleRate, int framesPerBuffer) : AudioDevice{host} {
  Pa_Initialize();

  Pa_OpenDefaultStream(&m_stream,
                       0,
                       2,
                       paFloat32,
                       sampleRate,
                       framesPerBuffer,
                       audioCallBack,
                       this);
  Pa_StartStream(m_stream);
}

bool PortAudioDevice::initialized() { return m_stream != nullptr; }
