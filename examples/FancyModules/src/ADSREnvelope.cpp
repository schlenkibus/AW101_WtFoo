#include "ADSREnvelope.h"
#include <libDSP/include/libDSP.h>

template <class T> inline float tickRampSegment(T &segment, float current) {
  const auto len = segment.length;
  const auto tar = segment.targetLevel;
  const auto tal = segment.timeAlive;
  const auto stepsLeft = len - tal;

  float step = 0;
  const auto distanceLeft = tar - current;

  if (len != -1) {
    step = distanceLeft / stepsLeft;
  }

  segment.timeAlive++;


  return current + step;
}

template <class T>
inline void checkTransition(T &segment,
                            ADSREnvelope::State &memberSegmentState) {
  if (segment.timeAlive == segment.length) {
    segment.timeAlive = 0;
    memberSegmentState = segment.nextState;
  }
}

void ADSREnvelope::copyParameters() {
  setValue<Attack>(m_attackValue->getValue());
  setValue<Sustain>(m_sustainValue->getValue());

  setLength<Attack>(m_attackTime->getValue());
  setLength<Decay>(m_decayTime->getValue());
  setLength<Release>(m_releaseTime->getValue());
}

void ADSREnvelope::tick() {
  DSPContainer::tick();

  if(currentSegment == Idle && m_gate->getSignal() != 0.0) {
    copyParameters();
    noteOn();
  }

  if(currentSegment != Idle && currentSegment != Release && m_gate->getSignal() == 0.0) {
    noteOff();
  }

  signal = tickRampSegment(m_segments[currentSegment], signal);
  checkTransition(m_segments[currentSegment], currentSegment);

  m_out->set(signal);
}

void ADSREnvelope::noteOn() {
  currentSegment = Attack;
}

void ADSREnvelope::reset() {
  currentSegment = Idle;
  m_segments[currentSegment].timeAlive = 0;
  signal = 0;
}

ADSREnvelope::ADSREnvelope(DSPHost* h) : DSPModule{h} {
  setValue<Idle>(0.0);
  setValue<Attack>(1.0);
  setValue<Decay>(0.8);
  setValue<Sustain>(0.8);
  setValue<Release>(0.0);

  setLength<Idle>(-1);
  setLength<Attack>(DSPInfo::SampleRate / 25);
  setLength<Decay>(DSPInfo::SampleRate / 25);
  setLength<Sustain>(-1);
  setLength<Attack>(DSPInfo::SampleRate / 25);

  m_segments[State::Idle].nextState = Attack;
  m_segments[State::Attack].nextState = Decay;
  m_segments[State::Decay].nextState = Sustain;
  m_segments[State::Sustain].nextState = Release;
  m_segments[State::Release].nextState = Idle;

  m_gate = createInput("Gate");
  m_out = createOutput("Envelope");

  createParameter("AttackTime", DSPInfo::SampleRate * 0.4, 1, DSPInfo::SampleRate * 2, 3);
  createParameter("DecayTime", DSPInfo::SampleRate * 0.4, 1, DSPInfo::SampleRate * 2, 3);
  createParameter("ReleaseTime", DSPInfo::SampleRate * 0.4, 1, DSPInfo::SampleRate * 2, 3);

  createParameter("AttackValue", 1.0, 0, 1.0);
  createParameter("SustainValue", 1.0, 0, 1.0);

  m_attackTime = findParameter("AttackTime");
  m_decayTime = findParameter("DecayTime");
  m_releaseTime = findParameter("ReleaseTime");
  m_attackValue = findParameter("AttackValue");
  m_sustainValue = findParameter("SustainValue");

  copyParameters();
}

bool ADSREnvelope::running() { return currentSegment != Idle; }

void ADSREnvelope::noteOff() {
  m_segments[currentSegment].timeAlive = 0;
  currentSegment = State::Release;
}
const char *ADSREnvelope::getName() { return "ADSREnvelope"; }
