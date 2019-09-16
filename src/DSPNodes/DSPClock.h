#pragma once
#include "DSPNode.h"

class DSPClock : public DSPNode {
public:
  explicit DSPClock(long tickLenght);
  void tick() override;
  const char* TYPE() const override { return "CLOCK"; }

private:
    long m_currentTick;
    long m_targetTick;
};
