#pragma once
#include <libDSP/include/Modules/DSPModule.h>

class CrossFaderModule : public DSPModule {
public:
  explicit CrossFaderModule(DSPHost* host);
  const char *getName() override;
  void tick() override;

private:
  Input* l;
  Input* r;
  Parameter* mix;
  Output* o;
};
