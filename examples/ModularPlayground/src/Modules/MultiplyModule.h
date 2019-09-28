#pragma once
#include <libDSP/include/Modules/DSPModule.h>

class MultiplyModule : public DSPModule {
public:
  MultiplyModule(DSPHost *parent);
  void tick() override;

private:
  const Input *a;
  const Input *b;
  Output *out;
};
