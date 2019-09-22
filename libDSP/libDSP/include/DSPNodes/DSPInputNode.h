#pragma once

#include "DSPNode.h"
#include "DSPOutputNode.h"

class DSPInputNode : public DSPNode {
public:
    explicit DSPInputNode(float def = 0.0);
    void tick() override;
    virtual void connect(DSPOutputNode* node);
    DSPOutputNode* connectedTo();
    void removeIngoingConnection();
    void print(std::ostream &stream) const override;
    const char *TYPE() const override;

  protected:
    DSPOutputNode* m_signalFrom{nullptr};
    float defaultSignal;
};