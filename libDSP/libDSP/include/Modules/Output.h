#pragma once
#include "libDSP/include/DSPNodes/DSPOutputNode.h"

class DSPModule;

class Output {
public:
 Output(DSPModule *parent, std::string na, DSPOutputNode *no);
  std::string name;

  friend bool operator==(const Output &lhs, const Output &rhs) {
    return lhs.name == rhs.name;
  }

  void set(float signal) const { node->feedSignal(signal); }

  const LibUUID::UUID &getUUID() const { return node->m_uuid; }

  DSPModule* getModule();
private:
  DSPOutputNode *node;

  friend class DSPModule;
  friend class Input;
};
