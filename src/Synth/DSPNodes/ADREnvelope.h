#pragma once
#include "DSPNode.h"
#include <array>
#include <functional>

class ADREnvelope : public DSPNode {
public:
  enum State { Idle, Attack, Decay, Sustain, Release };

  ADREnvelope();
  void noteOn(float velocity);
  void noteOff();
  void tick() override;

  void reset() override;

  template <State tSegment> void setValue(float level) {
    auto &segment = m_segments[tSegment];
    segment.targetLevel = level;
  }

  template <State tSegment> void setLength(long length) {
    auto &segment = m_segments[tSegment];
    segment.length = length;
  }

  bool running();

protected:
  State currentSegment = Idle;

  struct Segment {
    float targetLevel = 0.0;
    long length = -1;
    long timeAlive = 0;
    State nextState = Idle;
  };

  std::array<Segment, 5> m_segments{};
};
