#pragma once
#include "DSPNode.h"
#include <vector>

class DPSMixerNode : public DSPNode {
public:
  void connect(DSPNode *node);
  void remove(DSPNode *node);
  void tick() override;
  const char* TYPE() const override { return "MIXER"; }
protected:
  std::vector<DSPNode *> m_inputs;
};
