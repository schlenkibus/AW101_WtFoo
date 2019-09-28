#pragma once
#include <libDSP/include/Modules/DSPModule.h>

class DuplicationModule : public DSPModule {
public:
  DuplicationModule(DSPHost *parent);
  void tick() override;
private:
  Input* m_input;
};
