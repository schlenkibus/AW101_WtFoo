#pragma once
#include <libDSP/include/Modules/DSPModule.h>

class NegationModule : public DSPModule {
public:
  explicit NegationModule(DSPHost *parent);
  void tick() override;
  const char *getName() override;

private:
    Input* m_input;
    Output* m_output;
};