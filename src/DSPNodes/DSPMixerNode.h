#pragma once
#include "DSPInputNode.h"
#include <vector>

class DSPMixerNode : public DSPNode {
public:
  void tick() override;
  const char* TYPE() const override { return "MIXER"; }
protected:
  std::vector<DSPNode *> m_inputs;
};
