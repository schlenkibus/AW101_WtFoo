#pragma once
#include "DSPNode.h"

class DSPOutputNode : public DSPNode {
public:
  void feedSignal(float signal);
  void tick() override;
  const char *TYPE() const override { return "DSPOutputNode"; };
};
