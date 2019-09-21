#pragma once
#include "../../LibDSP/Modules/DSPModule.h"

class MixerModule : public DSPModule {
public:
  MixerModule();
  const char *TYPE() const override;
  void tick() override;
  Output *m_out;
};
