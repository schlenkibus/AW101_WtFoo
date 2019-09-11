#include "DSPHost.h"
#include "../../Defines.h"
#include "../../Synth/DSPInfo.h"
#include "SoundFile.h"

static int audioCallBack(const void *inputBuffer, void *outputBuffer,
                         unsigned long framesPerBuffer,
                         const PaStreamCallbackTimeInfo *timeInfo,
                         PaStreamCallbackFlags statusFlags, void *userData) {
  auto *dspHost = reinterpret_cast<DSPHost *>(userData);
  auto *out = reinterpret_cast<float *>(outputBuffer);

  for (decltype(framesPerBuffer) i = 0; i < framesPerBuffer; i++) {
    dspHost->tick();
    *out++ = dspHost->getLeftChannelSignal();
    *out++ = dspHost->getRightChannelSignal();
  }

  return 0;
}

DSPHost::DSPHost() : m_track1(DSPInfo::SampleRate), m_track2(DSPInfo::SampleRate) {
  Pa_Initialize();

  Pa_OpenDefaultStream(&m_stream,
                       0,
                       2,
                       paFloat32,
                       DSPInfo::SampleRate,
                       DSPInfo::FramesPerBuffer,
                       audioCallBack,
                       this);
  Pa_StartStream(m_stream);
}

void DSPHost::tick() {
  m_track1.tick();
  m_track2.tick();
  m_drumkit.tick();

}

float DSPHost::getLeftChannelSignal() {
  return m_drumkit._signal;

  auto track1 = m_track1.getSignalLeft();
  auto track2 = m_track2.getSignalLeft();

  auto track1Factor = m_mainCrossFade;
  auto track2Factor = 1 - m_mainCrossFade;


  return track1 * track1Factor + track2 * track2Factor;
}

float DSPHost::getRightChannelSignal() {
  return m_drumkit._signal;

  auto track1 = m_track1.getSignalRight();
  auto track2 = m_track2.getSignalRight();

  auto track1Factor = m_mainCrossFade;
  auto track2Factor = 1 - m_mainCrossFade;


  return track1 * track1Factor + track2 * track2Factor;
}

bool DSPHost::running() {
  return m_running;
}

void DSPHost::setCrossFade(float mix) {
  mix = (mix + 1.0) / 2.0;
  m_mainCrossFade = mix;
}


float DSPHost::getCrossFade() const{
  return (m_mainCrossFade * 2.0) - 1.0;
}