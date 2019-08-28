#include "ADREnvelope.h"
#include "../DSPInfo.h"

void ADREnvelope::tick() {
  if(!running()) {
    signal = 0;
    return;
  }

  auto& segment = m_segments[currentSegment];
  segment.curr += segment.inc;
  segment.pos++;

  signal = segment.curr;

  if(segment.pos >= segment.lenght)
    currentSegment++;
}

void ADREnvelope::noteOn(float velocity) {
  for(auto& segment: m_segments) {
    segment.pos = 0;
    segment.inc = (segment.endValue - segment.startValue) / segment.lenght;
    segment.curr = segment.startValue;
  }

  currentSegment = 0;
}
void ADREnvelope::reset() {
  currentSegment = 3;
  signal = 0;
}

void ADREnvelope::setAttack(float value, int lenght) {
  auto& attack = m_segments[0];
  attack.startValue = 0;
  attack.lenght = lenght;
  attack.endValue = value;
  m_segments[1].startValue = value;
}

void ADREnvelope::setReleaseTime(int lenght) {
  auto& release = m_segments[2];
  release.lenght = lenght;
  release.startValue = m_segments[1].endValue;
  release.endValue = 0;
}

void ADREnvelope::setDecay(float value, int lenght) {
  auto& release = m_segments[1];
  release.lenght = lenght;
  release.startValue = m_segments[0].endValue;
  release.endValue = value;
  m_segments[2].startValue = value;
}

ADREnvelope::ADREnvelope() {
  setAttack(0.5, 0.25 * DSPInfo::SampleRate);
  setDecay(1.0, 0.5 * DSPInfo::SampleRate);
  setReleaseTime(1 * DSPInfo::SampleRate);
}

bool ADREnvelope::running(){
    return currentSegment < 3;
}

void ADREnvelope::setAttackTime(int lenght){
    setAttack(m_segments[0].endValue, lenght);
}

void ADREnvelope::setDecayTime(int lenght) {
  setDecay(m_segments[1].endValue, lenght);
}

void ADREnvelope::setAttackValue(float value) {
  setAttack(value, m_segments[0].lenght);
}

void ADREnvelope::setDecayValue(float value) {
  setDecay(value, m_segments[1].lenght);
}
