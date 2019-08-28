#pragma once
#include "SignalNode.h"

class GenericSignalEmitterNode : public SignalNode {
public:
  void tick() override;
  void setSignal(bool b);
};
