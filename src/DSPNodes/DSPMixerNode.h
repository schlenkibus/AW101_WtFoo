#pragma once
#include "DSPInput.h"
#include <vector>

class DSPMixerNode : public DSPInput {
public:
  void connect(DSPNode *node) override;
  void remove(const DSPNode *node) override;
  void tick() override;
  const char* TYPE() const override { return "MIXER"; }
protected:
  std::vector<DSPNode *> m_inputs;
};
