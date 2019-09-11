#include "MySynthesizer.h"
#include "DSPInfo.h"
#include "DSPNodes/SineWaveGenerator.h"

static int audioCallBack(const void* inputBuffer,
                          void* outputBuffer,
                          unsigned long framesPerBuffer,
                          const PaStreamCallbackTimeInfo* timeInfo,
                          PaStreamCallbackFlags statusFlags,
                          void* userData)
{
  auto *pSynthContainer = reinterpret_cast<MySynthesizer*>(userData);
  auto *out = reinterpret_cast<float*>(outputBuffer);

  for(decltype(framesPerBuffer) i = 0; i < framesPerBuffer; i++ )
  {
    pSynthContainer->tick();

    auto left = pSynthContainer->getOutputMixerLeft();
    auto right = pSynthContainer->getOutputMixerRight();
    *out++ = left;
    *out++ = right;
  }

  return 0;
}

MySynthesizer::MySynthesizer(int sampleRate, int framesPerBuffer)
  : m_stream{nullptr}
  , m_voices{}
  , _signal{0}
{
  for(auto& v: m_voices) {
    v.reset();
  }

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

void MySynthesizer::tick() {
  float temp = 0.0;
  auto voices = 1;

  for(auto& voice: m_voices) {
    voice.tick();
    auto sig = voice.signal;
    temp += sig;
    voices += sig != 0.0;
  }

  if(voices > 1)
    voices-=1;

  _signal = temp / voices;

  if(_signal > 1.0 || _signal < -1.0) {
    _signal = std::copysign(1.0, _signal);
  }

  m_ringbuffer.put(_signal);
}

float MySynthesizer::getOutputMixerLeft() const
{
  return _signal;
}

float MySynthesizer::getOutputMixerRight() const
{
  return _signal;
}

void MySynthesizer::addNote(int key, float velocity) {
  if(velocity == -1.0)
    velocity = m_velocity;

  for(auto& voice: m_voices) {
    if(!voice.m_envelope.running()) {
      voice.reset();
      voice.noteOn(key, velocity);
      return;
    }
  }
}

void MySynthesizer::setAttackValue(float value) {
  for(auto& v: m_voices) {
    v.m_envelope.setValue<ADREnvelope::Attack>(value);
  }
}

void MySynthesizer::setDecayValue(float value) {
  for(auto& v: m_voices) {
    v.m_envelope.setValue<ADREnvelope::Decay>(value);
  }
}

void MySynthesizer::setAttackTime(long ticks) {
  for(auto& v: m_voices) {
    v.m_envelope.setLength<ADREnvelope::Attack>(ticks);
  }
}

void MySynthesizer::setDecayTime(long ticks) {
  for(auto& v: m_voices) {
    v.m_envelope.setLength<ADREnvelope::Decay>(ticks);
  }
}

void MySynthesizer::setReleaseTime(long ticks) {
  for(auto& v: m_voices) {
    v.m_envelope.setLength<ADREnvelope::Release>(ticks);
  }
}

void MySynthesizer::setMasterKey(int key) {
  m_masterKey = key;
}

void MySynthesizer::setPhaseOffset(float offset)
{
  for(auto& v: m_voices)
  {
    v.m_oscillatorII.setOffset(offset);
  }
}

MySynthesizer::tRingBuffer &MySynthesizer::getRingBuffer() {
  return m_ringbuffer;
}

bool MySynthesizer::toggleNote(int key, float) {

  bool found = false;

  for(auto& v: m_voices) {
    if(v.key == key && v.m_envelope.running()) {
      v.noteOff();
      found = true;
    }
  }

  if(!found)
    addNote(key, m_velocity);

  return !found;
}
