#pragma once
#include <libDSP/include/Modules/DSPModule.h>

class NumberModule : public DSPModule {
public:
  explicit NumberModule(DSPHost *host);
  void tick() override;
  const char *getName() override;

protected:
  Output* m_numberOut;
  Parameter* m_numberIn;
};
