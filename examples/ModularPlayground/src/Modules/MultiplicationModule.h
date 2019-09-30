#pragma once
#include <libDSP/include/Modules/DSPModule.h>

class MultiplicationModule : public DSPModule {
public:
  MultiplicationModule(DSPHost *parent);
  void tick() override;
  const char *getName() override;

private:
  const Input *a;
  const Input *b;
  Output *out;
};
