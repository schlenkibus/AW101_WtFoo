#pragma once
#include <libDSP/include/Modules/DSPModule.h>

class MultiplyModule : public DSPModule {
public:
  MultiplyModule(DSPHost *parent);
  const char *TYPE() const override;
  void tick() override;

private:
  const Input *a;
  const Input *b;
  Output *out;
};
