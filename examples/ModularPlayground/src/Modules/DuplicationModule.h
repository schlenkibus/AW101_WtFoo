#pragma once
#include <libDSP/Modules/DSPModule.h>

class DuplicationModule : public DSPModule {
public:
  DuplicationModule(DSPHost *parent);
  const char *TYPE() const override;
  void tick() override;
private:
  Input* m_input;
};
