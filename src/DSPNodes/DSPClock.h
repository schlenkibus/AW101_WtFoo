#pragma once
#include "DSPCollection.h"
#include "DSPInput.h"
#include "DSPNode.h"

class DSPClock : public DSPCollection {
public:
  explicit DSPClock(long tickLenght);
  void tick() override;
  const char* TYPE() const override { return "CLOCK"; }
  void print(std::ostream &stream) const override;
  void removeNode(const LibUUID::UUID &uuid) override;

  DSPInput* getInputNode();

private:
  DSPInput* m_inputRunning;
  long m_currentTick;
  long m_targetTick;
};
