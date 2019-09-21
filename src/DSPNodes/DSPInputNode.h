#pragma once

#include "DSPNode.h"
class DSPInputNode : public DSPNode {
public:
    explicit DSPInputNode(float def = 0.0);
    void tick() override;
    virtual void connect(DSPNode* node);
    void remove();
    void print(std::ostream &stream) const override;
    const char *TYPE() const override;

  protected:
    DSPNode* m_signalFrom{nullptr};
    float defaultSignal;
};
