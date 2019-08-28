#pragma once
#include "DSPNode.h"
#include <array>

class ADREnvelope : public DSPNode {
public:
  ADREnvelope();
  void noteOn(float velocity);
  void tick() override;
  void reset() override;

  void setAttackTime(int lenght);
  void setDecayTime(int lenght);
  void setReleaseTime(int length);

  void setAttackValue(float value);
  void setDecayValue(float value);

  void setAttack(float value, int lenght);
  void setDecay(float value, int lenght);

  bool running();

protected:
    short currentSegment{0};

    struct Segment {
        long lenght;
        long pos;
        float startValue;
        float endValue;

        float inc;

        float curr;
    };

    std::array<Segment, 3> m_segments{};
};
