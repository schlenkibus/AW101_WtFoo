#pragma once
#include "../UUID/UUID.h"
#include "../Defines.h"

class DSPNode {
public:
  DSPNode();
  virtual void tick() = 0;
  virtual void reset();
  virtual void print(std::ostream& stream) const;
  virtual const char *TYPE() const { return "DSPNode Pure Virtual"; }

  float signal{0};
  LibUUID::UUID m_uuid;

  friend std::ostream& operator<< (std::ostream& out, const DSPNode& node) {
    node.print(out);
    return out;
  }

};
