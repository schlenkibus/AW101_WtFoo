#pragma once
#include <array>
#include <functional>
#include <libDSP/include/Modules/DSPModule.h>

class ADSREnvelope : public DSPModule {
public:
  enum State { Idle, Attack, Decay, Sustain, Release };

  ADSREnvelope(DSPHost* host);

  void reset() override;
  void tick() override;

  void copyParameters();
  const char *getName() override;

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
  void noteOn();
  void noteOff();

  State currentSegment = Idle;

  struct Segment {
    float targetLevel = 0.0;
    long length = -1;
    long timeAlive = 0;
    State nextState = Idle;
  };

  std::array<Segment, 5> m_segments{};

  Input* m_gate;
  Output* m_out;
  Parameter* m_attackTime;
  Parameter* m_decayTime;
  Parameter* m_releaseTime;
  Parameter* m_attackValue;
  Parameter* m_decayValue;
  Parameter* m_sustainValue;
};