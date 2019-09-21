#pragma once
#include "../../LibDSP/Modules/DSPModule.h"

class DuplicationModule : public DSPModule {
public:
  DuplicationModule();
  const char *TYPE() const override;
  void tick() override;
private:
  Input* m_input;
};
