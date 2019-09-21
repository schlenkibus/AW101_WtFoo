#include "ADREnvelope.h"
#include "../LibDSP/DSPInfo.h"

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
                            ADREnvelope::State &memberSegmentState) {
  if (segment.timeAlive == segment.length) {
    segment.timeAlive = 0;
    memberSegmentState = segment.nextState;
  }
}

void ADREnvelope::tick() {
  signal = tickRampSegment(m_segments[currentSegment], signal);
  checkTransition(m_segments[currentSegment], currentSegment);
}

void ADREnvelope::noteOn(float velocity) { currentSegment = Attack; }

void ADREnvelope::reset() {
  currentSegment = Idle;
  m_segments[currentSegment].timeAlive = 0;
  signal = 0;
}

ADREnvelope::ADREnvelope() {
  init(1.0, static_cast<long>(DSPInfo::SampleRate * 0.05), 0.8,
       static_cast<long>(DSPInfo::SampleRate * 0.1),
       static_cast<long>(DSPInfo::SampleRate * 0.25));

  m_segments[State::Idle].nextState = Attack;
  m_segments[State::Attack].nextState = Decay;
  m_segments[State::Decay].nextState = Release;
  m_segments[State::Release].nextState = Idle;
}

bool ADREnvelope::running() { return currentSegment != Idle; }

void ADREnvelope::noteOff() {
  m_segments[currentSegment].timeAlive = 0;
  currentSegment = State::Release;
}

void ADREnvelope::init(float levelA, long lengthA, float levelD, long lengthD,
                       long lengthR) {
  setValue<Idle>(0.0);
  setLength<Idle>(-1);

  setValue<Attack>(levelA);
  setLength<Attack>(lengthA);

  setValue<Decay>(levelD);
  setLength<Decay>(lengthD);

  setValue<Release>(0.0);
  setLength<Release>(lengthR);
}
