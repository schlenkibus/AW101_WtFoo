#pragma once
#include "../../LibDSP/Modules/DSPModule.h"

class MultiplyModule : public DSPModule {
public:
  MultiplyModule();
  const char *TYPE() const override;
  void tick() override;

private:
  const Input *a;
  const Input *b;
  Output *out;
};
