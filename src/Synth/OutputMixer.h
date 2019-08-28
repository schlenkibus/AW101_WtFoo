#pragma once
#include "DSPNodes/DSPInputNode.h"
#include <vector>

class OutputMixer : public DSPInputNode {
public:
  void tick() override;
  void setMaster(float gain);
  float getMaster() const;
protected:
  float m_masterGain{0.1};
};
