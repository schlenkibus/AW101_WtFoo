#pragma once

#include "DSPNode.h"
class DSPInput : public DSPNode {
public:
    explicit DSPInput(float def = 0.0);
    void tick() override;
    virtual void connect(DSPNode* node);
    virtual void remove(const DSPNode* node);
    void print(std::ostream &stream) const override;
    const char *TYPE() const override;

  protected:
    DSPNode* m_signalFrom{nullptr};
    float defaultSignal;
};
