#pragma once
#include "../DSPInfo.h"
#include "DSPNode.h"
#include <vector>

class DSPInputNode;

class DSPOutputNode : public DSPNode {
  public:
    void tick() override;
    void connectTo(DSPInputNode* node);
    void disconnectFrom(DSPInputNode* node);
  protected:
    struct OutputPair {
        explicit OutputPair(DSPInputNode* node);
        DSPInputNode* m_node;
        DSPSignalIndex m_index;
    };

    std::vector<OutputPair> m_outputs;
};
