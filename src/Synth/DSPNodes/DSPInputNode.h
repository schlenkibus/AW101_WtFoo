#pragma once
#include "../DSPInfo.h"
#include "DSPNode.h"
#include <cstddef>
#include <vector>

class DSPInputNode : public DSPNode {
public:
  void tick() override;
  DSPSignalIndex addInput();
    void setSignal(DSPSignalIndex index, float l, float r);
    void disconnect(DSPSignalIndex index);

  protected:
    struct Input {
        bool m_active;
        float m_leftSample;
        float m_rightSample;
    };

    inline Input* getItem(DSPSignalIndex index);

    std::vector<Input> m_inputs{};
};
