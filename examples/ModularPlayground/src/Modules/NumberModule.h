#pragma once
#include <libDSP/include/Modules/DSPModule.h>

class NumberModule : public DSPModule {
public:
  const char *TYPE() const override;
  explicit NumberModule(DSPHost *host);
  void tick() override;

protected:
  Output* m_numberOut;
  Parameter* m_numberIn;
};
