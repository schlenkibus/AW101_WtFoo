#pragma once
#include "libDSP/include/UUID/UUID.h"

class DSPNode {
public:
  DSPNode();
  virtual ~DSPNode() = default;
  virtual void tick();
  virtual void reset();

  float signal{0};
  LibUUID::UUID m_uuid;
};
