#pragma once

#include "SignalNode.h"
#include <mutex>
class AndGateNode : public SignalNode {
  public:
    void tick() override;

    void setA(bool a);
    void setB(bool b);

  protected:
    bool inputA = false;
    bool inputB = false;
};
