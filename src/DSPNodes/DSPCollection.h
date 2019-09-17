#pragma once

#include "DSPContainer.h"
class DSPCollection : public DSPContainer {
public:
  void tick() override;
  const char *TYPE() const override;
};