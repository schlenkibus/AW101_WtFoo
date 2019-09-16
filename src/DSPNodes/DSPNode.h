#pragma once
#include "../UUID/UUID.h"

class DSPNode {
public:
  DSPNode();
  virtual void tick() = 0;
  virtual void reset();
  virtual void print(std::ostream& stream) const;
  virtual const char *TYPE() const { return "INVALID"; }
  float signal{0};
  LibUUID::UUID m_uuid;

  friend std::ostream& operator<< (std::ostream& out, const DSPNode& mc) {
    mc.print(out);
    return out;
  }
};
